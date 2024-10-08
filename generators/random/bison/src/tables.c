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

#include <bitsetv.h>
#include <quotearg.h>

#include "complain.h"
#include "conflicts.h"
#include "files.h"
#include "getargs.h"
#include "gram.h"
#include "lalr.h"
#include "reader.h"
#include "symtab.h"
#include "tables.h"

/* Several tables are indexed both by state and nonterminal numbers.
   We call such an index a `vector'; i.e., a vector is either a state
   or a nonterminal number.

   Of course vector_number_t ought to be wide enough to contain
   state_number and symbol_number.  */
typedef short vector_number;

static inline vector_number
state_number_to_vector_number (state_number s)
{
  return s;
}

static inline vector_number
symbol_number_to_vector_number (symbol_number s)
{
  return state_number_as_int (nstates) + s - ntokens;
}

int nvectors;


/* FROMS and TOS are indexed by vector_number.

   If VECTOR is a nonterminal, (FROMS[VECTOR], TOS[VECTOR]) form an
   array of state numbers of the non defaulted GOTO on VECTOR.

   If VECTOR is a state, TOS[VECTOR] is the array of actions to do on
   the (array of) symbols FROMS[VECTOR].

   In both cases, TALLY[VECTOR] is the size of the arrays
   FROMS[VECTOR], TOS[VECTOR]; and WIDTH[VECTOR] =
   (FROMS[VECTOR][SIZE] - FROMS[VECTOR][0] + 1) where SIZE =
   TALLY[VECTOR].

   FROMS therefore contains symbol_number and action_number,
   TOS state_number and action_number,
   TALLY sizes,
   WIDTH differences of FROMS.

   Let base_number be the type of FROMS, TOS, and WIDTH.  */
#define BASE_MAXIMUM INT_MAX
#define BASE_MINIMUM INT_MIN

static base_number **froms = NULL;
static base_number **tos = NULL;
static unsigned int **conflict_tos = NULL;
static short *tally = NULL;
static base_number *width = NULL;


/* For a given state, N = ACTROW[SYMBOL]:

   If N = 0, stands for `run the default action'.
   If N = MIN, stands for `raise a syntax error'.
   If N > 0, stands for `shift SYMBOL and go to n'.
   If N < 0, stands for `reduce -N'.  */
typedef short action_number;
#define ACTION_NUMBER_MINIMUM SHRT_MIN

static action_number *actrow = NULL;

/* FROMS and TOS are reordered to be compressed.  ORDER[VECTOR] is the
   new vector number of VECTOR.  We skip `empty' vectors (i.e.,
   TALLY[VECTOR] = 0), and call these `entries'.  */
static vector_number *order = NULL;
static int nentries;

base_number *base = NULL;
/* A distinguished value of BASE, negative infinite.  During the
   computation equals to BASE_MINIMUM, later mapped to BASE_NINF to
   keep parser tables small.  */
base_number base_ninf = 0;
static base_number *pos = NULL;

static unsigned int *conflrow = NULL;
unsigned int *conflict_table = NULL;
unsigned int *conflict_list = NULL;
int conflict_list_cnt;
static int conflict_list_free;

/* TABLE_SIZE is the allocated size of both TABLE and CHECK.  We start
   with more or less the original hard-coded value (which was
   SHRT_MAX).  */
static int table_size = 32768;
base_number *table = NULL;
base_number *check = NULL;
/* The value used in TABLE to denote explicit syntax errors
   (%nonassoc), a negative infinite.  First defaults to ACTION_NUMBER_MININUM,
   but in order to keep small tables, renumbered as TABLE_ERROR, which
   is the smallest (non error) value minus 1.  */
base_number table_ninf = 0;
static int lowzero;
int high;

state_number *yydefgoto;
rule_number *yydefact;

/*----------------------------------------------------------------.
| If TABLE (and CHECK) appear to be small to be addressed at      |
| DESIRED, grow them.  Note that TABLE[DESIRED] is to be used, so |
| the desired size is at least DESIRED + 1.                       |
`----------------------------------------------------------------*/

static void
table_grow (int desired)
{
  int old_size = table_size;

  while (table_size <= desired)
    table_size *= 2;

  if (trace_flag & trace_resource)
    fprintf (stderr, "growing table and check from: %d to %d\n",
	     old_size, table_size);

  REALLOC (table, table_size);
  REALLOC (check, table_size);
  REALLOC (conflict_table, table_size);

  for (/* Nothing. */; old_size < table_size; ++old_size)
    {
      table[old_size] = 0;
      check[old_size] = -1;
    }
}




/*-------------------------------------------------------------------.
| For GLR parsers, for each conflicted token in S, as indicated      |
| by non-zero entries in CONFLROW, create a list of possible 	     |
| reductions that are alternatives to the shift or reduction	     |
| currently recorded for that token in S.  Store the alternative     |
| reductions followed by a 0 in CONFLICT_LIST, updating		     |
| CONFLICT_LIST_CNT, and storing an index to the start of the list   |
| back into CONFLROW.						     |
`-------------------------------------------------------------------*/

static void
conflict_row (state *s)
{
  int i, j;
  reductions *reds = s->reductions;

  if (! glr_parser)
    return;

  for (j = 0; j < ntokens; j += 1)
    if (conflrow[j])
      {
	conflrow[j] = conflict_list_cnt;

	/* Find all reductions for token J, and record all that do not
	   match ACTROW[J].  */
	for (i = 0; i < reds->num; i += 1)
	  if (bitset_test (reds->lookaheads[i], j)
	      && (actrow[j]
		  != rule_number_as_item_number (reds->rules[i]->number)))
	    {
	      if (conflict_list_free <= 0)
		abort ();
	      conflict_list[conflict_list_cnt] = reds->rules[i]->number + 1;
	      conflict_list_cnt += 1;
	      conflict_list_free -= 1;
	    }

	/* Leave a 0 at the end.  */
	if (conflict_list_free <= 0)
	  abort ();
	conflict_list_cnt += 1;
	conflict_list_free -= 1;
      }
}


/*------------------------------------------------------------------.
| Decide what to do for each type of token if seen as the lookahead |
| token in specified state.  The value returned is used as the      |
| default action (yydefact) for the state.  In addition, ACTROW is  |
| filled with what to do for each kind of token, index by symbol    |
| number, with zero meaning do the default action.  The value       |
| ACTION_NUMBER_MINIMUM, a very negative number, means this	    |
| situation is an error.  The parser recognizes this value	    |
| specially.							    |
|                                                                   |
| This is where conflicts are resolved.  The loop over lookahead    |
| rules considered lower-numbered rules last, and the last rule     |
| considered that likes a token gets to handle it.                  |
|                                                                   |
| For GLR parsers, also sets CONFLROW[SYM] to an index into         |
| CONFLICT_LIST iff there is an unresolved conflict (s/r or r/r)    |
| with symbol SYM. The default reduction is not used for a symbol   |
| that has any such conflicts.                                      |
`------------------------------------------------------------------*/

static rule *
action_row (state *s)
{
  int i;
  rule *default_rule = NULL;
  reductions *reds = s->reductions;
  transitions *trans = s->transitions;
  errs *errp = s->errs;
  /* Set to nonzero to inhibit having any default reduction.  */
  int nodefault = 0;
  int conflicted = 0;

  for (i = 0; i < ntokens; i++)
    actrow[i] = conflrow[i] = 0;

  if (reds->lookaheads)
    {
      int j;
      bitset_iterator biter;
      /* loop over all the rules available here which require
	 lookahead (in reverse order to give precedence to the first
	 rule) */
      for (i = reds->num - 1; i >= 0; --i)
	/* and find each token which the rule finds acceptable
	   to come next */
	BITSET_FOR_EACH (biter, reds->lookaheads[i], j, 0)
	{
	  /* and record this rule as the rule to use if that
	     token follows.  */
	  if (actrow[j] != 0)
	    conflicted = conflrow[j] = 1;
	  actrow[j] = rule_number_as_item_number (reds->rules[i]->number);
	}
    }

  /* Now see which tokens are allowed for shifts in this state.  For
     them, record the shift as the thing to do.  So shift is preferred
     to reduce.  */
  FOR_EACH_SHIFT (trans, i)
    {
      symbol_number sym = TRANSITION_SYMBOL (trans, i);
      state *shift_state = trans->states[i];

      if (actrow[sym] != 0)
	conflicted = conflrow[sym] = 1;
      actrow[sym] = state_number_as_int (shift_state->number);

      /* Do not use any default reduction if there is a shift for
	 error */
      if (sym == errtoken->number)
	nodefault = 1;
    }

  /* See which tokens are an explicit error in this state (due to
     %nonassoc).  For them, record ACTION_NUMBER_MINIMUM as the
     action.  */
  for (i = 0; i < errp->num; i++)
    {
      symbol *sym = errp->symbols[i];
      actrow[sym->number] = ACTION_NUMBER_MINIMUM;
    }

  /* Now find the most common reduction and make it the default action
     for this state.  */

  if (reds->num >= 1 && !nodefault)
    {
      if (s->consistent)
	default_rule = reds->rules[0];
      else
	{
	  int max = 0;
	  for (i = 0; i < reds->num; i++)
	    {
	      int count = 0;
	      rule *r = reds->rules[i];
	      symbol_number j;

	      for (j = 0; j < ntokens; j++)
		if (actrow[j] == rule_number_as_item_number (r->number))
		  count++;

	      if (count > max)
		{
		  max = count;
		  default_rule = r;
		}
	    }

	  /* GLR parsers need space for conflict lists, so we can't
	     default conflicted entries.  For non-conflicted entries
	     or as long as we are not building a GLR parser,
	     actions that match the default are replaced with zero,
	     which means "use the default". */

	  if (max > 0)
	    {
	      int j;
	      for (j = 0; j < ntokens; j++)
		if (actrow[j] == rule_number_as_item_number (default_rule->number)
		    && ! (glr_parser && conflrow[j]))
		  actrow[j] = 0;
	    }
	}
    }

  /* If have no default rule, the default is an error.
     So replace any action which says "error" with "use default".  */

  if (!default_rule)
    for (i = 0; i < ntokens; i++)
      if (actrow[i] == ACTION_NUMBER_MINIMUM)
	actrow[i] = 0;

  if (conflicted)
    conflict_row (s);

  return default_rule;
}


/*----------------------------------------.
| Set FROMS, TOS, TALLY and WIDTH for S.  |
`----------------------------------------*/

static void
save_row (state_number s)
{
  symbol_number i;
  int count;
  base_number *sp;
  base_number *sp1;
  base_number *sp2;
  unsigned int *sp3 IF_LINT (= NULL);

  /* Number of non default actions in S.  */
  count = 0;
  for (i = 0; i < ntokens; i++)
    if (actrow[i] != 0)
      count++;

  if (count == 0)
    return;

  /* Allocate non defaulted actions.  */
  froms[s] = sp = CALLOC (sp1, count);
  tos[s] = CALLOC (sp2, count);
  conflict_tos[s] = glr_parser ? CALLOC (sp3, count) : NULL;

  /* Store non defaulted actions.  */
  for (i = 0; i < ntokens; i++)
    if (actrow[i] != 0)
      {
	*sp1++ = i;
	*sp2++ = actrow[i];
	if (glr_parser)
	  *sp3++ = conflrow[i];
      }

  tally[s] = count;
  width[s] = sp1[-1] - sp[0] + 1;
}


/*------------------------------------------------------------------.
| Figure out the actions for the specified state, indexed by        |
| lookahead token type.                                             |
|                                                                   |
| The YYDEFACT table is output now.  The detailed info is saved for |
| putting into YYTABLE later.                                       |
`------------------------------------------------------------------*/

static void
token_actions (void)
{
  state_number i;
  symbol_number j;
  rule_number r;

  int nconflict = glr_parser ? conflicts_total_count () : 0;

  CALLOC (yydefact, nstates);

  CALLOC (actrow, ntokens);
  CALLOC (conflrow, ntokens);

  CALLOC (conflict_list, 1 + 2 * nconflict);
  conflict_list_free = 2 * nconflict;
  conflict_list_cnt = 1;

  /* Find the rules which are reduced.  */
  if (!glr_parser)
    for (r = 0; r < nrules; ++r)
      rules[r].useful = false;

  for (i = 0; i < nstates; ++i)
    {
      rule *default_rule = action_row (states[i]);
      yydefact[i] = default_rule ? default_rule->number + 1 : 0;
      save_row (i);

      /* Now that the parser was computed, we can find which rules are
	 really reduced, and which are not because of SR or RR
	 conflicts.  */
      if (!glr_parser)
	{
	  for (j = 0; j < ntokens; ++j)
	    if (actrow[j] < 0 && actrow[j] != ACTION_NUMBER_MINIMUM)
	      rules[item_number_as_rule_number (actrow[j])].useful = true;
	  if (yydefact[i])
	    rules[yydefact[i] - 1].useful = true;
	}
    }

  free (actrow);
  free (conflrow);
}


/*------------------------------------------------------------------.
| Compute FROMS[VECTOR], TOS[VECTOR], TALLY[VECTOR], WIDTH[VECTOR], |
| i.e., the information related to non defaulted GOTO on the nterm  |
| SYM.                                                              |
|                                                                   |
| DEFAULT_STATE is the principal destination on SYM, i.e., the      |
| default GOTO destination on SYM.                                  |
`------------------------------------------------------------------*/

static void
save_column (symbol_number sym, state_number default_state)
{
  int i;
  base_number *sp;
  base_number *sp1;
  base_number *sp2;
  int count;
  vector_number symno = symbol_number_to_vector_number (sym);

  goto_number begin = goto_map[sym - ntokens];
  goto_number end = goto_map[sym - ntokens + 1];

  /* Number of non default GOTO.  */
  count = 0;
  for (i = begin; i < end; i++)
    if (to_state[i] != default_state)
      count++;

  if (count == 0)
    return;

  /* Allocate room for non defaulted gotos.  */
  froms[symno] = sp = CALLOC (sp1, count);
  tos[symno] = CALLOC (sp2, count);

  /* Store the state numbers of the non defaulted gotos.  */
  for (i = begin; i < end; i++)
    if (to_state[i] != default_state)
      {
	*sp1++ = from_state[i];
	*sp2++ = to_state[i];
      }

  tally[symno] = count;
  width[symno] = sp1[-1] - sp[0] + 1;
}


/*-------------------------------------------------------------.
| Return `the' most common destination GOTO on SYM (a nterm).  |
`-------------------------------------------------------------*/

static state_number
default_goto (symbol_number sym, short state_count[])
{
  state_number s;
  int i;
  goto_number m = goto_map[sym - ntokens];
  goto_number n = goto_map[sym - ntokens + 1];
  state_number default_state = -1;
  int max = 0;

  if (m == n)
    return -1;

  for (s = 0; s < nstates; s++)
    state_count[s] = 0;

  for (i = m; i < n; i++)
    state_count[to_state[i]]++;

  for (s = 0; s < nstates; s++)
    if (state_count[s] > max)
      {
	max = state_count[s];
	default_state = s;
      }

  return default_state;
}


/*-------------------------------------------------------------------.
| Figure out what to do after reducing with each rule, depending on  |
| the saved state from before the beginning of parsing the data that |
| matched this rule.                                                 |
|                                                                    |
| The YYDEFGOTO table is output now.  The detailed info is saved for |
| putting into YYTABLE later.                                        |
`-------------------------------------------------------------------*/

static void
goto_actions (void)
{
  symbol_number i;
  short *state_count = CALLOC (state_count, nstates);
  MALLOC (yydefgoto, nvars);

  /* For a given nterm I, STATE_COUNT[S] is the number of times there
     is a GOTO to S on I.  */
  for (i = ntokens; i < nsyms; ++i)
    {
      state_number default_state = default_goto (i, state_count);
      save_column (i, default_state);
      yydefgoto[i - ntokens] = default_state;
    }
  free (state_count);
}


/*------------------------------------------------------------------.
| Compute ORDER, a reordering of vectors, in order to decide how to |
| pack the actions and gotos information into yytable.              |
`------------------------------------------------------------------*/

static void
sort_actions (void)
{
  int i;

  nentries = 0;

  for (i = 0; i < nvectors; i++)
    if (tally[i] > 0)
      {
	int k;
	int t = tally[i];
	int w = width[i];
	int j = nentries - 1;

	while (j >= 0 && (width[order[j]] < w))
	  j--;

	while (j >= 0 && (width[order[j]] == w) && (tally[order[j]] < t))
	  j--;

	for (k = nentries - 1; k > j; k--)
	  order[k + 1] = order[k];

	order[j + 1] = i;
	nentries++;
      }
}


/* If VECTOR is a state which actions (reflected by FROMS, TOS, TALLY
   and WIDTH of VECTOR) are common to a previous state, return this
   state number.

   In any other case, return -1.  */

static state_number
matching_state (vector_number vector)
{
  vector_number i = order[vector];
  int t;
  int w;
  int prev;

  /* If VECTOR is a nterm, return -1.  */
  if (nstates <= i)
    return -1;

  t = tally[i];
  w = width[i];

  /* If VECTOR has GLR conflicts, return -1 */
  if (conflict_tos[i] != NULL)
    {
      int j;
      for (j = 0; j < t; j += 1)
	if (conflict_tos[i][j] != 0)
	  return -1;
    }

  for (prev = vector - 1; prev >= 0; prev--)
    {
      vector_number j = order[prev];
      int k;
      int match = 1;

      /* Given how ORDER was computed, if the WIDTH or TALLY is
	 different, there cannot be a matching state.  */
      if (width[j] != w || tally[j] != t)
	return -1;

      for (k = 0; match && k < t; k++)
	if (tos[j][k] != tos[i][k] || froms[j][k] != froms[i][k]
	    || (conflict_tos[j] != NULL && conflict_tos[j][k] != 0))
	  match = 0;

      if (match)
	return j;
    }

  return -1;
}


static base_number
pack_vector (vector_number vector)
{
  vector_number i = order[vector];
  int j;
  int t = tally[i];
  int loc = 0;
  base_number *from = froms[i];
  base_number *to = tos[i];
  unsigned int *conflict_to = conflict_tos[i];

  if (! t)
    abort ();

  for (j = lowzero - from[0]; ; j++)
    {
      int k;
      int ok = 1;

      if (table_size <= j)
	abort ();

      for (k = 0; ok && k < t; k++)
	{
	  loc = j + state_number_as_int (from[k]);
	  if (table_size <= loc)
	    table_grow (loc);

	  if (table[loc] != 0)
	    ok = 0;
	}

      for (k = 0; ok && k < vector; k++)
	if (pos[k] == j)
	  ok = 0;

      if (ok)
	{
	  for (k = 0; k < t; k++)
	    {
	      loc = j + from[k];
	      table[loc] = to[k];
	      if (glr_parser && conflict_to != NULL)
		conflict_table[loc] = conflict_to[k];
	      check[loc] = from[k];
	    }

	  while (table[lowzero] != 0)
	    lowzero++;

	  if (loc > high)
	    high = loc;

	  if (! (BASE_MINIMUM <= j && j <= BASE_MAXIMUM))
	    abort ();
	  return j;
	}
    }
}


/*-------------------------------------------------------------.
| Remap the negative infinite in TAB from NINF to the greatest |
| possible smallest value.  Return it.                         |
|                                                              |
| In most case this allows us to use shorts instead of ints in |
| parsers.                                                     |
`-------------------------------------------------------------*/

static base_number
table_ninf_remap (base_number tab[], int size, base_number ninf)
{
  base_number res = 0;
  int i;

  for (i = 0; i < size; i++)
    if (tab[i] < res && tab[i] != ninf)
      res = tab[i];

  --res;

  for (i = 0; i < size; i++)
    if (tab[i] == ninf)
      tab[i] = res;

  return res;
}

static void
pack_table (void)
{
  int i;

  CALLOC (base, nvectors);
  CALLOC (pos, nentries);
  CALLOC (table, table_size);
  CALLOC (conflict_table, table_size);
  CALLOC (check, table_size);

  lowzero = 0;
  high = 0;

  for (i = 0; i < nvectors; i++)
    base[i] = BASE_MINIMUM;

  for (i = 0; i < table_size; i++)
    check[i] = -1;

  for (i = 0; i < nentries; i++)
    {
      state_number s = matching_state (i);
      base_number place;

      if (s < 0)
	/* A new set of state actions, or a nonterminal.  */
	place = pack_vector (i);
      else
	/* Action of I were already coded for S.  */
	place = base[s];

      pos[i] = place;
      base[order[i]] = place;
    }

  /* Use the greatest possible negative infinites.  */
  base_ninf = table_ninf_remap (base, nvectors, BASE_MINIMUM);
  table_ninf = table_ninf_remap (table, high + 1, ACTION_NUMBER_MINIMUM);

  free (pos);
}



/*-----------------------------------------------------------------.
| Compute and output yydefact, yydefgoto, yypact, yypgoto, yytable |
| and yycheck.                                                     |
`-----------------------------------------------------------------*/

void
tables_generate (void)
{
  int i;

  /* This is a poor way to make sure the sizes are properly
     correlated.  In particular the signedness is not taken into
     account.  But it's not useless.  */
  verify (sizes_are_properly_correlated,
	  (sizeof nstates <= sizeof nvectors
	   && sizeof nvars <= sizeof nvectors));

  nvectors = state_number_as_int (nstates) + nvars;

  CALLOC (froms, nvectors);
  CALLOC (tos, nvectors);
  CALLOC (conflict_tos, nvectors);
  CALLOC (tally, nvectors);
  CALLOC (width, nvectors);

  token_actions ();

  goto_actions ();
  free (goto_map);
  free (from_state);
  free (to_state);

  CALLOC (order, nvectors);
  sort_actions ();
  pack_table ();
  free (order);

  free (tally);
  free (width);

  for (i = 0; i < nvectors; i++)
    {
      free (froms[i]);
      free (tos[i]);
      XFREE (conflict_tos[i]);
    }

  free (froms);
  free (tos);
  free (conflict_tos);
}


/*-------------------------.
| Free the parser tables.  |
`-------------------------*/

void
tables_free (void)
{
  free (base);
  free (conflict_table);
  free (conflict_list);
  free (table);
  free (check);
  free (yydefgoto);
  free (yydefact);
}
