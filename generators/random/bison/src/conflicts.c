/* Find and resolve or report look-ahead conflicts for bison,

   Copyright (C) 1984, 1989, 1992, 2000, 2001, 2002
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

#include <bitset.h>

#include "LR0.h"
#include "complain.h"
#include "conflicts.h"
#include "files.h"
#include "getargs.h"
#include "gram.h"
#include "lalr.h"
#include "reader.h"
#include "state.h"
#include "symtab.h"

/* -1 stands for not specified. */
int expected_conflicts = -1;
static char *conflicts = NULL;
struct obstack solved_conflicts_obstack;

static bitset shiftset;
static bitset lookaheadset;



enum conflict_resolution
  {
    shift_resolution,
    reduce_resolution,
    left_resolution,
    right_resolution,
    nonassoc_resolution
  };


/*----------------------------------------------------------------.
| Explain how an SR conflict between TOKEN and RULE was resolved: |
| RESOLUTION.                                                     |
`----------------------------------------------------------------*/

static inline void
log_resolution (rule *r, symbol_number token,
		enum conflict_resolution resolution)
{
  if (report_flag & report_solved_conflicts)
    {
      /* The description of the resolution. */
      switch (resolution)
	{
	case shift_resolution:
	case right_resolution:
	  obstack_fgrow2 (&solved_conflicts_obstack,
			  _("\
    Conflict between rule %d and token %s resolved as shift"),
			  r->number,
			  symbols[token]->tag);
	  break;
	case reduce_resolution:
	case left_resolution:
	  obstack_fgrow2 (&solved_conflicts_obstack,
			  _("\
    Conflict between rule %d and token %s resolved as reduce"),
			  r->number,
			  symbols[token]->tag);
	  break;
	case nonassoc_resolution:
	  obstack_fgrow2 (&solved_conflicts_obstack,
			  _("\
    Conflict between rule %d and token %s resolved as an error"),
			  r->number,
			  symbols[token]->tag);
	  break;
	}

      /* The reason. */
      switch (resolution)
	{
	case shift_resolution:
	  obstack_fgrow2 (&solved_conflicts_obstack,
			  " (%s < %s)",
			  r->prec->tag,
			  symbols[token]->tag);
	  break;

	case reduce_resolution:
	  obstack_fgrow2 (&solved_conflicts_obstack,
			  " (%s < %s)",
			  symbols[token]->tag,
			  r->prec->tag);
	  break;

	case left_resolution:
	  obstack_fgrow1 (&solved_conflicts_obstack,
			  " (%%left %s)",
			  symbols[token]->tag);
	  break;

	case right_resolution:
	  obstack_fgrow1 (&solved_conflicts_obstack,
			  " (%%right %s)",
			  symbols[token]->tag);
	  break;
	case nonassoc_resolution:
	  obstack_fgrow1 (&solved_conflicts_obstack,
			  " (%%nonassoc %s)",
			  symbols[token]->tag);
	  break;
	}
      obstack_sgrow (&solved_conflicts_obstack, ".\n");
    }
}


/*------------------------------------------------------------------.
| Turn off the shift recorded for the specified token in the        |
| specified state.  Used when we resolve a shift-reduce conflict in |
| favor of the reduction.                                           |
`------------------------------------------------------------------*/

static void
flush_shift (state *s, int token)
{
  transitions *trans = s->transitions;
  int i;

  bitset_reset (lookaheadset, token);
  for (i = 0; i < trans->num; i++)
    if (!TRANSITION_IS_DISABLED (trans, i)
	&& TRANSITION_SYMBOL (trans, i) == token)
      TRANSITION_DISABLE (trans, i);
}


/*-------------------------------------------------------------------.
| Turn off the reduce recorded for the specified token for the       |
| specified lookahead.  Used when we resolve a shift-reduce conflict |
| in favor of the shift.                                             |
`-------------------------------------------------------------------*/

static void
flush_reduce (bitset lookaheads, int token)
{
  bitset_reset (lookaheads, token);
}


/*------------------------------------------------------------------.
| Attempt to resolve shift-reduce conflict for one rule by means of |
| precedence declarations.  It has already been checked that the    |
| rule has a precedence.  A conflict is resolved by modifying the   |
| shift or reduce tables so that there is no longer a conflict.     |
|                                                                   |
| LOOKAHEAD is the number of the lookahead bitset to consider.      |
|                                                                   |
| ERRORS can be used to store discovered explicit errors.           |
`------------------------------------------------------------------*/

static void
resolve_sr_conflict (state *s, int ruleno, symbol **errors)
{
  symbol_number i;
  reductions *reds = s->reductions;
  /* Find the rule to reduce by to get precedence of reduction.  */
  rule *redrule = reds->rules[ruleno];
  int redprec = redrule->prec->prec;
  bitset lookaheads = reds->lookaheads[ruleno];
  int nerrs = 0;

  for (i = 0; i < ntokens; i++)
    if (bitset_test (lookaheads, i)
	&& bitset_test (lookaheadset, i)
	&& symbols[i]->prec)
      {
	/* Shift-reduce conflict occurs for token number i
	   and it has a precedence.
	   The precedence of shifting is that of token i.  */
	if (symbols[i]->prec < redprec)
	  {
	    log_resolution (redrule, i, reduce_resolution);
	    flush_shift (s, i);
	  }
	else if (symbols[i]->prec > redprec)
	  {
	    log_resolution (redrule, i, shift_resolution);
	    flush_reduce (lookaheads, i);
	  }
	else
	  /* Matching precedence levels.
	     For left association, keep only the reduction.
	     For right association, keep only the shift.
	     For nonassociation, keep neither.  */

	  switch (symbols[i]->assoc)
	    {
	    case right_assoc:
	      log_resolution (redrule, i, right_resolution);
	      flush_reduce (lookaheads, i);
	      break;

	    case left_assoc:
	      log_resolution (redrule, i, left_resolution);
	      flush_shift (s, i);
	      break;

	    case non_assoc:
	      log_resolution (redrule, i, nonassoc_resolution);
	      flush_shift (s, i);
	      flush_reduce (lookaheads, i);
	      /* Record an explicit error for this token.  */
	      errors[nerrs++] = symbols[i];
	      break;

	    case undef_assoc:
	      abort ();
	    }
      }

  /* Some tokens have been explicitly made errors.  Allocate a
     permanent errs structure for this state, to record them.  */
  state_errs_set (s, nerrs, errors);

  if (obstack_object_size (&solved_conflicts_obstack))
    {
      obstack_1grow (&solved_conflicts_obstack, '\0');
      s->solved_conflicts = obstack_finish (&solved_conflicts_obstack);
    }
}


/*-------------------------------------------------------------------.
| Solve the S/R conflicts of state S using the                       |
| precedence/associativity, and flag it inconsistent if it still has |
| conflicts.  ERRORS can be used as storage to compute the list of   |
| lookaheads on which S raises a syntax error (%nonassoc).           |
`-------------------------------------------------------------------*/

static void
set_conflicts (state *s, symbol **errors)
{
  int i;
  transitions *trans = s->transitions;
  reductions *reds = s->reductions;

  if (s->consistent)
    return;

  bitset_zero (lookaheadset);

  FOR_EACH_SHIFT (trans, i)
    bitset_set (lookaheadset, TRANSITION_SYMBOL (trans, i));

  /* Loop over all rules which require lookahead in this state.  First
     check for shift-reduce conflict, and try to resolve using
     precedence.  */
  for (i = 0; i < reds->num; ++i)
    if (reds->rules[i]->prec && reds->rules[i]->prec->prec
	&& !bitset_disjoint_p (reds->lookaheads[i], lookaheadset))
      {
	resolve_sr_conflict (s, i, errors);
	break;
      }

  /* Loop over all rules which require lookahead in this state.  Check
     for conflicts not resolved above.  */
  for (i = 0; i < reds->num; ++i)
    {
      if (!bitset_disjoint_p (reds->lookaheads[i], lookaheadset))
	conflicts[s->number] = 1;

      bitset_or (lookaheadset, lookaheadset, reds->lookaheads[i]);
    }
}


/*----------------------------------------------------------------.
| Solve all the S/R conflicts using the precedence/associativity, |
| and flag as inconsistent the states that still have conflicts.  |
`----------------------------------------------------------------*/

void
conflicts_solve (void)
{
  state_number i;
  /* List of lookaheads on which we explicitly raise a syntax error.  */
  symbol **errors = MALLOC (errors, ntokens + 1);

  CALLOC (conflicts, nstates);
  shiftset = bitset_create (ntokens, BITSET_FIXED);
  lookaheadset = bitset_create (ntokens, BITSET_FIXED);
  obstack_init (&solved_conflicts_obstack);

  for (i = 0; i < nstates; i++)
    {
      set_conflicts (states[i], errors);

      /* For uniformity of the code, make sure all the states have a valid
	 `errs' member.  */
      if (!states[i]->errs)
	states[i]->errs = errs_new (0, 0);
    }

  free (errors);
}


/*---------------------------------------------.
| Count the number of shift/reduce conflicts.  |
`---------------------------------------------*/

static int
count_sr_conflicts (state *s)
{
  int i;
  int src_count = 0;
  transitions *trans = s->transitions;
  reductions *reds = s->reductions;

  if (!trans)
    return 0;

  bitset_zero (lookaheadset);
  bitset_zero (shiftset);

  FOR_EACH_SHIFT (trans, i)
    bitset_set (shiftset, TRANSITION_SYMBOL (trans, i));

  for (i = 0; i < reds->num; ++i)
    bitset_or (lookaheadset, lookaheadset, reds->lookaheads[i]);

  bitset_and (lookaheadset, lookaheadset, shiftset);

  src_count = bitset_count (lookaheadset);

  return src_count;
}


/*----------------------------------------------------------------.
| Count the number of reduce/reduce conflicts.  If ONE_PER_TOKEN, |
| count one conflict for each token that has any reduce/reduce    |
| conflicts.  Otherwise, count one conflict for each pair of      |
| conflicting reductions.                                         |
+`----------------------------------------------------------------*/

static int
count_rr_conflicts (state *s, int one_per_token)
{
  int i;
  reductions *reds = s->reductions;
  int rrc_count = 0;

  for (i = 0; i < ntokens; i++)
    {
      int count = 0;
      int j;
      for (j = 0; j < reds->num; ++j)
	if (bitset_test (reds->lookaheads[j], i))
	  count++;

      if (count >= 2)
	rrc_count += one_per_token ? 1 : count-1;
    }

  return rrc_count;
}


/*--------------------------------------------------------.
| Report the number of conflicts, using the Yacc format.  |
`--------------------------------------------------------*/

static void
conflict_report (FILE *out, int src_num, int rrc_num)
{
  if (src_num && rrc_num)
    fprintf (out, _("conflicts: %d shift/reduce, %d reduce/reduce\n"),
	     src_num, rrc_num);
  else if (src_num)
    fprintf (out, _("conflicts: %d shift/reduce\n"), src_num);
  else if (rrc_num)
    fprintf (out, _("conflicts: %d reduce/reduce\n"), rrc_num);
}


/*-----------------------------------------------------------.
| Output the detailed description of states with conflicts.  |
`-----------------------------------------------------------*/

void
conflicts_output (FILE *out)
{
  bool printed_sth = false;
  state_number i;
  for (i = 0; i < nstates; i++)
    {
      state *s = states[i];
      if (conflicts[i])
	{
	  fprintf (out, _("State %d "), i);
	  conflict_report (out, count_sr_conflicts (s),
			   count_rr_conflicts (s, true));
	  printed_sth = true;
	}
    }
  if (printed_sth)
    fputs ("\n\n", out);
}

/*--------------------------------------------------------.
| Total the number of S/R and R/R conflicts.  Unlike the  |
| code in conflicts_output, however, count EACH pair of   |
| reductions for the same state and lookahead as one      |
| conflict.						  |
`--------------------------------------------------------*/

int
conflicts_total_count (void)
{
  state_number i;
  int count;

  /* Conflicts by state.  */
  count = 0;
  for (i = 0; i < nstates; i++)
    if (conflicts[i])
      {
	count += count_sr_conflicts (states[i]);
	count += count_rr_conflicts (states[i], false);
      }
  return count;
}


/*------------------------------------------.
| Reporting the total number of conflicts.  |
`------------------------------------------*/

void
conflicts_print (void)
{
  /* Is the number of SR conflicts OK?  Either EXPECTED_CONFLICTS is
     not set, and then we want 0 SR, or else it is specified, in which
     case we want equality.  */
  int src_ok = 0;

  int src_total = 0;
  int rrc_total = 0;

  /* Conflicts by state.  */
  {
    state_number i;

    for (i = 0; i < nstates; i++)
      if (conflicts[i])
	{
	  src_total += count_sr_conflicts (states[i]);
	  rrc_total += count_rr_conflicts (states[i], true);
	}
  }

  src_ok = src_total == (expected_conflicts == -1 ? 0 : expected_conflicts);

  /* If there are no RR conflicts, and as many SR conflicts as
     expected, then there is nothing to report.  */
  if (!rrc_total && src_ok)
    return;

  /* Report the total number of conflicts on STDERR.  */
  if (! yacc_flag)
    fprintf (stderr, "%s: ", current_file);
  conflict_report (stderr, src_total, rrc_total);

  if (expected_conflicts != -1)
    {
      if (! src_ok)
	complain (ngettext ("expected %d shift/reduce conflict",
			    "expected %d shift/reduce conflicts",
			    expected_conflicts),
		  expected_conflicts);
      if (rrc_total)
	complain (_("expected 0 reduce/reduce conflicts"));
    }
}


void
conflicts_free (void)
{
  XFREE (conflicts);
  bitset_free (shiftset);
  bitset_free (lookaheadset);
  obstack_free (&solved_conflicts_obstack, NULL);
}
