/* Output the generated parsing program for Bison.

   Copyright (C) 1984, 1986, 1989, 1992, 2000, 2001, 2002
   Free Software Foundation, Inc.

   This file is part of Bison, the GNU Compiler Compiler.

   Bison is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   Bison is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Bison; see the file COPYING.  If not, write to the Free
   Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
   02111-1307, USA.  */


#include "system.h"

#include <error.h>
#include <get-errno.h>
#include <quotearg.h>
#include <subpipe.h>
#include <timevar.h>

#include "complain.h"
#include "files.h"
#include "getargs.h"
#include "gram.h"
#include "muscle_tab.h"
#include "output.h"
#include "reader.h"
#include "symtab.h"
#include "tables.h"

/* From src/scan-skel.l. */
void scan_skel (FILE *);


static struct obstack format_obstack;

int error_verbose = 0;



/*-------------------------------------------------------------------.
| Create a function NAME which associates to the muscle NAME the     |
| result of formatting the FIRST and then TABLE_DATA[BEGIN..END[ (of |
| TYPE), and to the muscle NAME_max, the max value of the            |
| TABLE_DATA.                                                        |
`-------------------------------------------------------------------*/


#define GENERATE_MUSCLE_INSERT_TABLE(Name, Type)			\
									\
static void								\
Name (const char *name,							\
      Type *table_data,							\
      Type first,							\
      int begin,							\
      int end)								\
{									\
  Type min = first;							\
  Type max = first;							\
  long int lmin;							\
  long int lmax;							\
  int i;								\
  int j = 1;								\
									\
  obstack_fgrow1 (&format_obstack, "%6d", first);			\
  for (i = begin; i < end; ++i)						\
    {									\
      obstack_1grow (&format_obstack, ',');				\
      if (j >= 10)							\
	{								\
	  obstack_sgrow (&format_obstack, "\n  ");			\
	  j = 1;							\
	}								\
      else								\
	++j;								\
      obstack_fgrow1 (&format_obstack, "%6d", table_data[i]);		\
      if (table_data[i] < min)						\
	min = table_data[i];						\
      if (max < table_data[i])						\
	max = table_data[i];						\
    }									\
  obstack_1grow (&format_obstack, 0);					\
  muscle_insert (name, obstack_finish (&format_obstack));		\
									\
  lmin = min;								\
  lmax = max;								\
  /* Build `NAME_min' and `NAME_max' in the obstack. */			\
  obstack_fgrow1 (&format_obstack, "%s_min", name);			\
  obstack_1grow (&format_obstack, 0);					\
  MUSCLE_INSERT_LONG_INT (obstack_finish (&format_obstack), lmin);	\
  obstack_fgrow1 (&format_obstack, "%s_max", name);			\
  obstack_1grow (&format_obstack, 0);					\
  MUSCLE_INSERT_LONG_INT (obstack_finish (&format_obstack), lmax);	\
}

GENERATE_MUSCLE_INSERT_TABLE(muscle_insert_unsigned_int_table, unsigned int)
GENERATE_MUSCLE_INSERT_TABLE(muscle_insert_int_table, int)
GENERATE_MUSCLE_INSERT_TABLE(muscle_insert_short_table, short)
GENERATE_MUSCLE_INSERT_TABLE(muscle_insert_base_table, base_number)
GENERATE_MUSCLE_INSERT_TABLE(muscle_insert_rule_number_table, rule_number)
GENERATE_MUSCLE_INSERT_TABLE(muscle_insert_symbol_number_table, symbol_number)
GENERATE_MUSCLE_INSERT_TABLE(muscle_insert_item_number_table, item_number)
GENERATE_MUSCLE_INSERT_TABLE(muscle_insert_state_number_table, state_number)


/*----------------------------------------------------------------------.
| Print to OUT a representation of FILENAME escaped both for C and M4.  |
`----------------------------------------------------------------------*/

static void
escaped_file_name_output (FILE *out, char const *filename)
{
  char const *p;
  fprintf (out, "[[");

  for (p = quotearg_style (c_quoting_style, filename); *p; p++)
    switch (*p)
      {
      case '$': fputs ("$][", out); break;
      case '@': fputs ("@@",  out); break;
      case '[': fputs ("@{",  out); break;
      case ']': fputs ("@}",  out); break;
      default: fputc (*p, out); break;
      }

  fprintf (out, "]]");
}


/*------------------------------------------------------------------.
| Prepare the muscles related to the symbols: translate, tname, and |
| toknum.                                                           |
`------------------------------------------------------------------*/

static void
prepare_symbols (void)
{
  MUSCLE_INSERT_INT ("tokens_number", ntokens);
  MUSCLE_INSERT_INT ("nterms_number", nvars);
  MUSCLE_INSERT_INT ("undef_token_number", undeftoken->number);
  MUSCLE_INSERT_INT ("user_token_number_max", max_user_token_number);

  muscle_insert_symbol_number_table ("translate",
				     token_translations,
				     token_translations[0],
				     1, max_user_token_number + 1);

  /* tname -- token names.  */
  {
    int i;
    int j = 0;
    for (i = 0; i < nsyms; i++)
      {
	/* Be sure not to use twice the same QUOTEARG slot:
	   SYMBOL_TAG_GET uses slot 0.  */
	const char *cp =
	  quotearg_n_style (1, c_quoting_style,
			    symbols[i]->tag);
	/* Width of the next token, including the two quotes, the comma
	   and the space.  */
	int width = strlen (cp) + 2;

	if (j + width > 75)
	  {
	    obstack_sgrow (&format_obstack, "\n  ");
	    j = 2;
	  }

	MUSCLE_OBSTACK_SGROW (&format_obstack, cp);
	obstack_sgrow (&format_obstack, ", ");
	j += width;
      }
    /* Add a NULL entry to list of tokens (well, 0, as NULL might not be
       defined).  */
    obstack_sgrow (&format_obstack, "0");

    /* Finish table and store. */
    obstack_1grow (&format_obstack, 0);
    muscle_insert ("tname", obstack_finish (&format_obstack));
  }

  /* Output YYTOKNUM. */
  {
    int i;
    int *values = MALLOC (values, ntokens);
    for (i = 0; i < ntokens; ++i)
      values[i] = symbols[i]->user_token_number;
    muscle_insert_int_table ("toknum", values,
			     values[0], 1, ntokens);
    free (values);
  }
}


/*-------------------------------------------------------------.
| Prepare the muscles related to the rules: rhs, prhs, r1, r2, |
| rline, dprec, merger.                                        |
`-------------------------------------------------------------*/

static void
prepare_rules (void)
{
  rule_number r;
  unsigned int i = 0;
  item_number *rhs = MALLOC (rhs, nritems);
  unsigned int *prhs = MALLOC (prhs, nrules);
  unsigned int *rline = MALLOC (rline, nrules);
  symbol_number *r1 = MALLOC (r1, nrules);
  unsigned int *r2 = MALLOC (r2, nrules);
  short *dprec = MALLOC (dprec, nrules);
  short *merger = MALLOC (merger, nrules);

  for (r = 0; r < nrules; ++r)
    {
      item_number *rhsp = NULL;
      /* Index of rule R in RHS. */
      prhs[r] = i;
      /* RHS of the rule R. */
      for (rhsp = rules[r].rhs; *rhsp >= 0; ++rhsp)
	rhs[i++] = *rhsp;
      /* LHS of the rule R. */
      r1[r] = rules[r].lhs->number;
      /* Length of rule R's RHS. */
      r2[r] = i - prhs[r];
      /* Separator in RHS. */
      rhs[i++] = -1;
      /* Line where rule was defined. */
      rline[r] = rules[r].location.start.line;
      /* Dynamic precedence (GLR).  */
      dprec[r] = rules[r].dprec;
      /* Merger-function index (GLR).  */
      merger[r] = rules[r].merger;
    }
  if (i != nritems)
    abort ();

  muscle_insert_item_number_table ("rhs", rhs, ritem[0], 1, nritems);
  muscle_insert_unsigned_int_table ("prhs", prhs, 0, 0, nrules);
  muscle_insert_unsigned_int_table ("rline", rline, 0, 0, nrules);
  muscle_insert_symbol_number_table ("r1", r1, 0, 0, nrules);
  muscle_insert_unsigned_int_table ("r2", r2, 0, 0, nrules);
  muscle_insert_short_table ("dprec", dprec, 0, 0, nrules);
  muscle_insert_short_table ("merger", merger, 0, 0, nrules);

  MUSCLE_INSERT_INT ("rules_number", nrules);

  free (rhs);
  free (prhs);
  free (rline);
  free (r1);
  free (r2);
  free (dprec);
  free (merger);
}

/*--------------------------------------------.
| Prepare the muscles related to the states.  |
`--------------------------------------------*/

static void
prepare_states (void)
{
  state_number i;
  symbol_number *values = MALLOC (values, nstates);
  for (i = 0; i < nstates; ++i)
    values[i] = states[i]->accessing_symbol;
  muscle_insert_symbol_number_table ("stos", values,
				     0, 1, nstates);
  free (values);

  MUSCLE_INSERT_INT ("last", high);
  MUSCLE_INSERT_INT ("final_state_number", final_state->number);
  MUSCLE_INSERT_INT ("states_number", nstates);
}



/*---------------------------------.
| Output the user actions to OUT.  |
`---------------------------------*/

static void
user_actions_output (FILE *out)
{
  rule_number r;

  fputs ("m4_define([b4_actions], \n[[", out);
  for (r = 0; r < nrules; ++r)
    if (rules[r].action)
      {
	fprintf (out, "  case %d:\n", r + 1);

	fprintf (out, "]b4_syncline([[%d]], ",
		 rules[r].action_location.start.line);
	escaped_file_name_output (out, rules[r].action_location.start.file);
	fprintf (out, ")[\n");
	fprintf (out, "    %s\n    break;\n\n",
		 rules[r].action);
      }
  fputs ("]])\n\n", out);
}

/*--------------------------------------.
| Output the merge functions to OUT.   |
`--------------------------------------*/

static void
merger_output (FILE *out)
{
  int n;
  merger_list* p;

  fputs ("m4_define([b4_mergers], \n[[", out);
  for (n = 1, p = merge_functions; p != NULL; n += 1, p = p->next)
    {
      if (p->type[0] == '\0')
	fprintf (out, "  case %d: yyval = %s (*yy0, *yy1); break;\n",
		 n, p->name);
      else
	fprintf (out, "  case %d: yyval.%s = %s (*yy0, *yy1); break;\n",
		 n, p->type, p->name);
    }
  fputs ("]])\n\n", out);
}

/*--------------------------------------.
| Output the tokens definition to OUT.  |
`--------------------------------------*/

static void
token_definitions_output (FILE *out)
{
  int i;
  int first = 1;

  fputs ("m4_define([b4_tokens], \n[", out);
  for (i = 0; i < ntokens; ++i)
    {
      symbol *sym = symbols[i];
      int number = sym->user_token_number;

      /* At this stage, if there are literal aliases, they are part of
	 SYMBOLS, so we should not find symbols which are the aliases
	 here.  */
      if (number == USER_NUMBER_ALIAS)
	abort ();

      /* Skip error token.  */
      if (sym == errtoken)
	continue;

      /* If this string has an alias, then it is necessarily the alias
	 which is to be output.  */
      if (sym->alias)
	sym = sym->alias;

      /* Don't output literal chars or strings (when defined only as a
	 string).  Note that must be done after the alias resolution:
	 think about `%token 'f' "f"'.  */
      if (sym->tag[0] == '\'' || sym->tag[0] == '\"')
	continue;

      /* Don't #define nonliteral tokens whose names contain periods
	 or '$' (as does the default value of the EOF token).  */
      if (strchr (sym->tag, '.') || strchr (sym->tag, '$'))
	continue;

      fprintf (out, "%s[[[%s]], [%d]]",
	       first ? "" : ",\n", sym->tag, number);

      first = 0;
    }
  fputs ("])\n\n", out);
}


/*---------------------------------------.
| Output the symbol destructors to OUT.  |
`---------------------------------------*/

static void
symbol_destructors_output (FILE *out)
{
  int i;
  int first = 1;

  fputs ("m4_define([b4_symbol_destructors], \n[", out);
  for (i = 0; i < nsyms; ++i)
    if (symbols[i]->destructor)
      {
	symbol *sym = symbols[i];

	/* Filename, lineno,
	   Symbol-name, Symbol-number,
	   destructor, typename. */
	fprintf (out, "%s[",
		 first ? "" : ",\n");
	escaped_file_name_output (out, sym->destructor_location.start.file);
	fprintf (out, ", [[%d]], [[%s]], [[%d]], [[%s]], [[%s]]]",
		 sym->destructor_location.start.line,
		 sym->tag,
		 sym->number,
		 sym->destructor,
		 sym->type_name);

	first = 0;
      }
  fputs ("])\n\n", out);
}


/*------------------------------------.
| Output the symbol printers to OUT.  |
`------------------------------------*/

static void
symbol_printers_output (FILE *out)
{
  int i;
  int first = 1;

  fputs ("m4_define([b4_symbol_printers], \n[", out);
  for (i = 0; i < nsyms; ++i)
    if (symbols[i]->destructor)
      {
	symbol *sym = symbols[i];

	/* Filename, lineno,
	   Symbol-name, Symbol-number,
	   printer, typename. */
	fprintf (out, "%s[",
		 first ? "" : ",\n");
	escaped_file_name_output (out, sym->printer_location.start.file);
	fprintf (out, ", [[%d]], [[%s]], [[%d]], [[%s]], [[%s]]]",
		 sym->printer_location.start.line,
		 sym->tag,
		 sym->number,
		 sym->printer,
		 sym->type_name);

	first = 0;
      }
  fputs ("])\n\n", out);
}


static void
prepare_actions (void)
{
  /* Figure out the actions for the specified state, indexed by
     lookahead token type.  */

  muscle_insert_rule_number_table ("defact", yydefact,
				   yydefact[0], 1, nstates);

  /* Figure out what to do after reducing with each rule, depending on
     the saved state from before the beginning of parsing the data
     that matched this rule.  */
  muscle_insert_state_number_table ("defgoto", yydefgoto,
				    yydefgoto[0], 1, nsyms - ntokens);


  /* Output PACT. */
  muscle_insert_base_table ("pact", base,
			     base[0], 1, nstates);
  MUSCLE_INSERT_INT ("pact_ninf", base_ninf);

  /* Output PGOTO. */
  muscle_insert_base_table ("pgoto", base,
			     base[nstates], nstates + 1, nvectors);

  muscle_insert_base_table ("table", table,
			    table[0], 1, high + 1);
  MUSCLE_INSERT_INT ("table_ninf", table_ninf);

  muscle_insert_base_table ("check", check,
			    check[0], 1, high + 1);

  /* GLR parsing slightly modifies YYTABLE and YYCHECK (and thus
     YYPACT) so that in states with unresolved conflicts, the default
     reduction is not used in the conflicted entries, so that there is
     a place to put a conflict pointer.

     This means that YYCONFLP and YYCONFL are nonsense for a non-GLR
     parser, so we could avoid accidents by not writing them out in
     that case.  Nevertheless, it seems even better to be able to use
     the GLR skeletons even without the non-deterministic tables.  */
  muscle_insert_unsigned_int_table ("conflict_list_heads", conflict_table,
				    conflict_table[0], 1, high + 1);
  muscle_insert_unsigned_int_table ("conflicting_rules", conflict_list,
				    conflict_list[0], 1, conflict_list_cnt);
}


/*---------------------------.
| Call the skeleton parser.  |
`---------------------------*/

static void
output_skeleton (void)
{
  FILE *in;
  FILE *out;
  int filter_fd[2];
  char const *argv[6];
  pid_t pid;

  /* Compute the names of the package data dir and skeleton file.
     Test whether m4sugar.m4 is readable, to check for proper
     installation.  A faulty installation can cause deadlock, so a
     cheap sanity check is worthwhile.  */
  char const m4sugar[] = "m4sugar/m4sugar.m4";
  char *full_m4sugar;
  char *full_cm4;
  char *full_path;
  char const *p;
  char const *m4 = (p = getenv ("M4")) ? p : M4;
  char const *pkgdatadir = (p = getenv ("BISON_PKGDATADIR")) ? p : PKGDATADIR;
  size_t skeleton_size = strlen (skeleton) + 1;
  size_t pkgdatadirlen = strlen (pkgdatadir);
  while (pkgdatadirlen && pkgdatadir[pkgdatadirlen - 1] == '/')
    pkgdatadirlen--;
  full_path = xmalloc (pkgdatadirlen + 1
		       + (skeleton_size < sizeof m4sugar
			  ? sizeof m4sugar : skeleton_size));
  strcpy (full_path, pkgdatadir);
  full_path[pkgdatadirlen] = '/';
  strcpy (full_path + pkgdatadirlen + 1, m4sugar);
  full_m4sugar = xstrdup (full_path);
  strcpy (full_path + pkgdatadirlen + 1, "c.m4");
  full_cm4 = xstrdup (full_path);
  strcpy (full_path + pkgdatadirlen + 1, skeleton);
  xfclose (xfopen (full_m4sugar, "r"));

  /* Create an m4 subprocess connected to us via two pipes.  */

  if (trace_flag & trace_tools)
    fprintf (stderr, "running: %s %s - %s %s\n",
	     m4, full_m4sugar, full_cm4, full_path);

  argv[0] = m4;
  argv[1] = full_m4sugar;
  argv[2] = "-";
  argv[3] = full_cm4;
  argv[4] = full_path;
  argv[5] = NULL;

  init_subpipe ();
  pid = create_subpipe (argv, filter_fd);
  free (full_m4sugar);
  free (full_cm4);
  free (full_path);

  out = fdopen (filter_fd[0], "w");
  if (! out)
    error (EXIT_FAILURE, get_errno (), "fdopen");

  /* Output the definitions of all the muscles.  */
  fputs ("m4_init()\n", out);

  user_actions_output (out);
  merger_output (out);
  token_definitions_output (out);
  symbol_destructors_output (out);
  symbol_printers_output (out);

  muscles_m4_output (out);

  fputs ("m4_wrap([m4_divert_pop(0)])\n", out);
  fputs ("m4_divert_push(0)dnl\n", out);
  xfclose (out);

  /* Read and process m4's output.  */
  timevar_push (TV_M4);
  in = fdopen (filter_fd[1], "r");
  if (! in)
    error (EXIT_FAILURE, get_errno (), "fdopen");
  scan_skel (in);
  xfclose (in);
  reap_subpipe (pid, m4);
  timevar_pop (TV_M4);
}

static void
prepare (void)
{
  /* Flags. */
  MUSCLE_INSERT_INT ("debug", debug_flag);
  MUSCLE_INSERT_INT ("defines_flag", defines_flag);
  MUSCLE_INSERT_INT ("error_verbose", error_verbose);
  MUSCLE_INSERT_INT ("locations_flag", locations_flag);
  MUSCLE_INSERT_INT ("pure", pure_parser);
  MUSCLE_INSERT_INT ("synclines_flag", !no_lines_flag);

  /* File names.  */
  MUSCLE_INSERT_STRING ("prefix", spec_name_prefix ? spec_name_prefix : "yy");

  /* User Code.  */
  obstack_1grow (&pre_prologue_obstack, 0);
  obstack_1grow (&post_prologue_obstack, 0);
  muscle_insert ("pre_prologue", obstack_finish (&pre_prologue_obstack));
  muscle_insert ("post_prologue", obstack_finish (&post_prologue_obstack));

  /* Find the right skeleton file.  */
  if (!skeleton)
    {
      if (glr_parser)
	skeleton = "glr.c";
      else
	skeleton = "yacc.c";
    }

  /* Parse the skeleton file and output the needed parsers.  */
  MUSCLE_INSERT_C_STRING ("skeleton", skeleton);
}


/*----------------------------------------------------------.
| Output the parsing tables and the parser code to ftable.  |
`----------------------------------------------------------*/

void
output (void)
{
  obstack_init (&format_obstack);

  prepare_symbols ();
  prepare_rules ();
  prepare_states ();
  prepare_actions ();

  prepare ();

  /* Process the selected skeleton file.  */
  output_skeleton ();

  obstack_free (&format_obstack, NULL);
  obstack_free (&pre_prologue_obstack, NULL);
  obstack_free (&post_prologue_obstack, NULL);
}
