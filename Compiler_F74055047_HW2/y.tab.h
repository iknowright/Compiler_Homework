/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PRINT = 258,
    IF = 259,
    ELSE = 260,
    WHILE = 261,
    ID = 262,
    SEMICOLON = 263,
    COMMA = 264,
    QUOTA = 265,
    ADD = 266,
    SUB = 267,
    MUL = 268,
    DIV = 269,
    MOD = 270,
    INC = 271,
    DEC = 272,
    MT = 273,
    LT = 274,
    MTE = 275,
    LTE = 276,
    EQ = 277,
    NE = 278,
    ASGN = 279,
    ADDASGN = 280,
    SUBASGN = 281,
    MULASGN = 282,
    DIVASGN = 283,
    MODASGN = 284,
    AND = 285,
    OR = 286,
    NOT = 287,
    LB = 288,
    RB = 289,
    LCB = 290,
    RCB = 291,
    LSB = 292,
    RSB = 293,
    VOID = 294,
    FLOAT = 295,
    INT = 296,
    STRING = 297,
    BOOL = 298,
    RETURN = 299,
    TRUE = 300,
    FALSE = 301,
    CPP_COMMENT = 302,
    C_COMMENT = 303,
    I_CONST = 304,
    F_CONST = 305,
    STR_CONST = 306
  };
#endif
/* Tokens.  */
#define PRINT 258
#define IF 259
#define ELSE 260
#define WHILE 261
#define ID 262
#define SEMICOLON 263
#define COMMA 264
#define QUOTA 265
#define ADD 266
#define SUB 267
#define MUL 268
#define DIV 269
#define MOD 270
#define INC 271
#define DEC 272
#define MT 273
#define LT 274
#define MTE 275
#define LTE 276
#define EQ 277
#define NE 278
#define ASGN 279
#define ADDASGN 280
#define SUBASGN 281
#define MULASGN 282
#define DIVASGN 283
#define MODASGN 284
#define AND 285
#define OR 286
#define NOT 287
#define LB 288
#define RB 289
#define LCB 290
#define RCB 291
#define LSB 292
#define RSB 293
#define VOID 294
#define FLOAT 295
#define INT 296
#define STRING 297
#define BOOL 298
#define RETURN 299
#define TRUE 300
#define FALSE 301
#define CPP_COMMENT 302
#define C_COMMENT 303
#define I_CONST 304
#define F_CONST 305
#define STR_CONST 306

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 24 "compiler_hw2.y" /* yacc.c:1921  */

    int i_val;
    double f_val;
    char* string;

#line 166 "y.tab.h" /* yacc.c:1921  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
