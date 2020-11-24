
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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
     PRE_PLUS_SELF = 276,
     NEXT_PLUS_SELF = 277,
     PRE_MINUS_SELF = 278,
     NEXT_MINUS_SELF = 279,
     PLUS = 280,
     MINUS = 281,
     STAR = 282,
     DIV = 283,
     ASSIGNOP = 284,
     ASSIGNOP_PLUS = 285,
     ASSIGNOP_MINUS = 286,
     ASSIGNOP_STAR = 287,
     ASSIGNOP_DIV = 288,
     AND = 289,
     OR = 290,
     NOT = 291,
     VARDEC = 292,
     IF = 293,
     ELSE = 294,
     WHILE = 295,
     RETURN = 296,
     FOR = 297,
     STRUCT = 298,
     BREAK = 299,
     CONTINUE = 300,
     ARRAY_ASSIGNOP = 301,
     ASSIGNOP_ARRAY = 302,
     MINUS_SELF = 303,
     PLUS_SELF = 304,
     UMINUS = 305,
     LOWER_THEN_ELSE = 306
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
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



/* Line 1676 of yacc.c  */
#line 118 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

extern YYLTYPE yylloc;

