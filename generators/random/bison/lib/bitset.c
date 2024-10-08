/* General bitsets.
   Copyright (C) 2002 Free Software Foundation, Inc.
   Contributed by Michael Hayes (m.hayes@elec.canterbury.ac.nz).

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
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include "bitset.h"
#include "abitset.h"
#include "lbitset.h"
#include "ebitset.h"
#include "bitset_stats.h"
#include "obstack.h"

const char * const bitset_type_names[] = BITSET_TYPE_NAMES;


/* Return number of bytes required to create a N_BIT bitset
   of TYPE.  The bitset may grow to require more bytes than this.  */
size_t
bitset_bytes (enum bitset_type type, bitset_bindex n_bits)
{
  size_t bytes;

  if (bitset_stats_enabled)
    return bitset_stats_bytes ();

  switch (type)
    {
    case BITSET_ARRAY:
      bytes = abitset_bytes (n_bits);
      break;

    case BITSET_LIST:
      bytes = lbitset_bytes (n_bits);
      break;

    case BITSET_TABLE:
      bytes = ebitset_bytes (n_bits);
      break;

    default:
      abort ();
    }

  return bytes;
}


/* Initialise bitset BSET of TYPE for N_BITS.  */
bitset
bitset_init (bitset bset, bitset_bindex n_bits, enum bitset_type type)
{
  if (bitset_stats_enabled)
    return bitset_stats_init (bset, n_bits, type);

  switch (type)
    {
    case BITSET_ARRAY:
      return abitset_init (bset, n_bits);

    case BITSET_LIST:
      return lbitset_init (bset, n_bits);

    case BITSET_TABLE:
      return ebitset_init (bset, n_bits);

    default:
      abort ();
    }
}


/* Select a bitset type for a set of N_BITS and with attribute hints
   specified by ATTR.  For variable size bitsets, N_BITS is only a
   hint and may be zero.  */
enum bitset_type
bitset_type_choose (bitset_bindex n_bits ATTRIBUTE_UNUSED, unsigned int attr)
{
  enum bitset_type type;

  /* Check attributes.  */
  if (attr & BITSET_FIXED && attr & BITSET_VARIABLE)
    abort ();
  if (attr & BITSET_SPARSE && attr & BITSET_DENSE)
    abort ();

  /* Choose the type of bitset. Note that sometimes we will be asked
  for a zero length fixed size bitset.  */

  type = BITSET_ARRAY;
  /* Currently, the simple bitsets do not support a variable size.  */
  if (attr & BITSET_VARIABLE || attr & BITSET_SPARSE)
    {
      type = BITSET_LIST;
      if (attr & BITSET_DENSE || attr & BITSET_GREEDY)
	type = BITSET_TABLE;
    }

  return type;
}


/* Create a bitset of N_BITS of type TYPE.  */
bitset
bitset_alloc (bitset_bindex n_bits, enum bitset_type type)
{
  size_t bytes;
  bitset bset;

  bytes = bitset_bytes (type, n_bits);

  bset = (bitset) xcalloc (1, bytes);

  /* The cache is disabled until some elements are allocated.  If we
     have variable length arrays, then we may need to allocate a dummy
     element.  */

  return bitset_init (bset, n_bits, type);
}


/* Create a bitset of N_BITS of type TYPE.  */
bitset
bitset_obstack_alloc (struct obstack *bobstack,
		      bitset_bindex n_bits, enum bitset_type type)
{
  size_t bytes;
  bitset bset;

  bytes = bitset_bytes (type, n_bits);

  bset = obstack_alloc (bobstack, bytes);
  memset (bset, 0, bytes);

  return bitset_init (bset, n_bits, type);
}


/* Create a bitset of N_BITS and with attribute hints specified by
   ATTR.  */
bitset
bitset_create (bitset_bindex n_bits, unsigned int attr)
{
  enum bitset_type type;

  type = bitset_type_choose (n_bits, attr);

  return bitset_alloc (n_bits, type);
}


/* Free bitset BSET.  */
void
bitset_free (bitset bset)
{
  BITSET_FREE_ (bset);
  free (bset);
}


/* Free bitset BSET allocated on obstack.  */
void
bitset_obstack_free (bitset bset)
{
  BITSET_FREE_ (bset);
}


/* Return bitset type.  */
enum bitset_type
bitset_type_get (bitset bset)
{
   enum bitset_type type;

   type = BITSET_TYPE_ (bset);
   if (type != BITSET_STATS)
      return type;

   return bitset_stats_type_get (bset);
}


/* Return name of bitset type.  */
const char *
bitset_type_name_get (bitset bset)
{
  enum bitset_type type;

  type = bitset_type_get (bset);

  return bitset_type_names[type];
}


/* Find next bit set in SRC starting from and including BITNO.
   Return BITSET_BINDEX_MAX if SRC empty.  */
bitset_bindex
bitset_next (bitset src, bitset_bindex bitno)
{
  bitset_bindex val;
  bitset_bindex next = bitno;

  if (!bitset_list (src, &val, 1, &next))
    return BITSET_BINDEX_MAX;
  return val;
}


/* Find previous bit set in SRC starting from and including BITNO.
   Return BITSET_BINDEX_MAX if SRC empty.  */
bitset_bindex
bitset_prev (bitset src, bitset_bindex bitno)
{
  bitset_bindex val;
  bitset_bindex next = bitno;

  if (!bitset_list_reverse (src, &val, 1, &next))
    return BITSET_BINDEX_MAX;
  return val;
}


/* Find first set bit.   */
bitset_bindex
bitset_first (bitset src)
{
  return bitset_next (src, 0);
}


/* Find last set bit.   */
bitset_bindex
bitset_last (bitset src)
{
  return bitset_prev (src, 0);
}


/* Return non-zero if BITNO in SRC is the only set bit.  */
int
bitset_only_set_p (bitset src, bitset_bindex bitno)
{
  bitset_bindex val[2];
  bitset_bindex next = 0;

  if (bitset_list (src, val, 2, &next) != 1)
    return 0;
  return val[0] == bitno;
}


/* Print contents of bitset BSET to FILE.   */
static void
bitset_print (FILE *file, bitset bset, int verbose)
{
  unsigned int pos;
  bitset_bindex i;
  bitset_iterator iter;

  if (verbose)
    fprintf (file, "n_bits = %lu, set = {",
	     (unsigned long) bitset_size (bset));

  pos = 30;
  BITSET_FOR_EACH (iter, bset, i, 0)
  {
    if (pos > 70)
      {
	fprintf (file, "\n");
	pos = 0;
      }

    fprintf (file, "%d ", i);
    pos += 1 + (i >= 10) + (i >= 100);
  };

  if (verbose)
    fprintf (file, "}\n");
}


/* Dump bitset BSET to FILE.  */
void
bitset_dump (FILE *file, bitset bset)
{
  bitset_print (file, bset, 0);
}



/* Release memory associated with bitsets.  */
void
bitset_release_memory (void)
{
  lbitset_release_memory ();
  ebitset_release_memory ();
}



/* Toggle bit BITNO in bitset BSET and return non-zero if not set.  */
int
bitset_toggle_ (bitset bset, bitset_bindex bitno)
{
  /* This routine is for completeness.  It could be optimized if
     required.  */
  if (bitset_test (bset, bitno))
    {
      bitset_reset (bset, bitno);
      return 0;
    }
  else
    {
      bitset_set (bset, bitno);
      return 1;
    }
}


/* Return number of bits set in bitset SRC.  */
bitset_bindex
bitset_count_ (bitset src)
{
  bitset_bindex list[BITSET_LIST_SIZE];
  bitset_bindex next;
  bitset_bindex num;
  bitset_bindex count;

  /* This could be greatly sped up by adding a count method for each
     bitset implementation that uses a direct technique (based on
     masks) for counting the number of bits set in a word.  */

  next = 0;
  for (count = 0; (num = bitset_list (src, list, BITSET_LIST_SIZE, &next));
       count += num)
    continue;

  return count;
}


/* DST = SRC.  Return non-zero if DST != SRC.
   This is a fallback for the case where SRC and DST are different
   bitset types.  */
int
bitset_copy_ (bitset dst, bitset src)
{
  bitset_bindex i;
  bitset_iterator iter;

  /* Convert bitset types.  We assume that the DST bitset
     is large enough to hold the SRC bitset.  */
  bitset_zero (dst);
  BITSET_FOR_EACH (iter, src, i, 0)
  {
     bitset_set (dst, i);
  };

  return 1;
}


/* This is a fallback for implementations that do not support
   four operand operations.  */
static inline int
bitset_op4_cmp (bitset dst, bitset src1, bitset src2, bitset src3,
		enum bitset_ops op)
{
  int changed = 0;
  int stats_enabled_save;
  bitset tmp;

  /* Create temporary bitset.  */
  stats_enabled_save = bitset_stats_enabled;
  bitset_stats_enabled = 0;
  tmp = bitset_alloc (0, bitset_type_get (dst));
  bitset_stats_enabled = stats_enabled_save;

  switch (op)
    {
    case BITSET_OP_OR_AND:
      bitset_or (tmp, src1, src2);
      changed = bitset_and_cmp (dst, src3, tmp);
      break;

    case BITSET_OP_AND_OR:
      bitset_and (tmp, src1, src2);
      changed = bitset_or_cmp (dst, src3, tmp);
      break;

    case BITSET_OP_ANDN_OR:
      bitset_andn (tmp, src1, src2);
      changed = bitset_or_cmp (dst, src3, tmp);
      break;

    default:
      abort ();
    }

  bitset_free (tmp);
  return changed;
}


/* DST = (SRC1 & SRC2) | SRC3.  */
void
bitset_and_or_ (bitset dst, bitset src1, bitset src2, bitset src3)
{
  bitset_and_or_cmp_ (dst, src1, src2, src3);
}


/* DST = (SRC1 & SRC2) | SRC3.  Return non-zero if
   DST != (SRC1 & SRC2) | SRC3.  */
int
bitset_and_or_cmp_ (bitset dst, bitset src1, bitset src2, bitset src3)
{
  return bitset_op4_cmp (dst, src1, src2, src3, BITSET_OP_AND_OR);
}


/* DST = (SRC1 & ~SRC2) | SRC3.  */
void
bitset_andn_or_ (bitset dst, bitset src1, bitset src2, bitset src3)
{
  bitset_andn_or_cmp_ (dst, src1, src2, src3);
}


/* DST = (SRC1 & ~SRC2) | SRC3.  Return non-zero if
   DST != (SRC1 & ~SRC2) | SRC3.  */
int
bitset_andn_or_cmp_ (bitset dst, bitset src1, bitset src2, bitset src3)
{
  return bitset_op4_cmp (dst, src1, src2, src3, BITSET_OP_ANDN_OR);
}


/* DST = (SRC1 | SRC2) & SRC3.  */
void
bitset_or_and_ (bitset dst, bitset src1, bitset src2, bitset src3)
{
  bitset_or_and_cmp_ (dst, src1, src2, src3);
}


/* DST = (SRC1 | SRC2) & SRC3.  Return non-zero if
   DST != (SRC1 | SRC2) & SRC3.  */
int
bitset_or_and_cmp_ (bitset dst, bitset src1, bitset src2, bitset src3)
{
  return bitset_op4_cmp (dst, src1, src2, src3, BITSET_OP_OR_AND);
}


/* Function to be called from debugger to print bitset.  */
void
debug_bitset (bitset bset)
{
  if (bset)
    bitset_print (stderr, bset, 1);
}
