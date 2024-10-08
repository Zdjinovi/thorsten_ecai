/* Input parser for Bison

   Copyright (C) 2000, 2001, 2002 Free Software Foundation, Inc.

   This file is part of Bison, the GNU Compiler Compiler.

   Bison is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   Bison is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Bison; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

#ifndef READER_H_
# define READER_H_

# include "location.h"
# include "symlist.h"

# include "parse-gram.h"

typedef struct merger_list
{
  struct merger_list* next;
  uniqstr name;
  uniqstr type;
} merger_list;

/* From the scanner.  */
extern FILE *gram_in;
extern int gram__flex_debug;
extern boundary scanner_cursor;
void scanner_initialize (void);
void scanner_free (void);
void scanner_last_string_free (void);

# define YY_DECL int gram_lex (YYSTYPE *val, location *loc)
YY_DECL;


/* From the parser.  */
extern int gram_debug;
int gram_parse (void);
char const *token_name (int);


/* From reader.c. */
void grammar_start_symbol_set (symbol *s, location loc);
void prologue_augment (const char *prologue, location loc);
void epilogue_augment (const char *epilogue, location loc);
void grammar_symbol_append (symbol *s, location loc);
void grammar_rule_begin (symbol *lhs, location loc);
void grammar_rule_end (location loc);
void grammar_midrule_action (void);
void grammar_current_rule_prec_set (symbol *precsym, location loc);
void grammar_current_rule_dprec_set (int dprec, location loc);
void grammar_current_rule_merge_set (uniqstr name, location loc);

void grammar_current_rule_symbol_append (symbol *sym, location loc);
void grammar_current_rule_action_append (const char *action, location loc);
extern symbol_list *current_rule;
void reader (void);
void free_merger_functions (void);

extern merger_list *merge_functions;

extern int typed;

#endif /* !READER_H_ */
