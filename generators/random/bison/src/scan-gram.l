/* Bison Grammar Scanner                             -*- C -*-

   Copyright (C) 2002 Free Software Foundation, Inc.

   This file is part of Bison, the GNU Compiler Compiler.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307  USA
*/

%option debug nodefault noyywrap never-interactive
%option prefix="gram_" outfile="lex.yy.c"

%{
#include "system.h"

#include <mbswidth.h>
#include <get-errno.h>
#include <quote.h>

#include "complain.h"
#include "files.h"
#include "getargs.h"
#include "gram.h"
#include "reader.h"
#include "uniqstr.h"

#define YY_USER_INIT					\
  do							\
    {							\
      scanner_cursor.file = current_file;		\
      scanner_cursor.line = 1;				\
      scanner_cursor.column = 1;			\
    }							\
  while (0)

/* Location of scanner cursor.  */
boundary scanner_cursor;

static void adjust_location (location *, char const *, size_t);
#define YY_USER_ACTION  adjust_location (loc, yytext, yyleng);

static size_t no_cr_read (FILE *, char *, size_t);
#define YY_INPUT(buf, result, size) ((result) = no_cr_read (yyin, buf, size))


/* OBSTACK_FOR_STRING -- Used to store all the characters that we need to
   keep (to construct ID, STRINGS etc.).  Use the following macros to
   use it.

   Use STRING_GROW to append what has just been matched, and
   STRING_FINISH to end the string (it puts the ending 0).
   STRING_FINISH also stores this string in LAST_STRING, which can be
   used, and which is used by STRING_FREE to free the last string.  */

static struct obstack obstack_for_string;

/* A string representing the most recently saved token.  */
static char *last_string;


#define STRING_GROW   \
  obstack_grow (&obstack_for_string, yytext, yyleng)

#define STRING_FINISH					\
  do {							\
    obstack_1grow (&obstack_for_string, '\0');		\
    last_string = obstack_finish (&obstack_for_string);	\
  } while (0)

#define STRING_FREE \
  obstack_free (&obstack_for_string, last_string)

void
scanner_last_string_free (void)
{
  STRING_FREE;
}

/* Within well-formed rules, RULE_LENGTH is the number of values in
   the current rule so far, which says where to find `$0' with respect
   to the top of the stack.  It is not the same as the rule->length in
   the case of mid rule actions.

   Outside of well-formed rules, RULE_LENGTH has an undefined value.  */
static int rule_length;

static void handle_dollar (int token_type, char *cp, location loc);
static void handle_at (int token_type, char *cp, location loc);
static void handle_syncline (char *args);
static int convert_ucn_to_byte (char const *hex_text);
static void unexpected_end_of_file (boundary, char const *);

%}
%x SC_COMMENT SC_LINE_COMMENT SC_YACC_COMMENT
%x SC_STRING SC_CHARACTER
%x SC_AFTER_IDENTIFIER
%x SC_ESCAPED_STRING SC_ESCAPED_CHARACTER
%x SC_PRE_CODE SC_BRACED_CODE SC_PROLOGUE SC_EPILOGUE

letter	  [.abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_]
id	  {letter}({letter}|[0-9])*
directive %{letter}({letter}|[0-9]|-)*
int	  [0-9]+

/* POSIX says that a tag must be both an id and a C union member, but
   historically almost any character is allowed in a tag.  We disallow
   NUL and newline, as this simplifies our implementation.  */
tag	 [^\0\n>]+

/* Zero or more instances of backslash-newline.  Following GCC, allow
   white space between the backslash and the newline.  */
splice	 (\\[ \f\t\v]*\n)*

%%
%{
  /* Nesting level of the current code in braces.  */
  int braces_level IF_LINT (= 0);

  /* Parent context state, when applicable.  */
  int context_state IF_LINT (= 0);

  /* Token type to return, when applicable.  */
  int token_type IF_LINT (= 0);

  /* Location of most recent identifier, when applicable.  */
  location id_loc IF_LINT (= *loc);

  /* Where containing code started, when applicable.  */
  boundary code_start IF_LINT (= loc->start);

  /* Where containing comment or string or character literal started,
     when applicable.  */
  boundary token_start IF_LINT (= loc->start);
%}


  /*-----------------------.
  | Scanning white space.  |
  `-----------------------*/

<INITIAL,SC_AFTER_IDENTIFIER,SC_PRE_CODE>
{
  [ \f\n\t\v]  ;
  ","	       warn_at (*loc, _("stray `,' treated as white space"));

  /* Comments. */
  "//".*       ;
  "/*" {
    token_start = loc->start;
    context_state = YY_START;
    BEGIN SC_YACC_COMMENT;
  }

  /* #line directives are not documented, and may be withdrawn or
     modified in future versions of Bison.  */
  ^"#line "{int}" \"".*"\"\n" {
    handle_syncline (yytext + sizeof "#line " - 1);
  }
}


  /*----------------------------.
  | Scanning Bison directives.  |
  `----------------------------*/
<INITIAL>
{
  "%binary"               return PERCENT_NONASSOC;
  "%debug"                return PERCENT_DEBUG;
  "%define"               return PERCENT_DEFINE;
  "%defines"              return PERCENT_DEFINES;
  "%destructor"		  token_type = PERCENT_DESTRUCTOR; BEGIN SC_PRE_CODE;
  "%dprec"		  return PERCENT_DPREC;
  "%error"[-_]"verbose"   return PERCENT_ERROR_VERBOSE;
  "%expect"               return PERCENT_EXPECT;
  "%file-prefix"          return PERCENT_FILE_PREFIX;
  "%fixed"[-_]"output"[-_]"files"   return PERCENT_YACC;
  "%glr-parser"           return PERCENT_GLR_PARSER;
  "%left"                 return PERCENT_LEFT;
  "%lex-param"		  token_type = PERCENT_LEX_PARAM; BEGIN SC_PRE_CODE;
  "%locations"            return PERCENT_LOCATIONS;
  "%merge"		  return PERCENT_MERGE;
  "%name"[-_]"prefix"     return PERCENT_NAME_PREFIX;
  "%no"[-_]"lines"        return PERCENT_NO_LINES;
  "%nonassoc"             return PERCENT_NONASSOC;
  "%nterm"                return PERCENT_NTERM;
  "%output"               return PERCENT_OUTPUT;
  "%parse-param"	  token_type = PERCENT_PARSE_PARAM; BEGIN SC_PRE_CODE;
  "%prec"                 rule_length--; return PERCENT_PREC;
  "%printer"              token_type = PERCENT_PRINTER; BEGIN SC_PRE_CODE;
  "%pure"[-_]"parser"     return PERCENT_PURE_PARSER;
  "%right"                return PERCENT_RIGHT;
  "%skeleton"             return PERCENT_SKELETON;
  "%start"                return PERCENT_START;
  "%term"                 return PERCENT_TOKEN;
  "%token"                return PERCENT_TOKEN;
  "%token"[-_]"table"     return PERCENT_TOKEN_TABLE;
  "%type"                 return PERCENT_TYPE;
  "%union"		  token_type = PERCENT_UNION; BEGIN SC_PRE_CODE;
  "%verbose"              return PERCENT_VERBOSE;
  "%yacc"                 return PERCENT_YACC;

  {directive} {
    complain_at (*loc, _("invalid directive: %s"), quote (yytext));
  }

  "="                     return EQUAL;
  "|"                     rule_length = 0; return PIPE;
  ";"                     return SEMICOLON;

  {id} {
    val->symbol = symbol_get (yytext, *loc);
    id_loc = *loc;
    rule_length++;
    BEGIN SC_AFTER_IDENTIFIER;
  }

  {int} {
    unsigned long num;
    set_errno (0);
    num = strtoul (yytext, 0, 10);
    if (INT_MAX < num || get_errno ())
      {
	complain_at (*loc, _("integer out of range: %s"), quote (yytext));
	num = INT_MAX;
      }
    val->integer = num;
    return INT;
  }

  /* Characters.  We don't check there is only one.  */
  "'"	      STRING_GROW; token_start = loc->start; BEGIN SC_ESCAPED_CHARACTER;

  /* Strings. */
  "\""	      STRING_GROW; token_start = loc->start; BEGIN SC_ESCAPED_STRING;

  /* Prologue. */
  "%{"        code_start = loc->start; BEGIN SC_PROLOGUE;

  /* Code in between braces.  */
  "{" {
    STRING_GROW;
    token_type = BRACED_CODE;
    braces_level = 0;
    code_start = loc->start;
    BEGIN SC_BRACED_CODE;
  }

  /* A type. */
  "<"{tag}">" {
    obstack_grow (&obstack_for_string, yytext + 1, yyleng - 2);
    STRING_FINISH;
    val->uniqstr = uniqstr_new (last_string);
    STRING_FREE;
    return TYPE;
  }

  "%%" {
    static int percent_percent_count;
    if (++percent_percent_count == 2)
      {
	code_start = loc->start;
	BEGIN SC_EPILOGUE;
      }
    return PERCENT_PERCENT;
  }

  . {
    complain_at (*loc, _("invalid character: %s"), quote (yytext));
  }
}


  /*-----------------------------------------------------------------.
  | Scanning after an identifier, checking whether a colon is next.  |
  `-----------------------------------------------------------------*/

<SC_AFTER_IDENTIFIER>
{
  ":" {
    rule_length = 0;
    *loc = id_loc;
    BEGIN INITIAL;
    return ID_COLON;
  }
  . {
    scanner_cursor.column -= mbsnwidth (yytext, yyleng, 0);
    yyless (0);
    *loc = id_loc;
    BEGIN INITIAL;
    return ID;
  }
  <<EOF>> {
    *loc = id_loc;
    BEGIN INITIAL;
    return ID;
  }
}


  /*---------------------------------------------------------------.
  | Scanning a Yacc comment.  The initial `/ *' is already eaten.  |
  `---------------------------------------------------------------*/

<SC_YACC_COMMENT>
{
  "*/"     BEGIN context_state;
  .|\n	   ;
  <<EOF>>  unexpected_end_of_file (token_start, "*/");
}


  /*------------------------------------------------------------.
  | Scanning a C comment.  The initial `/ *' is already eaten.  |
  `------------------------------------------------------------*/

<SC_COMMENT>
{
  "*"{splice}"/"  STRING_GROW; BEGIN context_state;
  <<EOF>>	  unexpected_end_of_file (token_start, "*/");
}


  /*--------------------------------------------------------------.
  | Scanning a line comment.  The initial `//' is already eaten.  |
  `--------------------------------------------------------------*/

<SC_LINE_COMMENT>
{
  "\n"		 STRING_GROW; BEGIN context_state;
  {splice}	 STRING_GROW;
  <<EOF>>	 BEGIN context_state;
}


  /*----------------------------------------------------------------.
  | Scanning a C string, including its escapes.  The initial `"' is |
  | already eaten.                                                  |
  `----------------------------------------------------------------*/

<SC_ESCAPED_STRING>
{
  "\"" {
    STRING_GROW;
    STRING_FINISH;
    loc->start = token_start;
    val->chars = last_string;
    rule_length++;
    BEGIN INITIAL;
    return STRING;
  }

  .|\n	    STRING_GROW;
  <<EOF>>   unexpected_end_of_file (token_start, "\"");
}

  /*---------------------------------------------------------------.
  | Scanning a C character, decoding its escapes.  The initial "'" |
  | is already eaten.                                              |
  `---------------------------------------------------------------*/

<SC_ESCAPED_CHARACTER>
{
  "'" {
    unsigned char last_string_1;
    STRING_GROW;
    STRING_FINISH;
    loc->start = token_start;
    val->symbol = symbol_get (last_string, *loc);
    symbol_class_set (val->symbol, token_sym, *loc);
    last_string_1 = last_string[1];
    symbol_user_token_number_set (val->symbol, last_string_1, *loc);
    STRING_FREE;
    rule_length++;
    BEGIN INITIAL;
    return ID;
  }

  .|\n	    STRING_GROW;
  <<EOF>>   unexpected_end_of_file (token_start, "'");
}


  /*----------------------------.
  | Decode escaped characters.  |
  `----------------------------*/

<SC_ESCAPED_STRING,SC_ESCAPED_CHARACTER>
{
  \\[0-7]{1,3} {
    unsigned long c = strtoul (yytext + 1, 0, 8);
    if (UCHAR_MAX < c)
      complain_at (*loc, _("invalid escape sequence: %s"), quote (yytext));
    else
      obstack_1grow (&obstack_for_string, c);
  }

  \\x[0-9abcdefABCDEF]+ {
    unsigned long c;
    set_errno (0);
    c = strtoul (yytext + 2, 0, 16);
    if (UCHAR_MAX < c || get_errno ())
      complain_at (*loc, _("invalid escape sequence: %s"), quote (yytext));
    else
      obstack_1grow (&obstack_for_string, c);
  }

  \\a	obstack_1grow (&obstack_for_string, '\a');
  \\b	obstack_1grow (&obstack_for_string, '\b');
  \\f	obstack_1grow (&obstack_for_string, '\f');
  \\n	obstack_1grow (&obstack_for_string, '\n');
  \\r	obstack_1grow (&obstack_for_string, '\r');
  \\t	obstack_1grow (&obstack_for_string, '\t');
  \\v	obstack_1grow (&obstack_for_string, '\v');

  /* \\[\"\'?\\] would be shorter, but it confuses xgettext.  */
  \\("\""|"'"|"?"|"\\")  obstack_1grow (&obstack_for_string, yytext[1]);

  \\(u|U[0-9abcdefABCDEF]{4})[0-9abcdefABCDEF]{4} {
    int c = convert_ucn_to_byte (yytext);
    if (c < 0)
      complain_at (*loc, _("invalid escape sequence: %s"), quote (yytext));
    else
      obstack_1grow (&obstack_for_string, c);
  }
  \\(.|\n)	{
    complain_at (*loc, _("unrecognized escape sequence: %s"), quote (yytext));
    STRING_GROW;
  }
}


  /*----------------------------------------------------------.
  | Scanning a C character without decoding its escapes.  The |
  | initial "'" is already eaten.                             |
  `----------------------------------------------------------*/

<SC_CHARACTER>
{
  "'"			STRING_GROW; BEGIN context_state;
  \\{splice}[^$@\[\]]	STRING_GROW;
  <<EOF>>		unexpected_end_of_file (token_start, "'");
}


  /*----------------------------------------------------------------.
  | Scanning a C string, without decoding its escapes.  The initial |
  | `"' is already eaten.                                           |
  `----------------------------------------------------------------*/

<SC_STRING>
{
  "\""			STRING_GROW; BEGIN context_state;
  \\{splice}[^$@\[\]]	STRING_GROW;
  <<EOF>>		unexpected_end_of_file (token_start, "\"");
}


  /*---------------------------------------------------.
  | Strings, comments etc. can be found in user code.  |
  `---------------------------------------------------*/

<SC_BRACED_CODE,SC_PROLOGUE,SC_EPILOGUE>
{
  "'" {
    STRING_GROW;
    context_state = YY_START;
    token_start = loc->start;
    BEGIN SC_CHARACTER;
  }
  "\"" {
    STRING_GROW;
    context_state = YY_START;
    token_start = loc->start;
    BEGIN SC_STRING;
  }
  "/"{splice}"*" {
    STRING_GROW;
    context_state = YY_START;
    token_start = loc->start;
    BEGIN SC_COMMENT;
  }
  "/"{splice}"/" {
    STRING_GROW;
    context_state = YY_START;
    BEGIN SC_LINE_COMMENT;
  }
}


  /*---------------------------------------------------------------.
  | Scanning after %union etc., possibly followed by white space.  |
  | For %union only, allow arbitrary C code to appear before the   |
  | following brace, as an extension to POSIX.			   |
  `---------------------------------------------------------------*/

<SC_PRE_CODE>
{
  . {
    bool valid = yytext[0] == '{' || token_type == PERCENT_UNION;
    scanner_cursor.column -= mbsnwidth (yytext, yyleng, 0);
    yyless (0);

    if (valid)
      {
	braces_level = -1;
	code_start = loc->start;
	BEGIN SC_BRACED_CODE;
      }
    else
      {
	complain_at (*loc, _("missing `{' in `%s'"),
		     token_name (token_type));
	obstack_sgrow (&obstack_for_string, "{}");
	STRING_FINISH;
	val->chars = last_string;
	BEGIN INITIAL;
	return token_type;
      }
  }
}


  /*---------------------------------------------------------------.
  | Scanning some code in braces (%union and actions). The initial |
  | "{" is already eaten.                                          |
  `---------------------------------------------------------------*/

<SC_BRACED_CODE>
{
  "{"|"<"{splice}"%"  STRING_GROW; braces_level++;
  "%"{splice}">"      STRING_GROW; braces_level--;
  "}" {
    bool outer_brace = --braces_level < 0;

    /* As an undocumented Bison extension, append `;' before the last
       brace in braced code, so that the user code can omit trailing
       `;'.  But do not append `;' if emulating Yacc, since Yacc does
       not append one.

       FIXME: Bison should warn if a semicolon seems to be necessary
       here, and should omit the semicolon if it seems unnecessary
       (e.g., after ';', '{', or '}', each followed by comments or
       white space).  Such a warning shouldn't depend on --yacc; it
       should depend on a new --pedantic option, which would cause
       Bison to warn if it detects an extension to POSIX.  --pedantic
       should also diagnose other Bison extensions like %yacc.
       Perhaps there should also be a GCC-style --pedantic-errors
       option, so that such warnings are diagnosed as errors.  */
    if (outer_brace && token_type == BRACED_CODE && ! yacc_flag)
      obstack_1grow (&obstack_for_string, ';');

    obstack_1grow (&obstack_for_string, '}');

    if (outer_brace)
      {
	STRING_FINISH;
	rule_length++;
	loc->start = code_start;
	val->chars = last_string;
	BEGIN INITIAL;
	return token_type;
      }
  }

  /* Tokenize `<<%' correctly (as `<<' `%') rather than incorrrectly
     (as `<' `<%').  */
  "<"{splice}"<"  STRING_GROW;

  "$"("<"{tag}">")?(-?[0-9]+|"$")  handle_dollar (token_type, yytext, *loc);
  "@"(-?[0-9]+|"$")		   handle_at (token_type, yytext, *loc);

  <<EOF>>  unexpected_end_of_file (code_start, "}");
}


  /*--------------------------------------------------------------.
  | Scanning some prologue: from "%{" (already scanned) to "%}".  |
  `--------------------------------------------------------------*/

<SC_PROLOGUE>
{
  "%}" {
    STRING_FINISH;
    loc->start = code_start;
    val->chars = last_string;
    BEGIN INITIAL;
    return PROLOGUE;
  }

  <<EOF>>  unexpected_end_of_file (code_start, "%}");
}


  /*---------------------------------------------------------------.
  | Scanning the epilogue (everything after the second "%%", which |
  | has already been eaten).                                       |
  `---------------------------------------------------------------*/

<SC_EPILOGUE>
{
  <<EOF>> {
    STRING_FINISH;
    loc->start = code_start;
    val->chars = last_string;
    BEGIN INITIAL;
    return EPILOGUE;
  }
}


  /*----------------------------------------------------------------.
  | By default, grow the string obstack with the input, escaping M4 |
  | quoting characters.						    |
  `----------------------------------------------------------------*/

<SC_COMMENT,SC_LINE_COMMENT,SC_STRING,SC_CHARACTER,SC_BRACED_CODE,SC_PROLOGUE,SC_EPILOGUE>
{
  \$	obstack_sgrow (&obstack_for_string, "$][");
  \@	obstack_sgrow (&obstack_for_string, "@@");
  \[	obstack_sgrow (&obstack_for_string, "@{");
  \]	obstack_sgrow (&obstack_for_string, "@}");
  .|\n  STRING_GROW;
}


%%

/* Set *LOC and adjust scanner cursor to account for token TOKEN of
   size SIZE.  */

static void
adjust_location (location *loc, char const *token, size_t size)
{
  int line = scanner_cursor.line;
  int column = scanner_cursor.column;
  char const *p0 = token;
  char const *p = token;
  char const *lim = token + size;

  loc->start = scanner_cursor;

  for (p = token; p < lim; p++)
    switch (*p)
      {
      case '\n':
	line++;
	column = 1;
	p0 = p + 1;
	break;

      case '\t':
	column += mbsnwidth (p0, p - p0, 0);
	column += 8 - ((column - 1) & 7);
	p0 = p + 1;
	break;
      }

  scanner_cursor.line = line;
  scanner_cursor.column = column + mbsnwidth (p0, p - p0, 0);

  loc->end = scanner_cursor;
}


/* Read bytes from FP into buffer BUF of size SIZE.  Return the
   number of bytes read.  Remove '\r' from input, treating \r\n
   and isolated \r as \n.  */

static size_t
no_cr_read (FILE *fp, char *buf, size_t size)
{
  size_t s = fread (buf, 1, size, fp);
  if (s)
    {
      char *w = memchr (buf, '\r', s);
      if (w)
	{
	  char const *r = ++w;
	  char const *lim = buf + s;

	  for (;;)
	    {
	      /* Found an '\r'.  Treat it like '\n', but ignore any
		 '\n' that immediately follows.  */
	      w[-1] = '\n';
	      if (r == lim)
		{
		  int ch = getc (fp);
		  if (ch != '\n' && ungetc (ch, fp) != ch)
		    break;
		}
	      else if (*r == '\n')
		r++;

	      /* Copy until the next '\r'.  */
	      do
		{
		  if (r == lim)
		    return w - buf;
		}
	      while ((*w++ = *r++) != '\r');
	    }

	  return w - buf;
	}
    }

  return s;
}


/*------------------------------------------------------------------.
| TEXT is pointing to a wannabee semantic value (i.e., a `$').      |
|                                                                   |
| Possible inputs: $[<TYPENAME>]($|integer)                         |
|                                                                   |
| Output to OBSTACK_FOR_STRING a reference to this semantic value.  |
`------------------------------------------------------------------*/

static inline bool
handle_action_dollar (char *text, location loc)
{
  const char *type_name = NULL;
  char *cp = text + 1;

  if (! current_rule)
    return false;

  /* Get the type name if explicit. */
  if (*cp == '<')
    {
      type_name = ++cp;
      while (*cp != '>')
	++cp;
      *cp = '\0';
      ++cp;
    }

  if (*cp == '$')
    {
      if (!type_name)
	type_name = symbol_list_n_type_name_get (current_rule, loc, 0);
      if (!type_name && typed)
	complain_at (loc, _("$$ of `%s' has no declared type"),
		     current_rule->sym->tag);
      if (!type_name)
	type_name = "";
      obstack_fgrow1 (&obstack_for_string,
		      "]b4_lhs_value([%s])[", type_name);
    }
  else
    {
      long num;
      set_errno (0);
      num = strtol (cp, 0, 10);

      if (INT_MIN <= num && num <= rule_length && ! get_errno ())
	{
	  int n = num;
	  if (!type_name && n > 0)
	    type_name = symbol_list_n_type_name_get (current_rule, loc, n);
	  if (!type_name && typed)
	    complain_at (loc, _("$%d of `%s' has no declared type"),
			 n, current_rule->sym->tag);
	  if (!type_name)
	    type_name = "";
	  obstack_fgrow3 (&obstack_for_string,
			  "]b4_rhs_value([%d], [%d], [%s])[",
			  rule_length, n, type_name);
	}
      else
	complain_at (loc, _("integer out of range: %s"), quote (text));
    }

  return true;
}


/*-----------------------------------------------------------------.
| Dispatch onto handle_action_dollar, or handle_destructor_dollar, |
| depending upon TOKEN_TYPE.                                       |
`-----------------------------------------------------------------*/

static void
handle_dollar (int token_type, char *text, location loc)
{
  switch (token_type)
    {
    case BRACED_CODE:
      if (handle_action_dollar (text, loc))
	return;
      break;

    case PERCENT_DESTRUCTOR:
    case PERCENT_PRINTER:
      if (text[1] == '$')
	{
	  obstack_sgrow (&obstack_for_string, "]b4_dollar_dollar[");
	  return;
	}
      break;

    default:
      break;
    }

  complain_at (loc, _("invalid value: %s"), quote (text));
}


/*------------------------------------------------------.
| TEXT is a location token (i.e., a `@...').  Output to |
| OBSTACK_FOR_STRING a reference to this location.      |
`------------------------------------------------------*/

static inline bool
handle_action_at (char *text, location loc)
{
  char *cp = text + 1;
  locations_flag = 1;

  if (! current_rule)
    return false;

  if (*cp == '$')
    obstack_sgrow (&obstack_for_string, "]b4_lhs_location[");
  else
    {
      long num;
      set_errno (0);
      num = strtol (cp, 0, 10);

      if (INT_MIN <= num && num <= rule_length && ! get_errno ())
	{
	  int n = num;
	  obstack_fgrow2 (&obstack_for_string, "]b4_rhs_location([%d], [%d])[",
			  rule_length, n);
	}
      else
	complain_at (loc, _("integer out of range: %s"), quote (text));
    }

  return true;
}


/*-------------------------------------------------------------------.
| Dispatch onto handle_action_at, or handle_destructor_at, depending |
| upon CODE_KIND.                                                    |
`-------------------------------------------------------------------*/

static void
handle_at (int token_type, char *text, location loc)
{
  switch (token_type)
    {
    case BRACED_CODE:
      handle_action_at (text, loc);
      return;

    case PERCENT_DESTRUCTOR:
    case PERCENT_PRINTER:
      if (text[1] == '$')
	{
	  obstack_sgrow (&obstack_for_string, "]b4_at_dollar[");
	  return;
	}
      break;

    default:
      break;
    }

  complain_at (loc, _("invalid value: %s"), quote (text));
}


/*------------------------------------------------------------------.
| Convert universal character name UCN to a single-byte character,  |
| and return that character.  Return -1 if UCN does not correspond  |
| to a single-byte character.					    |
`------------------------------------------------------------------*/

static int
convert_ucn_to_byte (char const *ucn)
{
  unsigned long code = strtoul (ucn + 2, 0, 16);

  /* FIXME: Currently we assume Unicode-compatible unibyte characters
     on ASCII hosts (i.e., Latin-1 on hosts with 8-bit bytes).  On
     non-ASCII hosts we support only the portable C character set.
     These limitations should be removed once we add support for
     multibyte characters.  */

  if (UCHAR_MAX < code)
    return -1;

#if ! ('$' == 0x24 && '@' == 0x40 && '`' == 0x60 && '~' == 0x7e)
  {
    /* A non-ASCII host.  Use CODE to index into a table of the C
       basic execution character set, which is guaranteed to exist on
       all Standard C platforms.  This table also includes '$', '@',
       and '`', which are not in the basic execution character set but
       which are unibyte characters on all the platforms that we know
       about.  */
    static signed char const table[] =
      {
	'\0',   -1,   -1,   -1,   -1,   -1,   -1, '\a',
	'\b', '\t', '\n', '\v', '\f', '\r',   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	 ' ',  '!',  '"',  '#',  '$',  '%',  '&', '\'',
	 '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
	 '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',
	 '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
	 '@',  'A',  'B',  'C',  'D',  'E',  'F',  'G',
	 'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
	 'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',
	 'X',  'Y',  'Z',  '[', '\\',  ']',  '^',  '_',
	 '`',  'a',  'b',  'c',  'd',  'e',  'f',  'g',
	 'h',  'i',  'j',  'k',  'l',  'm',  'n',  'o',
	 'p',  'q',  'r',  's',  't',  'u',  'v',  'w',
	 'x',  'y',  'z',  '{',  '|',  '}',  '~'
      };

    code = code < sizeof table ? table[code] : -1;
  }
#endif

  return code;
}


/*----------------------------------------------------------------.
| Handle `#line INT "FILE"'.  ARGS has already skipped `#line '.  |
`----------------------------------------------------------------*/

static void
handle_syncline (char *args)
{
  int lineno = strtol (args, &args, 10);
  const char *file = NULL;
  file = strchr (args, '"') + 1;
  *strchr (file, '"') = 0;
  scanner_cursor.file = current_file = xstrdup (file);
  scanner_cursor.line = lineno;
  scanner_cursor.column = 1;
}


/*------------------------------------------------------------------------.
| Report an unexpected EOF in a token or comment starting at START.       |
| An end of file was encountered and the expected TOKEN_END was missing.  |
| After reporting the problem, pretend that TOKEN_END was found.          |
`------------------------------------------------------------------------*/

static void
unexpected_end_of_file (boundary start, char const *token_end)
{
  size_t i = strlen (token_end);

  location loc;
  loc.start = start;
  loc.end = scanner_cursor;
  complain_at (loc, _("missing `%s' at end of file"), token_end);

  /* Adjust scanner cursor so that any later message does not count
     the characters about to be inserted.  */
  scanner_cursor.column -= i;

  while (i != 0)
    unput (token_end[--i]);
}


/*-------------------------.
| Initialize the scanner.  |
`-------------------------*/

void
scanner_initialize (void)
{
  obstack_init (&obstack_for_string);
}


/*-----------------------------------------------.
| Free all the memory allocated to the scanner.  |
`-----------------------------------------------*/

void
scanner_free (void)
{
  obstack_free (&obstack_for_string, 0);
  /* Reclaim Flex's buffers.  */
  yy_delete_buffer (YY_CURRENT_BUFFER);
}
