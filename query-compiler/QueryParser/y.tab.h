/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
     SELECT = 258,
     INSERT = 259,
     FROM = 260,
     WHERE = 261,
     SUM = 262,
     PROD = 263,
     COMMA = 264,
     AND = 265,
     STRNG = 266,
     NUMBER = 267,
     PLUS = 268,
     MINUS = 269,
     MUL = 270,
     DIV = 271,
     EQ = 272,
     GT = 273,
     LT = 274,
     GTE = 275,
     LTE = 276,
     NOT_EQ = 277,
     LPAREN = 278,
     RPAREN = 279,
     DBL_QT = 280,
     SNGL_QT = 281,
     SEMICOLON = 282
   };
#endif
/* Tokens.  */
#define SELECT 258
#define INSERT 259
#define FROM 260
#define WHERE 261
#define SUM 262
#define PROD 263
#define COMMA 264
#define AND 265
#define STRNG 266
#define NUMBER 267
#define PLUS 268
#define MINUS 269
#define MUL 270
#define DIV 271
#define EQ 272
#define GT 273
#define LT 274
#define GTE 275
#define LTE 276
#define NOT_EQ 277
#define LPAREN 278
#define RPAREN 279
#define DBL_QT 280
#define SNGL_QT 281
#define SEMICOLON 282




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 181 "par.y"

	char* str;
	int ival;



/* Line 2068 of yacc.c  */
#line 111 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


