
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 3 "parser.y"

#include "stdio.h"
#include "math.h"
#include "string.h"
#include "def.h"
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
void yyerror(const char* fmt, ...);
void display(struct node *,int);


/* Line 189 of yacc.c  */
#line 86 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     RELOP = 259,
     TYPE = 260,
     INT = 261,
     FLOAT = 262,
     DOUBLE = 263,
     CHAR = 264,
     STRING = 265,
     VOID = 266,
     LP = 267,
     RP = 268,
     LC = 269,
     RC = 270,
     LB = 271,
     RB = 272,
     DOT = 273,
     SEMI = 274,
     COMMA = 275,
     PLUS_SELF = 276,
     MINUS_SELF = 277,
     PLUS = 278,
     MINUS = 279,
     STAR = 280,
     DIV = 281,
     ASSIGNOP = 282,
     ASSIGNOP_PLUS = 283,
     ASSIGNOP_MINUS = 284,
     ASSIGNOP_STAR = 285,
     ASSIGNOP_DIV = 286,
     AND = 287,
     OR = 288,
     NOT = 289,
     VARDEC = 290,
     IF = 291,
     ELSE = 292,
     WHILE = 293,
     RETURN = 294,
     FOR = 295,
     STRUCT = 296,
     BREAK = 297,
     CONTINUE = 298,
     UMINUS = 299,
     LOWER_THEN_ELSE = 300
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 15 "parser.y"

	int    array_len;
	int    type_int;
	float  type_float;
	double type_double;
    char   type_char;
    char   type_string[32];
	char   type_void[5];
	char   type_id[32];
	char   type_struct[32];
	struct node *ptr;



/* Line 214 of yacc.c  */
#line 182 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 207 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   534

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNRULES -- Number of states.  */
#define YYNSTATES  142

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    13,    19,    23,    26,
      28,    32,    34,    36,    41,    46,    50,    52,    56,    59,
      64,    65,    68,    71,    73,    77,    83,    91,    97,   103,
     106,   109,   115,   119,   120,   123,   127,   129,   133,   135,
     139,   143,   147,   151,   155,   159,   164,   167,   170,   174,
     179,   182,   185,   189,   194,   198,   203,   207,   210,   213,
     218,   222,   227,   231,   233,   235,   237,   239,   241,   243,
     247
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      47,     0,    -1,    48,    -1,    -1,    49,    48,    -1,    51,
      50,    19,    -1,    51,    52,    27,    64,    19,    -1,    51,
      53,    56,    -1,     1,    19,    -1,    52,    -1,    52,    20,
      50,    -1,     5,    -1,     3,    -1,    52,    16,    64,    17,
      -1,     3,    12,    54,    13,    -1,     3,    12,    13,    -1,
      55,    -1,    55,    20,    54,    -1,    51,    52,    -1,    14,
      60,    57,    15,    -1,    -1,    58,    57,    -1,    64,    19,
      -1,    56,    -1,    39,    64,    19,    -1,    36,    12,    64,
      13,    58,    -1,    36,    12,    64,    13,    58,    37,    58,
      -1,    38,    12,    64,    13,    58,    -1,    40,    12,    59,
      13,    58,    -1,    42,    19,    -1,    43,    19,    -1,    64,
      19,    64,    19,    64,    -1,    19,    64,    19,    -1,    -1,
      61,    60,    -1,    51,    62,    19,    -1,    63,    -1,    63,
      20,    62,    -1,    52,    -1,    52,    27,    64,    -1,    64,
      27,    64,    -1,    64,    32,    64,    -1,    64,    33,    64,
      -1,    64,     4,    64,    -1,    64,    23,    64,    -1,    64,
      23,    27,    64,    -1,    64,    21,    -1,    21,    64,    -1,
      64,    24,    64,    -1,    64,    24,    27,    64,    -1,    64,
      22,    -1,    22,    64,    -1,    64,    25,    64,    -1,    64,
      25,    27,    64,    -1,    64,    26,    64,    -1,    64,    26,
      27,    64,    -1,    12,    64,    13,    -1,    24,    64,    -1,
      34,    64,    -1,     3,    12,    65,    13,    -1,     3,    12,
      13,    -1,    64,    16,    64,    17,    -1,    64,    18,     3,
      -1,     3,    -1,     6,    -1,     7,    -1,     8,    -1,     9,
      -1,    10,    -1,    64,    20,    65,    -1,    64,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    75,    75,    77,    78,    80,    81,    82,    83,    85,
      86,    88,    90,    91,    93,    94,    97,    98,   100,   103,
     105,   106,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   118,   119,   122,   123,   125,   127,   128,   130,   131,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   163,
     164
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "RELOP", "TYPE", "INT", "FLOAT",
  "DOUBLE", "CHAR", "STRING", "VOID", "LP", "RP", "LC", "RC", "LB", "RB",
  "DOT", "SEMI", "COMMA", "PLUS_SELF", "MINUS_SELF", "PLUS", "MINUS",
  "STAR", "DIV", "ASSIGNOP", "ASSIGNOP_PLUS", "ASSIGNOP_MINUS",
  "ASSIGNOP_STAR", "ASSIGNOP_DIV", "AND", "OR", "NOT", "VARDEC", "IF",
  "ELSE", "WHILE", "RETURN", "FOR", "STRUCT", "BREAK", "CONTINUE",
  "UMINUS", "LOWER_THEN_ELSE", "$accept", "program", "ExtDefList",
  "ExtDef", "ExtDecList", "Specifier", "VarDec", "FuncDec", "VarList",
  "ParamDec", "CompSt", "StmList", "Stmt", "ForDec", "DefList", "Def",
  "DecList", "Dec", "Exp", "Args", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    48,    48,    49,    49,    49,    49,    50,
      50,    51,    52,    52,    53,    53,    54,    54,    55,    56,
      57,    57,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    59,    59,    60,    60,    61,    62,    62,    63,    63,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    65,
      65
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     5,     3,     2,     1,
       3,     1,     1,     4,     4,     3,     1,     3,     2,     4,
       0,     2,     2,     1,     3,     5,     7,     5,     5,     2,
       2,     5,     3,     0,     2,     3,     1,     3,     1,     3,
       3,     3,     3,     3,     3,     4,     2,     2,     3,     4,
       2,     2,     3,     4,     3,     4,     3,     2,     2,     4,
       3,     4,     3,     1,     1,     1,     1,     1,     1,     3,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    11,     0,     2,     0,     0,     8,     1,     4,
      12,     0,     9,     0,     0,     5,     0,     0,     0,    33,
       7,    15,     0,     0,    16,    63,    64,    65,    66,    67,
      68,     0,     0,     0,     0,     0,     0,    12,    10,     9,
       0,     0,    20,    33,    18,    14,     0,     0,     0,    47,
      51,    57,    58,     0,     0,    13,     0,    46,    50,     0,
       0,     0,     0,     0,     0,     0,     6,    38,     0,    36,
       0,     0,     0,     0,     0,     0,    23,     0,    20,     0,
      34,    17,    60,    70,     0,    56,    43,     0,    62,     0,
      44,     0,    48,     0,    52,     0,    54,    40,    41,    42,
       0,    35,     0,     0,     0,     0,     0,    29,    30,    19,
      21,    22,     0,    59,    61,    45,    49,    53,    55,    39,
      37,     0,     0,    24,     0,     0,     0,    69,     0,     0,
       0,     0,     0,    25,    27,    32,    28,     0,     0,     0,
      26,    31
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    11,     6,    67,    13,    23,    24,
      76,    77,    78,   125,    42,    43,    68,    69,    79,    84
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -103
static const yytype_int16 yypact[] =
{
      58,   -14,  -103,     3,  -103,    58,    31,  -103,  -103,  -103,
      28,    22,    37,    38,     7,  -103,   209,    39,   209,    46,
    -103,  -103,    39,    41,    40,    49,  -103,  -103,  -103,  -103,
    -103,   209,   209,   209,   209,   209,   223,  -103,  -103,     8,
     247,    39,    91,    46,    54,  -103,    46,     1,   271,    88,
      88,    88,    88,   209,   209,  -103,    69,  -103,  -103,    59,
     129,   137,   166,   209,   209,   209,  -103,     5,    55,    56,
      66,    70,   209,    73,    72,    76,  -103,    74,    91,   295,
    -103,  -103,  -103,   319,    79,  -103,   236,   332,  -103,   209,
     260,   209,   260,   209,    88,   209,    88,   489,   284,   502,
     209,  -103,    39,   209,   209,   356,   189,  -103,  -103,  -103,
    -103,  -103,   209,  -103,  -103,   489,   489,   489,   489,   489,
    -103,   380,   404,  -103,   209,    89,   428,  -103,    91,    91,
     452,    91,   209,    77,  -103,  -103,  -103,   476,    91,   209,
    -103,   489
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -103,  -103,   102,  -103,    94,   -13,    33,  -103,    71,  -103,
     105,    42,  -102,  -103,    78,  -103,    17,  -103,   -16,    10
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -4
static const yytype_int16 yytable[] =
{
      36,    22,    40,     8,    25,     7,    41,    26,    27,    28,
      29,    30,     2,    31,    82,    48,    49,    50,    51,    52,
      21,    16,    32,    33,    16,    34,   133,   134,    17,   136,
      41,    83,   100,    22,    10,    35,   140,    86,    87,    12,
      14,    15,    37,    90,    92,    94,    96,    97,    98,    99,
      39,     2,    19,    16,    45,    44,   105,    17,    -3,     1,
      46,    47,    25,     2,    18,    26,    27,    28,    29,    30,
      16,    31,    88,   115,   101,   116,   102,   117,   103,   118,
      32,    33,   104,    34,   119,   106,    89,   121,   122,   109,
     126,   107,   113,    35,    25,   108,    83,    26,    27,    28,
      29,    30,   131,    31,    54,    19,    56,     9,   130,    57,
      58,    38,    32,    33,   138,    34,   137,    81,    20,   120,
     110,    80,   127,   141,     0,    35,     0,    70,     0,    71,
      72,    73,    25,    74,    75,    26,    27,    28,    29,    30,
      25,    31,     0,    26,    27,    28,    29,    30,     0,    31,
      32,    33,     0,    34,     0,     0,    91,     0,    32,    33,
       0,    34,     0,    35,    93,     0,     0,     0,     0,    25,
       0,    35,    26,    27,    28,    29,    30,     0,    31,     0,
       0,     0,     0,     0,     0,     0,     0,    32,    33,     0,
      34,     0,    25,    95,     0,    26,    27,    28,    29,    30,
      35,    31,     0,     0,     0,     0,     0,     0,   124,     0,
      32,    33,    25,    34,     0,    26,    27,    28,    29,    30,
       0,    31,     0,    35,     0,     0,     0,    53,     0,     0,
      32,    33,     0,    34,     0,     0,     0,     0,     0,    54,
      55,    56,     0,    35,    57,    58,    59,    60,    61,    62,
      63,    53,    54,     0,    56,    64,    65,    57,    58,    59,
      60,    61,    62,    54,     0,    56,    66,     0,    57,    58,
      59,    60,    61,    62,    63,    53,    54,     0,    56,    64,
      65,    57,    58,     0,    85,    61,    62,    54,    53,    56,
       0,     0,    57,    58,    59,    60,    61,    62,    63,    53,
      54,     0,    56,    64,    65,    57,    58,    59,    60,    61,
      62,    54,     0,    56,   111,     0,    57,    58,    59,    60,
      61,    62,    63,    53,     0,     0,     0,    64,    65,     0,
       0,     0,     0,     0,     0,    54,    53,    56,     0,   112,
      57,    58,    59,    60,    61,    62,    63,     0,    54,   114,
      56,    64,    65,    57,    58,    59,    60,    61,    62,    63,
      53,     0,     0,     0,    64,    65,     0,     0,     0,     0,
       0,     0,    54,     0,    56,   123,     0,    57,    58,    59,
      60,    61,    62,    63,    53,     0,     0,     0,    64,    65,
       0,     0,     0,   128,     0,     0,    54,     0,    56,     0,
       0,    57,    58,    59,    60,    61,    62,    63,    53,     0,
       0,     0,    64,    65,     0,     0,     0,   129,     0,     0,
      54,     0,    56,     0,     0,    57,    58,    59,    60,    61,
      62,    63,    53,     0,     0,     0,    64,    65,     0,     0,
       0,     0,     0,     0,    54,     0,    56,   132,     0,    57,
      58,    59,    60,    61,    62,    63,    53,     0,     0,     0,
      64,    65,     0,     0,     0,     0,     0,     0,    54,     0,
      56,   135,     0,    57,    58,    59,    60,    61,    62,    63,
      53,     0,     0,     0,    64,    65,     0,     0,     0,     0,
       0,     0,    54,    53,    56,   139,     0,    57,    58,    59,
      60,    61,    62,    63,     0,    54,    53,    56,    64,    65,
      57,    58,    59,    60,    61,    62,    63,     0,    54,     0,
      56,    64,    65,    57,    58,    59,    60,    61,    62,     0,
       0,     0,     0,     0,    64
};

static const yytype_int16 yycheck[] =
{
      16,    14,    18,     0,     3,    19,    19,     6,     7,     8,
       9,    10,     5,    12,    13,    31,    32,    33,    34,    35,
      13,    16,    21,    22,    16,    24,   128,   129,    20,   131,
      43,    47,    27,    46,     3,    34,   138,    53,    54,     6,
      12,    19,     3,    59,    60,    61,    62,    63,    64,    65,
      17,     5,    14,    16,    13,    22,    72,    20,     0,     1,
      20,    12,     3,     5,    27,     6,     7,     8,     9,    10,
      16,    12,     3,    89,    19,    91,    20,    93,    12,    95,
      21,    22,    12,    24,   100,    12,    27,   103,   104,    15,
     106,    19,    13,    34,     3,    19,   112,     6,     7,     8,
       9,    10,    13,    12,    16,    14,    18,     5,   124,    21,
      22,    17,    21,    22,    37,    24,   132,    46,    13,   102,
      78,    43,   112,   139,    -1,    34,    -1,    36,    -1,    38,
      39,    40,     3,    42,    43,     6,     7,     8,     9,    10,
       3,    12,    -1,     6,     7,     8,     9,    10,    -1,    12,
      21,    22,    -1,    24,    -1,    -1,    27,    -1,    21,    22,
      -1,    24,    -1,    34,    27,    -1,    -1,    -1,    -1,     3,
      -1,    34,     6,     7,     8,     9,    10,    -1,    12,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    22,    -1,
      24,    -1,     3,    27,    -1,     6,     7,     8,     9,    10,
      34,    12,    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,
      21,    22,     3,    24,    -1,     6,     7,     8,     9,    10,
      -1,    12,    -1,    34,    -1,    -1,    -1,     4,    -1,    -1,
      21,    22,    -1,    24,    -1,    -1,    -1,    -1,    -1,    16,
      17,    18,    -1,    34,    21,    22,    23,    24,    25,    26,
      27,     4,    16,    -1,    18,    32,    33,    21,    22,    23,
      24,    25,    26,    16,    -1,    18,    19,    -1,    21,    22,
      23,    24,    25,    26,    27,     4,    16,    -1,    18,    32,
      33,    21,    22,    -1,    13,    25,    26,    16,     4,    18,
      -1,    -1,    21,    22,    23,    24,    25,    26,    27,     4,
      16,    -1,    18,    32,    33,    21,    22,    23,    24,    25,
      26,    16,    -1,    18,    19,    -1,    21,    22,    23,    24,
      25,    26,    27,     4,    -1,    -1,    -1,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    16,     4,    18,    -1,    20,
      21,    22,    23,    24,    25,    26,    27,    -1,    16,    17,
      18,    32,    33,    21,    22,    23,    24,    25,    26,    27,
       4,    -1,    -1,    -1,    32,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    16,    -1,    18,    19,    -1,    21,    22,    23,
      24,    25,    26,    27,     4,    -1,    -1,    -1,    32,    33,
      -1,    -1,    -1,    13,    -1,    -1,    16,    -1,    18,    -1,
      -1,    21,    22,    23,    24,    25,    26,    27,     4,    -1,
      -1,    -1,    32,    33,    -1,    -1,    -1,    13,    -1,    -1,
      16,    -1,    18,    -1,    -1,    21,    22,    23,    24,    25,
      26,    27,     4,    -1,    -1,    -1,    32,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    16,    -1,    18,    19,    -1,    21,
      22,    23,    24,    25,    26,    27,     4,    -1,    -1,    -1,
      32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    16,    -1,
      18,    19,    -1,    21,    22,    23,    24,    25,    26,    27,
       4,    -1,    -1,    -1,    32,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    16,     4,    18,    19,    -1,    21,    22,    23,
      24,    25,    26,    27,    -1,    16,     4,    18,    32,    33,
      21,    22,    23,    24,    25,    26,    27,    -1,    16,    -1,
      18,    32,    33,    21,    22,    23,    24,    25,    26,    -1,
      -1,    -1,    -1,    -1,    32
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     5,    47,    48,    49,    51,    19,     0,    48,
       3,    50,    52,    53,    12,    19,    16,    20,    27,    14,
      56,    13,    51,    54,    55,     3,     6,     7,     8,     9,
      10,    12,    21,    22,    24,    34,    64,     3,    50,    52,
      64,    51,    60,    61,    52,    13,    20,    12,    64,    64,
      64,    64,    64,     4,    16,    17,    18,    21,    22,    23,
      24,    25,    26,    27,    32,    33,    19,    52,    62,    63,
      36,    38,    39,    40,    42,    43,    56,    57,    58,    64,
      60,    54,    13,    64,    65,    13,    64,    64,     3,    27,
      64,    27,    64,    27,    64,    27,    64,    64,    64,    64,
      27,    19,    20,    12,    12,    64,    12,    19,    19,    15,
      57,    19,    20,    13,    17,    64,    64,    64,    64,    64,
      62,    64,    64,    19,    19,    59,    64,    65,    13,    13,
      64,    13,    19,    58,    58,    19,    58,    64,    37,    19,
      58,    64
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


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
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

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
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 75 "parser.y"
    { semantic_Analysis0((yyvsp[(1) - (1)].ptr));/*语义分析*/ ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 77 "parser.y"
    {(yyval.ptr)=NULL;;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 78 "parser.y"
    {(yyval.ptr)=mknode(EXT_DEF_LIST,(yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr),NULL,yylineno);;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 80 "parser.y"
    {(yyval.ptr)=mknode(EXT_VAR_DEF,(yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr),NULL,yylineno);;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 81 "parser.y"
    {(yyval.ptr)=mknode(EXT_VAR_DEF_ASSIGN,(yyvsp[(1) - (5)].ptr),(yyvsp[(2) - (5)].ptr),(yyvsp[(4) - (5)].ptr),yylineno);;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 82 "parser.y"
    {(yyval.ptr)=mknode(FUNC_DEF,(yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr),(yyvsp[(3) - (3)].ptr),yylineno);;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 83 "parser.y"
    {(yyval.ptr)=NULL; ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 85 "parser.y"
    {(yyval.ptr)=(yyvsp[(1) - (1)].ptr);;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 86 "parser.y"
    {(yyval.ptr)=mknode(EXT_DEC_LIST,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL,yylineno);;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 88 "parser.y"
    {(yyval.ptr)=mknode(TYPE,NULL,NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (1)].type_id));if(!strcmp((yyvsp[(1) - (1)].type_id),"void"))(yyval.ptr)->type=VOID;if(!strcmp((yyvsp[(1) - (1)].type_id),"int"))(yyval.ptr)->type=INT;if(!strcmp((yyvsp[(1) - (1)].type_id),"float"))(yyval.ptr)->type=FLOAT;if(!strcmp((yyvsp[(1) - (1)].type_id),"double"))(yyval.ptr)->type=DOUBLE;if(!strcmp((yyvsp[(1) - (1)].type_id),"char"))(yyval.ptr)->type=CHAR;if(!strcmp((yyvsp[(1) - (1)].type_id),"string"))(yyval.ptr)->type=STRING;;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 90 "parser.y"
    {(yyval.ptr)=mknode(ID,NULL,NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (1)].type_id));;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 91 "parser.y"
    {(yyval.ptr)=mknode(ARRAY_DEC,(yyvsp[(1) - (4)].ptr),(yyvsp[(3) - (4)].ptr),NULL,yylineno);;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 93 "parser.y"
    {(yyval.ptr)=mknode(FUNC_DEC,(yyvsp[(3) - (4)].ptr),NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (4)].type_id));;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 94 "parser.y"
    {(yyval.ptr)=mknode(FUNC_DEC,NULL,NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (3)].type_id));;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 97 "parser.y"
    {(yyval.ptr)=mknode(PARAM_LIST,(yyvsp[(1) - (1)].ptr),NULL,NULL,yylineno);;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 98 "parser.y"
    {(yyval.ptr)=mknode(PARAM_LIST,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL,yylineno);;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 100 "parser.y"
    {(yyval.ptr)=mknode(PARAM_DEC,(yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr),NULL,yylineno);;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 103 "parser.y"
    {(yyval.ptr)=mknode(COMP_STM,(yyvsp[(2) - (4)].ptr),(yyvsp[(3) - (4)].ptr),NULL,yylineno);;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 105 "parser.y"
    {(yyval.ptr)=NULL; ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 106 "parser.y"
    {(yyval.ptr)=mknode(STM_LIST,(yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr),NULL,yylineno);;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 108 "parser.y"
    {(yyval.ptr)=mknode(EXP_STMT,(yyvsp[(1) - (2)].ptr),NULL,NULL,yylineno);;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 109 "parser.y"
    {(yyval.ptr)=(yyvsp[(1) - (1)].ptr);;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 110 "parser.y"
    {(yyval.ptr)=mknode(RETURN,(yyvsp[(2) - (3)].ptr),NULL,NULL,yylineno);;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 111 "parser.y"
    {(yyval.ptr)=mknode(IF_THEN,(yyvsp[(3) - (5)].ptr),(yyvsp[(5) - (5)].ptr),NULL,yylineno);;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 112 "parser.y"
    {(yyval.ptr)=mknode(IF_THEN_ELSE,(yyvsp[(3) - (7)].ptr),(yyvsp[(5) - (7)].ptr),(yyvsp[(7) - (7)].ptr),yylineno);;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 113 "parser.y"
    {(yyval.ptr)=mknode(WHILE,(yyvsp[(3) - (5)].ptr),(yyvsp[(5) - (5)].ptr),NULL,yylineno);;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 114 "parser.y"
    {(yyval.ptr)=mknode(FOR,(yyvsp[(3) - (5)].ptr),(yyvsp[(5) - (5)].ptr),NULL,yylineno);;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 115 "parser.y"
    {(yyval.ptr)=mknode(BREAK,NULL,NULL,NULL,yylineno);;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 116 "parser.y"
    {(yyval.ptr)=mknode(CONTINUE,NULL,NULL,NULL,yylineno);;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 118 "parser.y"
    {(yyval.ptr)=mknode(FOR_DEC,(yyvsp[(1) - (5)].ptr),(yyvsp[(3) - (5)].ptr),(yyvsp[(5) - (5)].ptr),yylineno);;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 119 "parser.y"
    {(yyval.ptr)=mknode(FOR_DEC,(yyvsp[(2) - (3)].ptr),NULL,NULL,yylineno);;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 122 "parser.y"
    {(yyval.ptr)=NULL; ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 123 "parser.y"
    {(yyval.ptr)=mknode(DEF_LIST,(yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr),NULL,yylineno);;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 125 "parser.y"
    {(yyval.ptr)=mknode(VAR_DEF,(yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr),NULL,yylineno);;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 127 "parser.y"
    {(yyval.ptr)=mknode(DEC_LIST,(yyvsp[(1) - (1)].ptr),NULL,NULL,yylineno);;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 128 "parser.y"
    {(yyval.ptr)=mknode(DEC_LIST,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL,yylineno);;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 130 "parser.y"
    {(yyval.ptr)=(yyvsp[(1) - (1)].ptr);;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 131 "parser.y"
    {(yyval.ptr)=mknode(ASSIGNOP,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"=");;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 133 "parser.y"
    {(yyval.ptr)=mknode(ASSIGNOP,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"=");;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 134 "parser.y"
    {(yyval.ptr)=mknode(AND,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"AND");;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 135 "parser.y"
    {(yyval.ptr)=mknode(OR,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"OR");;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 136 "parser.y"
    {(yyval.ptr)=mknode(RELOP,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(2) - (3)].type_id));;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 137 "parser.y"
    {(yyval.ptr)=mknode(PLUS,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"PLUS");;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 138 "parser.y"
    {(yyval.ptr)=mknode(ASSIGNOP_PLUS,(yyvsp[(1) - (4)].ptr),(yyvsp[(4) - (4)].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"+=");;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 139 "parser.y"
    {(yyval.ptr)=mknode(PLUS_SELF,(yyvsp[(1) - (2)].ptr),NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,"++");;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 140 "parser.y"
    {(yyval.ptr)=mknode(PLUS_SELF,(yyvsp[(2) - (2)].ptr),NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,"++");;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 141 "parser.y"
    {(yyval.ptr)=mknode(MINUS,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"MINUS");;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 142 "parser.y"
    {(yyval.ptr)=mknode(ASSIGNOP_MINUS,(yyvsp[(1) - (4)].ptr),(yyvsp[(4) - (4)].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"-=");;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 143 "parser.y"
    {(yyval.ptr)=mknode(MINUS_SELF,(yyvsp[(1) - (2)].ptr),NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,"--");;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 144 "parser.y"
    {(yyval.ptr)=mknode(MINUS_SELF,(yyvsp[(2) - (2)].ptr),NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,"--");;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 145 "parser.y"
    {(yyval.ptr)=mknode(STAR,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"STAR");;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 146 "parser.y"
    {(yyval.ptr)=mknode(ASSIGNOP_STAR,(yyvsp[(1) - (4)].ptr),(yyvsp[(4) - (4)].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"*=");;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 147 "parser.y"
    {(yyval.ptr)=mknode(DIV,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"DIV");;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 148 "parser.y"
    {(yyval.ptr)=mknode(ASSIGNOP_DIV,(yyvsp[(1) - (4)].ptr),(yyvsp[(4) - (4)].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"\\=");;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 149 "parser.y"
    {(yyval.ptr)=(yyvsp[(2) - (3)].ptr);;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 150 "parser.y"
    {(yyval.ptr)=mknode(UMINUS,(yyvsp[(2) - (2)].ptr),NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,"UMINUS");;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 151 "parser.y"
    {(yyval.ptr)=mknode(NOT,(yyvsp[(2) - (2)].ptr),NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,"!");;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 152 "parser.y"
    {(yyval.ptr)=mknode(FUNC_CALL,(yyvsp[(3) - (4)].ptr),NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (4)].type_id));;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 153 "parser.y"
    {(yyval.ptr)=mknode(FUNC_CALL,NULL,NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (3)].type_id));;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 154 "parser.y"
    {(yyval.ptr)=mknode(EXP_ARRAY,(yyvsp[(1) - (4)].ptr),(yyvsp[(3) - (4)].ptr),NULL,yylineno);}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 155 "parser.y"
    {(yyval.ptr)=mknode(EXP_ELE,NULL,NULL,NULL,yylineno);;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 156 "parser.y"
    {(yyval.ptr)=mknode(ID,NULL,NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (1)].type_id));;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 157 "parser.y"
    {(yyval.ptr)=mknode(INT,NULL,NULL,NULL,yylineno);(yyval.ptr)->type_int=(yyvsp[(1) - (1)].type_int);(yyval.ptr)->type=INT;;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 158 "parser.y"
    {(yyval.ptr)=mknode(FLOAT,NULL,NULL,NULL,yylineno);(yyval.ptr)->type_float=(yyvsp[(1) - (1)].type_float);(yyval.ptr)->type=FLOAT;;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 159 "parser.y"
    {(yyval.ptr)=mknode(DOUBLE,NULL,NULL,NULL,yylineno);(yyval.ptr)->type_float=(yyvsp[(1) - (1)].type_double);(yyval.ptr)->type=DOUBLE;;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 160 "parser.y"
    {(yyval.ptr)=mknode(CHAR,NULL,NULL,NULL,yylineno);(yyval.ptr)->type_char=(yyvsp[(1) - (1)].type_char);(yyval.ptr)->type=CHAR;;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 161 "parser.y"
    {(yyval.ptr)=mknode(STRING,NULL,NULL,NULL,yylineno);strcpy((yyval.ptr)->type_string,(yyvsp[(1) - (1)].type_string));(yyval.ptr)->type=STRING;;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 163 "parser.y"
    {(yyval.ptr)=mknode(ARGS,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL,yylineno);;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 164 "parser.y"
    {(yyval.ptr)=mknode(ARGS,(yyvsp[(1) - (1)].ptr),NULL,NULL,yylineno);;}
    break;



/* Line 1455 of yacc.c  */
#line 2123 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 166 "parser.y"


int main(int argc, char *argv[]){
	yyin=fopen(argv[1],"r");
	if (!yyin) return 0;
                yylineno=1;
                yyparse();
                return 0;
	}

#include<stdarg.h>
void yyerror(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, ".\n");
}
