/* Generate the nondeterministic finite state machine for Bison.

   Copyright (C) 1984, 1986, 1989, 2000, 2001, 2002 Free Software
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


/* See comments in state.h for the data structures that represent it.
   The entry point is generate_states.  */

#include "system.h"

#include <bitset.h>
#include <quotearg.h>

#include "LR0.h"
#include "closure.h"
#include "complain.h"
#include "getargs.h"
#include "gram.h"
#include "gram.h"
#include "lalr.h"
#include "reader.h"
#include "reduce.h"
#include "state.h"
#include "symtab.h"

typedef struct state_list
{
  struct state_list *next;
  state *state;
} state_list;

static state_list *first_state = NULL;
static state_list *last_state = NULL;


/*------------------------------------------------------------------.
| A state was just discovered from another state.  Queue it for     |
| later examination, in order to find its transitions.  Return it.  |
`------------------------------------------------------------------*/

static state *
state_list_append (symbol_number sym, size_t core_size, item_number *core)
{
  state_list *node = MALLOC (node, 1);
  state *s = state_new (sym, core_size, core);

  if (trace_flag & trace_automaton)
    fprintf (stderr, "state_list_append (state = %d, symbol = %d (%s))\n",
	     nstates, sym, symbols[sym]->tag);

  /* If this is the endtoken, and this is not the initial state, then
     this is the final state.  */
  if (sym == 0 && first_state)
    final_state = s;

  node->next = NULL;
  node->state = s;

  if (!first_state)
    first_state = node;
  if (last_state)
    last_state->next = node;
  last_state = node;

  return s;
}

static int nshifts;
static symbol_number *shift_symbol = NULL;

static rule **redset = NULL;
static state **shiftset = NULL;

static item_number **kernel_base = NULL;
static int *kernel_size = NULL;
static item_number *kernel_items = NULL;


static void
allocate_itemsets (void)
{
  symbol_number i;
  rule_number r;
  item_number *rhsp;

  /* Count the number of occurrences of all the symbols in RITEMS.
     Note that useless productions (hence useless nonterminals) are
     browsed too, hence we need to allocate room for _all_ the
     symbols.  */
  int count = 0;
  short *symbol_count = CALLOC (symbol_count, nsyms + nuseless_nonterminals);

  for (r = 0; r < nrules; ++r)
    for (rhsp = rules[r].rhs; *rhsp >= 0; ++rhsp)
      {
	count++;
	symbol_count[*rhsp]++;
      }

  /* See comments before new_itemsets.  All the vectors of items
     live inside KERNEL_ITEMS.  The number of active items after
     some symbol S cannot be more than the number of times that S
     appears as an item, which is SYMBOL_COUNT[S].
     We allocate that much space for each symbol.  */

  CALLOC (kernel_base, nsyms);
  if (count)
    CALLOC (kernel_items, count);

  count = 0;
  for (i = 0; i < nsyms; i++)
    {
      kernel_base[i] = kernel_items + count;
      count += symbol_count[i];
    }

  free (symbol_count);
  CALLOC (kernel_size, nsyms);
}


static void
allocate_storage (void)
{
  allocate_itemsets ();

  CALLOC (shiftset, nsyms);
  CALLOC (redset, nrules);
  state_hash_new ();
  CALLOC (shift_symbol, nsyms);
}


static void
free_storage (void)
{
  free (shift_symbol);
  free (redset);
  free (shiftset);
  free (kernel_base);
  free (kernel_size);
  XFREE (kernel_items);
  state_hash_free ();
}




/*---------------------------------------------------------------.
| Find which symbols can be shifted in S, and for each one       |
| record which items would be active after that shift.  Uses the |
| contents of itemset.                                           |
|                                                                |
| shift_symbol is set to a vector of the symbols that can be     |
| shifted.  For each symbol in the grammar, kernel_base[symbol]  |
| points to a vector of item numbers activated if that symbol is |
| shifted, and kernel_size[symbol] is their numbers.             |
`---------------------------------------------------------------*/

static void
new_itemsets (state *s)
{
  int i;

  if (trace_flag & trace_automaton)
    fprintf (stderr, "Entering new_itemsets, state = %d\n", s->number);

  for (i = 0; i < nsyms; i++)
    kernel_size[i] = 0;

  nshifts = 0;

  for (i = 0; i < nritemset; ++i)
    if (ritem[itemset[i]] >= 0)
      {
	symbol_number sym = item_number_as_symbol_number (ritem[itemset[i]]);
	if (!kernel_size[sym])
	  {
	    shift_symbol[nshifts] = sym;
	    nshifts++;
	  }

	kernel_base[sym][kernel_size[sym]] = itemset[i] + 1;
	kernel_size[sym]++;
      }
}



/*--------------------------------------------------------------.
| Find the state we would get to (from the current state) by    |
| shifting SYM.  Create a new state if no equivalent one exists |
| already.  Used by append_states.                              |
`--------------------------------------------------------------*/

static state *
get_state (symbol_number sym, size_t core_size, item_number *core)
{
  state *sp;

  if (trace_flag & trace_automaton)
    fprintf (stderr, "Entering get_state, symbol = %d (%s)\n",
	     sym, symbols[sym]->tag);

  sp = state_hash_lookup (core_size, core);
  if (!sp)
    sp = state_list_append (sym, core_size, core);

  if (trace_flag & trace_automaton)
    fprintf (stderr, "Exiting get_state => %d\n", sp->number);

  return sp;
}

/*---------------------------------------------------------------.
| Use the information computed by new_itemsets to find the state |
| numbers reached by each shift transition from S.		 |
|                                                                |
| SHIFTSET is set up as a vector of those states.                |
`---------------------------------------------------------------*/

static void
append_states (state *s)
{
  int i;

  if (trace_flag & trace_automaton)
    fprintf (stderr, "Entering append_states, state = %d\n", s->number);

  /* First sort shift_symbol into increasing order.  */

  for (i = 1; i < nshifts; i++)
    {
      symbol_number sym = shift_symbol[i];
      int j;
      for (j = i; 0 < j && sym < shift_symbol [j - 1]; j--)
	shift_symbol[j] = shift_symbol[j - 1];
      shift_symbol[j] = sym;
    }

  for (i = 0; i < nshifts; i++)
    {
      symbol_number sym = shift_symbol[i];
      shiftset[i] = get_state (sym, kernel_size[sym], kernel_base[sym]);
    }
}


/*----------------------------------------------------------------.
| Find which rules can be used for reduction transitions from the |
| current state and make a reductions structure for the state to  |
| record their rule numbers.                                      |
`----------------------------------------------------------------*/

static void
save_reductions (state *s)
{
  int count = 0;
  int i;

  /* Find and count the active items that represent ends of rules. */
  for (i = 0; i < nritemset; ++i)
    {
      int item = ritem[itemset[i]];
      if (item < 0)
	redset[count++] = &rules[item_number_as_rule_number (item)];
    }

  /* Make a reductions structure and copy the data into it.  */
  state_reductions_set (s, count, redset);
}


/*---------------.
| Build STATES.  |
`---------------*/

static void
set_states (void)
{
  CALLOC (states, nstates);

  while (first_state)
    {
      state_list *this = first_state;

      /* Pessimization, but simplification of the code: make sure all
	 the states have valid transitions and reductions members,
	 even if reduced to 0.  It is too soon for errs, which are
	 computed later, but set_conflicts.  */
      state *s = this->state;
      if (!s->transitions)
	state_transitions_set (s, 0, 0);
      if (!s->reductions)
	state_reductions_set (s, 0, 0);

      states[s->number] = s;

      first_state = this->next;
      free (this);
    }
  first_state = NULL;
  last_state = NULL;
}


/*-------------------------------------------------------------------.
| Compute the nondeterministic finite state machine (see state.h for |
| details) from the grammar.                                         |
`-------------------------------------------------------------------*/

void
generate_states (void)
{
  state_list *list = NULL;
  allocate_storage ();
  new_closure (nritems);

  /* Create the initial state.  The 0 at the lhs is the index of the
     item of this initial rule.  */
  kernel_base[0][0] = 0;
  kernel_size[0] = 1;
  state_list_append (0, kernel_size[0], kernel_base[0]);

  list = first_state;

  while (list)
    {
      state *s = list->state;
      if (trace_flag & trace_automaton)
	fprintf (stderr, "Processing state %d (reached by %s)\n",
		 s->number,
		 symbols[s->accessing_symbol]->tag);
      /* Set up ruleset and itemset for the transitions out of this
         state.  ruleset gets a 1 bit for each rule that could reduce
         now.  itemset gets a vector of all the items that could be
         accepted next.  */
      closure (s->items, s->nitems);
      /* Record the reductions allowed out of this state.  */
      save_reductions (s);
      /* Find the itemsets of the states that shifts can reach.  */
      new_itemsets (s);
      /* Find or create the core structures for those states.  */
      append_states (s);

      /* Create the shifts structures for the shifts to those states,
	 now that the state numbers transitioning to are known.  */
      state_transitions_set (s, nshifts, shiftset);

      /* states are queued when they are created; process them all.
	 */
      list = list->next;
    }

  /* discard various storage */
  free_closure ();
  free_storage ();

  /* Set up STATES. */
  set_states ();
}
