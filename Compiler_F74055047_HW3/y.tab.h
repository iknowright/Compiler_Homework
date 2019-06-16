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
    SEMICOLON = 262,
    COMMA = 263,
    QUOTA = 264,
    ADD = 265,
    SUB = 266,
    MUL = 267,
    DIV = 268,
    MOD = 269,
    INC = 270,
    DEC = 271,
    MT = 272,
    LT = 273,
    MTE = 274,
    LTE = 275,
    EQ = 276,
    NE = 277,
    AND = 278,
    OR = 279,
    NOT = 280,
    LB = 281,
    RB = 282,
    LCB = 283,
    RCB = 284,
    LSB = 285,
    RSB = 286,
    VOID = 287,
    FLOAT = 288,
    INT = 289,
    STRING = 290,
    BOOL = 291,
    RETURN = 292,
    CPP_COMMENT = 293,
    C_COMMENT = 294,
    I_CONST = 295,
    F_CONST = 296,
    STR_CONST = 297,
    TRUE = 298,
    FALSE = 299,
    ID = 300,
    ASGN = 301,
    MULASGN = 302,
    DIVASGN = 303,
    MODASGN = 304,
    ADDASGN = 305,
    SUBASGN = 306
  };
#endif
/* Tokens.  */
#define PRINT 258
#define IF 259
#define ELSE 260
#define WHILE 261
#define SEMICOLON 262
#define COMMA 263
#define QUOTA 264
#define ADD 265
#define SUB 266
#define MUL 267
#define DIV 268
#define MOD 269
#define INC 270
#define DEC 271
#define MT 272
#define LT 273
#define MTE 274
#define LTE 275
#define EQ 276
#define NE 277
#define AND 278
#define OR 279
#define NOT 280
#define LB 281
#define RB 282
#define LCB 283
#define RCB 284
#define LSB 285
#define RSB 286
#define VOID 287
#define FLOAT 288
#define INT 289
#define STRING 290
#define BOOL 291
#define RETURN 292
#define CPP_COMMENT 293
#define C_COMMENT 294
#define I_CONST 295
#define F_CONST 296
#define STR_CONST 297
#define TRUE 298
#define FALSE 299
#define ID 300
#define ASGN 301
#define MULASGN 302
#define DIVASGN 303
#define MODASGN 304
#define ADDASGN 305
#define SUBASGN 306

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 60 "compiler_hw3.y" /* yacc.c:1921  */

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
