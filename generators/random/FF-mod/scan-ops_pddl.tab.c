/* A Bison parser, made by GNU Bison 1.875.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0

/* If NAME_PREFIX is specified substitute the variables and functions
   names.  */
#define yyparse ops_pddlparse
#define yylex   ops_pddllex
#define yyerror ops_pddlerror
#define yylval  ops_pddllval
#define yychar  ops_pddlchar
#define yydebug ops_pddldebug
#define yynerrs ops_pddlnerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DEFINE_TOK = 258,
     DOMAIN_TOK = 259,
     REQUIREMENTS_TOK = 260,
     TYPES_TOK = 261,
     EITHER_TOK = 262,
     CONSTANTS_TOK = 263,
     PREDICATES_TOK = 264,
     ACTION_TOK = 265,
     VARS_TOK = 266,
     IMPLIES_TOK = 267,
     PRECONDITION_TOK = 268,
     PARAMETERS_TOK = 269,
     EFFECT_TOK = 270,
     EQ_TOK = 271,
     AND_TOK = 272,
     NOT_TOK = 273,
     WHEN_TOK = 274,
     FORALL_TOK = 275,
     IMPLY_TOK = 276,
     OR_TOK = 277,
     EXISTS_TOK = 278,
     NAME = 279,
     VARIABLE = 280,
     TYPE = 281,
     OPEN_PAREN = 282,
     CLOSE_PAREN = 283
   };
#endif
#define DEFINE_TOK 258
#define DOMAIN_TOK 259
#define REQUIREMENTS_TOK 260
#define TYPES_TOK 261
#define EITHER_TOK 262
#define CONSTANTS_TOK 263
#define PREDICATES_TOK 264
#define ACTION_TOK 265
#define VARS_TOK 266
#define IMPLIES_TOK 267
#define PRECONDITION_TOK 268
#define PARAMETERS_TOK 269
#define EFFECT_TOK 270
#define EQ_TOK 271
#define AND_TOK 272
#define NOT_TOK 273
#define WHEN_TOK 274
#define FORALL_TOK 275
#define IMPLY_TOK 276
#define OR_TOK 277
#define EXISTS_TOK 278
#define NAME 279
#define VARIABLE 280
#define TYPE 281
#define OPEN_PAREN 282
#define CLOSE_PAREN 283




/* Copy the first part of user declarations.  */
#line 23 "scan-ops_pddl.y"

#ifdef YYDEBUG
  extern int yydebug=1;
#endif


#include <stdio.h>
#include <string.h> 
#include "ff.h"
#include "memory.h"
#include "parse.h"


#ifndef SCAN_ERR
#define SCAN_ERR
#define DOMDEF_EXPECTED            0
#define DOMAIN_EXPECTED            1
#define DOMNAME_EXPECTED           2
#define LBRACKET_EXPECTED          3
#define RBRACKET_EXPECTED          4
#define DOMDEFS_EXPECTED           5
#define REQUIREM_EXPECTED          6
#define TYPEDLIST_EXPECTED         7
#define LITERAL_EXPECTED           8
#define PRECONDDEF_UNCORRECT       9
#define TYPEDEF_EXPECTED          10
#define CONSTLIST_EXPECTED        11
#define PREDDEF_EXPECTED          12 
#define NAME_EXPECTED             13
#define VARIABLE_EXPECTED         14
#define ACTIONFUNCTOR_EXPECTED    15
#define ATOM_FORMULA_EXPECTED     16
#define EFFECT_DEF_EXPECTED       17
#define NEG_FORMULA_EXPECTED      18
#define NOT_SUPPORTED             19
#define ACTION                    20
#endif


#define NAME_STR "name\0"
#define VARIABLE_STR "variable\0"
#define STANDARD_TYPE "OBJECT\0"
 

static char *serrmsg[] = {
  "domain definition expected",
  "'domain' expected",
  "domain name expected",
  "'(' expected",
  "')' expected",
  "additional domain definitions expected",
  "requirements (e.g. ':STRIPS') expected",
  "typed list of <%s> expected",
  "literal expected",
  "uncorrect precondition definition",
  "type definition expected",
  "list of constants expected",
  "predicate definition expected",
  "<name> expected",
  "<variable> expected",
  "action functor expected",
  "atomic formula expected",
  "effect definition expected",
  "negated atomic formula expected",
  "requirement %s not supported by this IPP version",  
  "action definition is not correct",
  NULL
};


/* void opserr( int errno, char *par ); */


static int sact_err;
static char *sact_err_par = NULL;
static PlOperator *scur_op = NULL;
static Bool sis_negated = FALSE;


int supported( char *str )

{

  int i;
  char * sup[] = { ":STRIPS", ":NEGATION", ":NEGATIVE-PRECONDITIONS", ":EQUALITY",":TYPING", 
		   ":CONDITIONAL-EFFECTS", ":DISJUNCTIVE-PRECONDITIONS", 
		   ":EXISTENTIAL-PRECONDITIONS", ":UNIVERSAL-PRECONDITIONS", 
		   ":QUANTIFIED-PRECONDITIONS", ":ADL",
		   NULL };     

  for (i=0; NULL != sup[i]; i++) {
    if ( SAME == strcmp(sup[i], str) ) {
      return TRUE;
    }
  }
  
  return FALSE;

}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 129 "scan-ops_pddl.y"
typedef union YYSTYPE {

  char string[MAX_LENGTH];
  char *pstring;
  PlNode *pPlNode;
  FactList *pFactList;
  TokenList *pTokenList;
  TypedList *pTypedList;

} YYSTYPE;
/* Line 186 of yacc.c.  */
#line 253 "scan-ops_pddl.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 265 "scan-ops_pddl.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   129

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  29
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  39
/* YYNRULES -- Number of rules. */
#define YYNRULES  72
/* YYNRULES -- Number of states. */
#define YYNSTATES  158

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     4,     7,     8,    14,    19,    21,    24,
      27,    30,    33,    36,    37,    43,    44,    45,    52,    53,
      54,    62,    63,    64,    68,    69,    75,    76,    82,    83,
      84,    93,    94,    99,   100,   106,   107,   112,   113,   118,
     120,   125,   130,   135,   141,   149,   157,   158,   161,   163,
     168,   176,   182,   183,   186,   191,   193,   198,   203,   204,
     207,   209,   211,   213,   216,   218,   219,   225,   229,   232,
     233,   239,   243
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      30,     0,    -1,    -1,    31,    32,    -1,    -1,    27,     3,
      34,    33,    35,    -1,    27,     4,    24,    28,    -1,    28,
      -1,    40,    35,    -1,    47,    35,    -1,    45,    35,    -1,
      49,    35,    -1,    36,    35,    -1,    -1,    27,     9,    38,
      37,    28,    -1,    -1,    -1,    27,    24,    67,    28,    39,
      38,    -1,    -1,    -1,    27,     5,    41,    24,    42,    43,
      28,    -1,    -1,    -1,    24,    44,    43,    -1,    -1,    27,
       6,    46,    66,    28,    -1,    -1,    27,     8,    48,    66,
      28,    -1,    -1,    -1,    27,    10,    50,    24,    51,    52,
      53,    28,    -1,    -1,    14,    27,    67,    28,    -1,    -1,
      11,    27,    67,    28,    53,    -1,    -1,    13,    56,    54,
      53,    -1,    -1,    15,    58,    55,    53,    -1,    60,    -1,
      27,    17,    57,    28,    -1,    27,    22,    57,    28,    -1,
      27,    18,    56,    28,    -1,    27,    21,    56,    56,    28,
      -1,    27,    23,    27,    67,    28,    56,    28,    -1,    27,
      20,    27,    67,    28,    56,    28,    -1,    -1,    56,    57,
      -1,    60,    -1,    27,    17,    59,    28,    -1,    27,    20,
      27,    67,    28,    58,    28,    -1,    27,    19,    56,    58,
      28,    -1,    -1,    58,    59,    -1,    27,    18,    61,    28,
      -1,    61,    -1,    27,    65,    62,    28,    -1,    27,    16,
      62,    28,    -1,    -1,    63,    62,    -1,    24,    -1,    25,
      -1,    24,    -1,    24,    64,    -1,    24,    -1,    -1,    24,
       7,    64,    28,    66,    -1,    24,    26,    66,    -1,    24,
      66,    -1,    -1,    25,     7,    64,    28,    67,    -1,    25,
      26,    67,    -1,    25,    67,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   185,   185,   185,   196,   195,   209,   219,   221,   223,
     225,   227,   229,   236,   235,   245,   248,   247,   277,   281,
     276,   292,   296,   295,   309,   308,   322,   321,   337,   341,
     336,   355,   359,   373,   376,   395,   394,   401,   400,   415,
     428,   434,   440,   446,   456,   471,   491,   495,   508,   521,
     527,   542,   561,   565,   577,   583,   592,   599,   612,   614,
     625,   631,   641,   648,   660,   671,   673,   683,   694,   714,
     716,   725,   736
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DEFINE_TOK", "DOMAIN_TOK", 
  "REQUIREMENTS_TOK", "TYPES_TOK", "EITHER_TOK", "CONSTANTS_TOK", 
  "PREDICATES_TOK", "ACTION_TOK", "VARS_TOK", "IMPLIES_TOK", 
  "PRECONDITION_TOK", "PARAMETERS_TOK", "EFFECT_TOK", "EQ_TOK", "AND_TOK", 
  "NOT_TOK", "WHEN_TOK", "FORALL_TOK", "IMPLY_TOK", "OR_TOK", 
  "EXISTS_TOK", "NAME", "VARIABLE", "TYPE", "OPEN_PAREN", "CLOSE_PAREN", 
  "$accept", "file", "@1", "domain_definition", "@2", "domain_name", 
  "optional_domain_defs", "predicates_def", "@3", "predicates_list", "@4", 
  "require_def", "@5", "@6", "require_key_star", "@7", "types_def", "@8", 
  "constants_def", "@9", "action_def", "@10", "@11", "param_def", 
  "action_def_body", "@12", "@13", "adl_goal_description", 
  "adl_goal_description_star", "adl_effect", "adl_effect_star", 
  "literal_term", "atomic_formula_term", "term_star", "term", "name_plus", 
  "predicate", "typed_list_name", "typed_list_variable", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    29,    31,    30,    33,    32,    34,    35,    35,    35,
      35,    35,    35,    37,    36,    38,    39,    38,    41,    42,
      40,    43,    44,    43,    46,    45,    48,    47,    50,    51,
      49,    52,    52,    53,    53,    54,    53,    55,    53,    56,
      56,    56,    56,    56,    56,    56,    57,    57,    58,    58,
      58,    58,    59,    59,    60,    60,    61,    61,    62,    62,
      63,    63,    64,    64,    65,    66,    66,    66,    66,    67,
      67,    67,    67
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     2,     0,     5,     4,     1,     2,     2,
       2,     2,     2,     0,     5,     0,     0,     6,     0,     0,
       7,     0,     0,     3,     0,     5,     0,     5,     0,     0,
       8,     0,     4,     0,     5,     0,     4,     0,     4,     1,
       4,     4,     4,     5,     7,     7,     0,     2,     1,     4,
       7,     5,     0,     2,     4,     1,     4,     4,     0,     2,
       1,     1,     1,     2,     1,     0,     5,     3,     2,     0,
       5,     3,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       2,     0,     0,     1,     0,     3,     0,     0,     4,     0,
       0,     0,     0,     7,     5,     0,     0,     0,     0,     0,
       6,    18,    24,    26,    15,    28,    12,     8,    10,     9,
      11,     0,    65,    65,     0,    13,     0,    19,    65,     0,
       0,    69,     0,    29,    21,     0,    65,    68,    25,    27,
      69,     0,    14,    31,    22,     0,    62,     0,    67,     0,
      69,    72,    16,     0,    33,    21,    20,    63,    65,     0,
      71,    15,    69,     0,     0,     0,     0,    23,    66,    69,
      17,     0,    69,     0,    35,    39,    55,     0,    37,    48,
      30,    70,    32,     0,    58,    46,     0,     0,     0,    46,
       0,    64,    58,    33,    52,     0,     0,     0,    33,    33,
      60,    61,     0,    58,    46,     0,     0,     0,    69,     0,
       0,    69,     0,    36,    52,     0,     0,     0,     0,    69,
      38,    34,    57,    59,    47,    40,    42,    54,     0,     0,
      41,     0,    56,    53,    49,     0,     0,     0,    43,     0,
      51,     0,     0,     0,     0,    45,    44,    50
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     1,     2,     5,    10,     8,    14,    15,    42,    35,
      71,    16,    31,    44,    55,    65,    17,    32,    18,    33,
      19,    36,    53,    64,    76,   103,   108,   114,   115,   124,
     125,    85,    86,   112,   113,    57,   102,    39,    51
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -96
static const yysigned_char yypact[] =
{
     -96,    15,     1,   -96,    31,   -96,    12,    48,   -96,    42,
     -14,    34,    64,   -96,   -96,   -14,   -14,   -14,   -14,   -14,
     -96,   -96,   -96,   -96,    40,   -96,   -96,   -96,   -96,   -96,
     -96,    51,    52,    52,    56,   -96,    57,   -96,    -3,    54,
      55,    60,    65,   -96,    68,    70,    52,   -96,   -96,   -96,
      -1,    67,   -96,    82,   -96,    69,    70,    71,   -96,    70,
      60,   -96,   -96,    73,    38,    68,   -96,   -96,    52,    74,
     -96,    40,    60,    76,    77,    78,    79,   -96,   -96,    60,
     -96,    80,    60,    24,   -96,   -96,   -96,    41,   -96,   -96,
     -96,   -96,   -96,    81,    39,    77,    77,    83,    77,    77,
      84,   -96,    39,    38,    78,    85,    77,    86,    38,    38,
     -96,   -96,    87,    39,    77,    88,    89,    90,    60,    77,
      91,    60,    92,   -96,    78,    93,     3,    90,    78,    60,
     -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,    94,    95,
     -96,    96,   -96,   -96,   -96,    97,    98,    77,   -96,    77,
     -96,    78,    99,   100,   101,   -96,   -96,   -96
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -96,   -96,   -96,   -96,   -96,   -96,    72,   -96,   -96,    27,
     -96,   -96,   -96,   -96,    36,   -96,   -96,   -96,   -96,   -96,
     -96,   -96,   -96,   -96,   -72,   -96,   -96,   -63,   -94,   -73,
     -18,   -74,   -79,   -95,   -96,   -47,   -96,   -30,   -50
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
      61,    89,    88,    40,    45,   120,    59,   122,    47,    67,
      70,    84,    69,    12,    13,     3,    58,   117,   133,    94,
     134,    38,    81,    46,    50,    60,   127,   101,     4,    91,
      89,   123,    93,   116,     6,   119,   130,   131,    78,     7,
      94,    95,    96,   128,    97,    98,    99,   100,   101,    73,
      89,    74,     9,    75,    89,   145,   139,    94,   104,   105,
     106,   107,    20,   110,   111,   101,    11,    34,   138,    21,
      22,   141,    23,    24,    25,    37,    38,    89,   154,   146,
      41,    43,    48,    49,   152,    50,   153,    26,    27,    28,
      29,    30,    54,    52,    56,    62,    63,    66,    80,    68,
      72,    77,    79,    82,    83,    87,   143,    90,    92,   109,
     118,   121,   126,   129,     0,   132,   135,   136,   137,   140,
     142,   144,   147,   148,   149,   150,   151,   155,   156,   157
};

static const short yycheck[] =
{
      50,    75,    75,    33,     7,    99,     7,   102,    38,    56,
      60,    74,    59,    27,    28,     0,    46,    96,   113,    16,
     114,    24,    72,    26,    25,    26,   105,    24,    27,    79,
     104,   103,    82,    96,     3,    98,   108,   109,    68,    27,
      16,    17,    18,   106,    20,    21,    22,    23,    24,    11,
     124,    13,     4,    15,   128,   128,   119,    16,    17,    18,
      19,    20,    28,    24,    25,    24,    24,    27,   118,     5,
       6,   121,     8,     9,    10,    24,    24,   151,   151,   129,
      24,    24,    28,    28,   147,    25,   149,    15,    16,    17,
      18,    19,    24,    28,    24,    28,    14,    28,    71,    28,
      27,    65,    28,    27,    27,    27,   124,    28,    28,    28,
      27,    27,    27,    27,    -1,    28,    28,    28,    28,    28,
      28,    28,    28,    28,    28,    28,    28,    28,    28,    28
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    30,    31,     0,    27,    32,     3,    27,    34,     4,
      33,    24,    27,    28,    35,    36,    40,    45,    47,    49,
      28,     5,     6,     8,     9,    10,    35,    35,    35,    35,
      35,    41,    46,    48,    27,    38,    50,    24,    24,    66,
      66,    24,    37,    24,    42,     7,    26,    66,    28,    28,
      25,    67,    28,    51,    24,    43,    24,    64,    66,     7,
      26,    67,    28,    14,    52,    44,    28,    64,    28,    64,
      67,    39,    27,    11,    13,    15,    53,    43,    66,    28,
      38,    67,    27,    27,    56,    60,    61,    27,    58,    60,
      28,    67,    28,    67,    16,    17,    18,    20,    21,    22,
      23,    24,    65,    54,    17,    18,    19,    20,    55,    28,
      24,    25,    62,    63,    56,    57,    56,    61,    27,    56,
      57,    27,    62,    53,    58,    59,    27,    61,    56,    27,
      53,    53,    28,    62,    57,    28,    28,    28,    67,    56,
      28,    67,    28,    59,    28,    58,    67,    28,    28,    28,
      28,    28,    56,    56,    58,    28,    28,    28
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1

/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylineno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylineno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 185 "scan-ops_pddl.y"
    { 
  opserr( DOMDEF_EXPECTED, NULL ); 
;}
    break;

  case 4:
#line 196 "scan-ops_pddl.y"
    { 
;}
    break;

  case 5:
#line 199 "scan-ops_pddl.y"
    {
  if ( gcmd_line.display_info >= 1 ) {
    printf("\ndomain '%s' defined\n", gdomain_name);
  }
;}
    break;

  case 6:
#line 210 "scan-ops_pddl.y"
    { 
  gdomain_name = new_Token( strlen(yyvsp[-1].string)+1 );
  strcpy( gdomain_name, yyvsp[-1].string);
;}
    break;

  case 13:
#line 236 "scan-ops_pddl.y"
    {
;}
    break;

  case 14:
#line 239 "scan-ops_pddl.y"
    { 
;}
    break;

  case 15:
#line 245 "scan-ops_pddl.y"
    {;}
    break;

  case 16:
#line 248 "scan-ops_pddl.y"
    {

  TypedListList *tll;

  if ( gparse_predicates ) {
    tll = gparse_predicates;
    while ( tll->next ) {
      tll = tll->next;
    }
    tll->next = new_TypedListList();
    tll = tll->next;
  } else {
    tll = new_TypedListList();
    gparse_predicates = tll;
  }

  tll->predicate = new_Token( strlen( yyvsp[-2].string ) + 1);
  strcpy( tll->predicate, yyvsp[-2].string );

  tll->args = yyvsp[-1].pTypedList;

;}
    break;

  case 18:
#line 277 "scan-ops_pddl.y"
    { 
  opserr( REQUIREM_EXPECTED, NULL ); 
;}
    break;

  case 19:
#line 281 "scan-ops_pddl.y"
    { 
  if ( !supported( yyvsp[0].string ) ) {
    opserr( NOT_SUPPORTED, yyvsp[0].string );
    yyerror();
  }
;}
    break;

  case 22:
#line 296 "scan-ops_pddl.y"
    { 
  if ( !supported( yyvsp[0].string ) ) {
    opserr( NOT_SUPPORTED, yyvsp[0].string );
    yyerror();
  }
;}
    break;

  case 24:
#line 309 "scan-ops_pddl.y"
    { 
  opserr( TYPEDEF_EXPECTED, NULL ); 
;}
    break;

  case 25:
#line 313 "scan-ops_pddl.y"
    {
  gparse_types = yyvsp[-1].pTypedList;
;}
    break;

  case 26:
#line 322 "scan-ops_pddl.y"
    { 
  opserr( CONSTLIST_EXPECTED, NULL ); 
;}
    break;

  case 27:
#line 326 "scan-ops_pddl.y"
    {
  gparse_constants = yyvsp[-1].pTypedList;
;}
    break;

  case 28:
#line 337 "scan-ops_pddl.y"
    { 
  opserr( ACTION, NULL ); 
;}
    break;

  case 29:
#line 341 "scan-ops_pddl.y"
    { 
  scur_op = new_PlOperator( yyvsp[0].string );
;}
    break;

  case 30:
#line 345 "scan-ops_pddl.y"
    {
  scur_op->next = gloaded_ops;
  gloaded_ops = scur_op; 
;}
    break;

  case 31:
#line 355 "scan-ops_pddl.y"
    { 
  scur_op->params = NULL; 
;}
    break;

  case 32:
#line 360 "scan-ops_pddl.y"
    {
  TypedList *tl;
  scur_op->parse_params = yyvsp[-1].pTypedList;
  for (tl = scur_op->parse_params; tl; tl = tl->next) {
    /* to be able to distinguish params from :VARS 
     */
    scur_op->number_of_real_params++;
  }
;}
    break;

  case 34:
#line 377 "scan-ops_pddl.y"
    {
  TypedList *tl = NULL;

  /* add vars as parameters 
   */
  if ( scur_op->parse_params ) {
    for( tl = scur_op->parse_params; tl->next; tl = tl->next ) {
      /* empty, get to the end of list 
       */
    }
    tl->next = yyvsp[-2].pTypedList;
    tl = tl->next;
  } else {
    scur_op->parse_params = yyvsp[-2].pTypedList;
  }
;}
    break;

  case 35:
#line 395 "scan-ops_pddl.y"
    { 
  scur_op->preconds = yyvsp[0].pPlNode; 
;}
    break;

  case 37:
#line 401 "scan-ops_pddl.y"
    { 
  scur_op->effects = yyvsp[0].pPlNode; 
;}
    break;

  case 39:
#line 416 "scan-ops_pddl.y"
    { 
  if ( sis_negated ) {
    yyval.pPlNode = new_PlNode(NOT);
    yyval.pPlNode->sons = new_PlNode(ATOM);
    yyval.pPlNode->sons->atom = yyvsp[0].pTokenList;
    sis_negated = FALSE;
  } else {
    yyval.pPlNode = new_PlNode(ATOM);
    yyval.pPlNode->atom = yyvsp[0].pTokenList;
  }
;}
    break;

  case 40:
#line 429 "scan-ops_pddl.y"
    { 
  yyval.pPlNode = new_PlNode(AND);
  yyval.pPlNode->sons = yyvsp[-1].pPlNode;
;}
    break;

  case 41:
#line 435 "scan-ops_pddl.y"
    { 
  yyval.pPlNode = new_PlNode(OR);
  yyval.pPlNode->sons = yyvsp[-1].pPlNode;
;}
    break;

  case 42:
#line 441 "scan-ops_pddl.y"
    { 
  yyval.pPlNode = new_PlNode(NOT);
  yyval.pPlNode->sons = yyvsp[-1].pPlNode;
;}
    break;

  case 43:
#line 447 "scan-ops_pddl.y"
    { 
  PlNode *np = new_PlNode(NOT);
  np->sons = yyvsp[-2].pPlNode;
  np->next = yyvsp[-1].pPlNode;

  yyval.pPlNode = new_PlNode(OR);
  yyval.pPlNode->sons = np;
;}
    break;

  case 44:
#line 459 "scan-ops_pddl.y"
    { 

  PlNode *pln;

  pln = new_PlNode(EX);
  pln->parse_vars = yyvsp[-3].pTypedList;

  yyval.pPlNode = pln;
  pln->sons = yyvsp[-1].pPlNode;

;}
    break;

  case 45:
#line 474 "scan-ops_pddl.y"
    { 

  PlNode *pln;

  pln = new_PlNode(ALL);
  pln->parse_vars = yyvsp[-3].pTypedList;

  yyval.pPlNode = pln;
  pln->sons = yyvsp[-1].pPlNode;

;}
    break;

  case 46:
#line 491 "scan-ops_pddl.y"
    {
  yyval.pPlNode = NULL;
;}
    break;

  case 47:
#line 496 "scan-ops_pddl.y"
    {
  yyvsp[-1].pPlNode->next = yyvsp[0].pPlNode;
  yyval.pPlNode = yyvsp[-1].pPlNode;
;}
    break;

  case 48:
#line 509 "scan-ops_pddl.y"
    { 
  if ( sis_negated ) {
    yyval.pPlNode = new_PlNode(NOT);
    yyval.pPlNode->sons = new_PlNode(ATOM);
    yyval.pPlNode->sons->atom = yyvsp[0].pTokenList;
    sis_negated = FALSE;
  } else {
    yyval.pPlNode = new_PlNode(ATOM);
    yyval.pPlNode->atom = yyvsp[0].pTokenList;
  }
;}
    break;

  case 49:
#line 522 "scan-ops_pddl.y"
    { 
  yyval.pPlNode = new_PlNode(AND);
  yyval.pPlNode->sons = yyvsp[-1].pPlNode;
;}
    break;

  case 50:
#line 530 "scan-ops_pddl.y"
    { 

  PlNode *pln;

  pln = new_PlNode(ALL);
  pln->parse_vars = yyvsp[-3].pTypedList;

  yyval.pPlNode = pln;
  pln->sons = yyvsp[-1].pPlNode;

;}
    break;

  case 51:
#line 543 "scan-ops_pddl.y"
    {
  /* This will be conditional effects in FF representation, but here
   * a formula like (WHEN p q) will be saved as:
   *  [WHEN]
   *  [sons]
   *   /  \
   * [p]  [q]
   * That means, the first son is p, and the second one is q. 
   */
  yyval.pPlNode = new_PlNode(WHEN);
  yyvsp[-2].pPlNode->next = yyvsp[-1].pPlNode;
  yyval.pPlNode->sons = yyvsp[-2].pPlNode;
;}
    break;

  case 52:
#line 561 "scan-ops_pddl.y"
    { 
  yyval.pPlNode = NULL; 
;}
    break;

  case 53:
#line 566 "scan-ops_pddl.y"
    {
  yyvsp[-1].pPlNode->next = yyvsp[0].pPlNode;
  yyval.pPlNode = yyvsp[-1].pPlNode;
;}
    break;

  case 54:
#line 578 "scan-ops_pddl.y"
    { 
  yyval.pTokenList = yyvsp[-1].pTokenList;
  sis_negated = TRUE;
;}
    break;

  case 55:
#line 584 "scan-ops_pddl.y"
    {
  yyval.pTokenList = yyvsp[0].pTokenList;
;}
    break;

  case 56:
#line 593 "scan-ops_pddl.y"
    { 
  yyval.pTokenList = new_TokenList();
  yyval.pTokenList->item = yyvsp[-2].pstring;
  yyval.pTokenList->next = yyvsp[-1].pTokenList;
;}
    break;

  case 57:
#line 600 "scan-ops_pddl.y"
    {
  yyval.pTokenList = new_TokenList();
  yyval.pTokenList->item = new_Token( 5 );
  yyval.pTokenList->item = "=";
  yyval.pTokenList->next = yyvsp[-1].pTokenList;
;}
    break;

  case 58:
#line 612 "scan-ops_pddl.y"
    { yyval.pTokenList = NULL; ;}
    break;

  case 59:
#line 615 "scan-ops_pddl.y"
    {
  yyval.pTokenList = new_TokenList();
  yyval.pTokenList->item = yyvsp[-1].pstring;
  yyval.pTokenList->next = yyvsp[0].pTokenList;
;}
    break;

  case 60:
#line 626 "scan-ops_pddl.y"
    { 
  yyval.pstring = new_Token( strlen(yyvsp[0].string)+1 );
  strcpy( yyval.pstring, yyvsp[0].string );
;}
    break;

  case 61:
#line 632 "scan-ops_pddl.y"
    { 
  yyval.pstring = new_Token( strlen(yyvsp[0].string)+1 );
  strcpy( yyval.pstring, yyvsp[0].string );
;}
    break;

  case 62:
#line 642 "scan-ops_pddl.y"
    {
  yyval.pTokenList = new_TokenList();
  yyval.pTokenList->item = new_Token( strlen(yyvsp[0].string)+1 );
  strcpy( yyval.pTokenList->item, yyvsp[0].string );
;}
    break;

  case 63:
#line 649 "scan-ops_pddl.y"
    {
  yyval.pTokenList = new_TokenList();
  yyval.pTokenList->item = new_Token( strlen(yyvsp[-1].string)+1 );
  strcpy( yyval.pTokenList->item, yyvsp[-1].string );
  yyval.pTokenList->next = yyvsp[0].pTokenList;
;}
    break;

  case 64:
#line 661 "scan-ops_pddl.y"
    { 
  yyval.pstring = new_Token( strlen(yyvsp[0].string)+1 );
  strcpy( yyval.pstring, yyvsp[0].string );
;}
    break;

  case 65:
#line 671 "scan-ops_pddl.y"
    { yyval.pTypedList = NULL; ;}
    break;

  case 66:
#line 674 "scan-ops_pddl.y"
    { 

  yyval.pTypedList = new_TypedList();
  yyval.pTypedList->name = new_Token( strlen(yyvsp[-4].string)+1 );
  strcpy( yyval.pTypedList->name, yyvsp[-4].string );
  yyval.pTypedList->type = yyvsp[-2].pTokenList;
  yyval.pTypedList->next = yyvsp[0].pTypedList;
;}
    break;

  case 67:
#line 684 "scan-ops_pddl.y"
    {
  yyval.pTypedList = new_TypedList();
  yyval.pTypedList->name = new_Token( strlen(yyvsp[-2].string)+1 );
  strcpy( yyval.pTypedList->name, yyvsp[-2].string );
  yyval.pTypedList->type = new_TokenList();
  yyval.pTypedList->type->item = new_Token( strlen(yyvsp[-1].string)+1 );
  strcpy( yyval.pTypedList->type->item, yyvsp[-1].string );
  yyval.pTypedList->next = yyvsp[0].pTypedList;
;}
    break;

  case 68:
#line 695 "scan-ops_pddl.y"
    {
  yyval.pTypedList = new_TypedList();
  yyval.pTypedList->name = new_Token( strlen(yyvsp[-1].string)+1 );
  strcpy( yyval.pTypedList->name, yyvsp[-1].string );
  if ( yyvsp[0].pTypedList ) {/* another element (already typed) is following */
    yyval.pTypedList->type = copy_TokenList( yyvsp[0].pTypedList->type );
  } else {/* no further element - it must be an untyped list */
    yyval.pTypedList->type = new_TokenList();
    yyval.pTypedList->type->item = new_Token( strlen(STANDARD_TYPE)+1 );
    strcpy( yyval.pTypedList->type->item, STANDARD_TYPE );
  }
  yyval.pTypedList->next = yyvsp[0].pTypedList;
;}
    break;

  case 69:
#line 714 "scan-ops_pddl.y"
    { yyval.pTypedList = NULL; ;}
    break;

  case 70:
#line 717 "scan-ops_pddl.y"
    { 
  yyval.pTypedList = new_TypedList();
  yyval.pTypedList->name = new_Token( strlen(yyvsp[-4].string)+1 );
  strcpy( yyval.pTypedList->name, yyvsp[-4].string );
  yyval.pTypedList->type = yyvsp[-2].pTokenList;
  yyval.pTypedList->next = yyvsp[0].pTypedList;
;}
    break;

  case 71:
#line 726 "scan-ops_pddl.y"
    {
  yyval.pTypedList = new_TypedList();
  yyval.pTypedList->name = new_Token( strlen(yyvsp[-2].string)+1 );
  strcpy( yyval.pTypedList->name, yyvsp[-2].string );
  yyval.pTypedList->type = new_TokenList();
  yyval.pTypedList->type->item = new_Token( strlen(yyvsp[-1].string)+1 );
  strcpy( yyval.pTypedList->type->item, yyvsp[-1].string );
  yyval.pTypedList->next = yyvsp[0].pTypedList;
;}
    break;

  case 72:
#line 737 "scan-ops_pddl.y"
    {
  yyval.pTypedList = new_TypedList();
  yyval.pTypedList->name = new_Token( strlen(yyvsp[-1].string)+1 );
  strcpy( yyval.pTypedList->name, yyvsp[-1].string );
  if ( yyvsp[0].pTypedList ) {/* another element (already typed) is following */
    yyval.pTypedList->type = copy_TokenList( yyvsp[0].pTypedList->type );
  } else {/* no further element - it must be an untyped list */
    yyval.pTypedList->type = new_TokenList();
    yyval.pTypedList->type->item = new_Token( strlen(STANDARD_TYPE)+1 );
    strcpy( yyval.pTypedList->type->item, STANDARD_TYPE );
  }
  yyval.pTypedList->next = yyvsp[0].pTypedList;
;}
    break;


    }

/* Line 991 of yacc.c.  */
#line 1823 "scan-ops_pddl.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("syntax error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab2;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:

  /* Suppress GCC warning that yyerrlab1 is unused when no action
     invokes YYERROR.  */
#if defined (__GNUC_MINOR__) && 2093 <= (__GNUC__ * 1000 + __GNUC_MINOR__)
  __attribute__ ((__unused__))
#endif


  goto yyerrlab2;


/*---------------------------------------------------------------.
| yyerrlab2 -- pop states until the error token can be shifted.  |
`---------------------------------------------------------------*/
yyerrlab2:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 737 "scan-ops_pddl.y"

#include "lex.ops_pddl.c"


/**********************************************************************
 * Functions
 **********************************************************************/

/* 
 * call	bison -pops -bscan-ops scan-ops.y
 */

/*void opserr( int errno, char *par )*/

/*{*/

/*   sact_err = errno; */

/*   if ( sact_err_par ) { */
/*     free(sact_err_par); */
/*   } */
/*   if ( par ) { */
/*     sact_err_par = new_Token(strlen(par)+1); */
/*     strcpy(sact_err_par, par); */
/*   } else { */
/*     sact_err_par = NULL; */
/*   } */

/*}*/
  


int yyerror( char *msg )

{

  fflush(stdout);
  fprintf(stderr, "\n%s: syntax error in line %d, '%s':\n", 
	  gact_filename, lineno, yytext);

  if ( NULL != sact_err_par ) {
    fprintf(stderr, "%s %s\n", serrmsg[sact_err], sact_err_par);
  } else {
    fprintf(stderr, "%s\n", serrmsg[sact_err]);
  }

  exit( 1 );

}



void load_ops_file( char *filename )

{

  FILE * fp;/* pointer to input files */
  char tmp[MAX_LENGTH] = "";

  /* open operator file 
   */
  if( ( fp = fopen( filename, "r" ) ) == NULL ) {
    sprintf(tmp, "\nff: can't find operator file: %s\n\n", filename );
    perror(tmp);
    exit( 1 );
  }

  gact_filename = filename;
  lineno = 1; 
  yyin = fp;

  yyparse();

  fclose( fp );/* and close file again */

}


