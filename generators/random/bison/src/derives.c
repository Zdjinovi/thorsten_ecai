/* Match rules with nonterminals for bison,

   Copyright (C) 1984, 1989, 2000, 2001, 2002 Free Software
   Foundation, Inc.

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


#include "system.h"

#include "getargs.h"

#include "derives.h"
#include "gram.h"
#include "reader.h"
#include "symtab.h"

/* Linked list of rule numbers.  */
typedef struct rule_list
{
  struct rule_list *next;
  rule *value;
} rule_list;

rule ***derives = NULL;

static void
print_derives (void)
{
  int i;

  fputs ("DERIVES\n", stderr);

  for (i = ntokens; i < nsyms; i++)
    {
      rule **rp;
      fprintf (stderr, "\t%s derives\n", symbols[i]->tag);
      for (rp = derives[i - ntokens]; *rp; ++rp)
	{
	  fprintf (stderr, "\t\t%3d ", (*rp)->user_number);
	  rule_rhs_print (*rp, stderr);
	}
    }

  fputs ("\n\n", stderr);
}


void
derives_compute (void)
{
  symbol_number i;
  int r;
  rule **q;

  /* DSET[NTERM - NTOKENS] -- A linked list of the numbers of the rules
     whose LHS is NTERM.  */
  rule_list **dset = CALLOC (dset, nvars);

  /* DELTS[RULE] -- There are NRULES rule number to attach to nterms.
     Instead of performing NRULES allocations for each, have an array
     indexed by rule numbers.  */
  rule_list *delts = CALLOC (delts, nrules);

  for (r = nrules - 1; r >= 0; --r)
    {
      symbol_number lhs = rules[r].lhs->number;
      rule_list *p = &delts[r];
      /* A new LHS is found.  */
      p->next = dset[lhs - ntokens];
      p->value = &rules[r];
      dset[lhs - ntokens] = p;
    }

  /* DSET contains what we need under the form of a linked list.  Make
     it a single array.  */

  CALLOC (derives, nvars);
  CALLOC (q, nvars + nrules);

  for (i = ntokens; i < nsyms; i++)
    {
      rule_list *p = dset[i - ntokens];
      derives[i - ntokens] = q;
      while (p)
	{
	  *q++ = p->value;
	  p = p->next;
	}
      *q++ = NULL;
    }

  if (trace_flag & trace_sets)
    print_derives ();

  free (dset);
  free (delts);
}


void
derives_free (void)
{
  XFREE (derives[0]);
  XFREE (derives);
}
