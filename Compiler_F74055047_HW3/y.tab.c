/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "compiler_hw3.y" /* yacc.c:337  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gencode.h"

FILE *file; // To generate .j file for Jasmin

typedef enum {
    PARAMETER, FUNCTION, VARIABLE
} kindEnum;

typedef struct Node {
    int index;
    char * name;
    kindEnum kind;
    int type;
    int scope;
    char * attribute;
    int func_flag;
    struct Node * next;
    int reg_num;
} Node;

int scope;

Node * table[100] = { NULL };

int scope_index[100];

typedef struct ID_INFO {
    int scope;
    int type;
    int reg_num;
} ID_INFO;

extern int yylineno;
extern int yylex();
extern char* yytext;   // Get current token from lex
extern char buf[256];  // Get current code line from lex

/* Symbol table function - you can add new function if needed. */
void insert_symbol(Node** head_ref, int index, char * name, kindEnum kind, int type, int scope, char * attribute, int func_flag, int reg_num);
void enum_to_string(char * stringkind, char * stringtype, int kind, int type);
void dump_symbol(int scope);
int lookup_symbol(int scope, char * name, kindEnum kind);
void custom_yyerror(char *s);
int lookup_reg(int stop_scope);
ID_INFO * get_id_info(int curr_scope, char * id);
void clearStatementStack();
void printStatementStack();

int stack_num = 0;

extern int dump_flag;
extern void yyerror(char * s);
extern int semantic_flag;
int syntactic_flag;
char error_str[100];
int forward_flag;

char global_value[100];

char statement_stack[100][100];

#line 136 "y.tab.c" /* yacc.c:337  */
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
#line 71 "compiler_hw3.y" /* yacc.c:352  */

    int i_val;
    double f_val;
    char* string;

#line 287 "y.tab.c" /* yacc.c:352  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



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
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   154

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  95
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  150

#define YYUNDEFTOK  2
#define YYMAXUTOK   306

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
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
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   121,   121,   122,   126,   127,   128,   132,   151,   152,
     155,   156,   157,   158,   159,   160,   164,   174,   175,   176,
     180,   181,   182,   186,   198,   201,   202,   203,   219,   235,
     251,   271,   275,   276,   277,   281,   285,   289,   293,   294,
     298,   299,   306,   310,   338,   339,   340,   341,   342,   346,
     347,   351,   352,   356,   357,   361,   362,   366,   367,   368,
     372,   373,   374,   375,   379,   380,   381,   382,   383,   384,
     388,   389,   390,   391,   392,   393,   397,   398,   399,   400,
     404,   405,   406,   411,   412,   413,   417,   425,   426,   427,
     428,   433,   437,   438,   439,   440
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PRINT", "IF", "ELSE", "WHILE",
  "SEMICOLON", "COMMA", "QUOTA", "ADD", "SUB", "MUL", "DIV", "MOD", "INC",
  "DEC", "MT", "LT", "MTE", "LTE", "EQ", "NE", "AND", "OR", "NOT", "LB",
  "RB", "LCB", "RCB", "LSB", "RSB", "VOID", "FLOAT", "INT", "STRING",
  "BOOL", "RETURN", "CPP_COMMENT", "C_COMMENT", "I_CONST", "F_CONST",
  "STR_CONST", "TRUE", "FALSE", "ID", "ASGN", "MULASGN", "DIVASGN",
  "MODASGN", "ADDASGN", "SUBASGN", "$accept", "program", "program_body",
  "function", "stats", "stat", "function_call", "argument_list",
  "expression_statement", "assign_statement", "return_statement",
  "printf_statement", "function_declaration", "variable_declaration",
  "while_statement", "if_statement", "block_body", "left_brace",
  "right_brace", "expression", "parameter_list", "parameter", "type",
  "assignment_expression", "logical_or_expression",
  "logical_and_expression", "relational_expression", "additive_expression",
  "multiplicative_expression", "relational_operator",
  "assignment_operator", "unary_expression", "unary_operator",
  "postfix_expression", "primary_expression", "string", "constant", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306
};
# endif

#define YYPACT_NINF -128

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-128)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -128,    33,  -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,
    -128,  -128,   -33,    -4,  -128,    22,    19,     5,  -128,   -27,
     -37,  -128,  -128,    19,    19,  -128,    19,  -128,  -128,  -128,
    -128,    11,  -128,    31,  -128,    37,    23,   111,    10,     2,
      88,    19,    61,  -128,  -128,  -128,    22,    -1,  -128,    74,
    -128,  -128,    60,    19,  -128,    19,    19,  -128,  -128,  -128,
    -128,  -128,  -128,    19,    19,    19,    19,    19,    19,  -128,
    -128,  -128,  -128,  -128,  -128,    19,  -128,  -128,  -128,  -128,
    -128,  -128,  -128,  -128,  -128,  -128,     9,  -128,    23,  -128,
     111,    10,     2,     2,  -128,  -128,  -128,  -128,    75,    19,
    -128,    62,    63,    66,  -128,  -128,    19,    76,  -128,  -128,
    -128,  -128,  -128,  -128,  -128,  -128,  -128,    86,    49,  -128,
      30,    19,    19,    90,    19,  -128,    -3,    64,    78,    87,
      94,   113,  -128,    96,   104,   110,   134,   114,   114,  -128,
     116,  -128,  -128,   139,  -128,   138,     3,  -128,  -128,  -128
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     1,    44,    46,    45,    48,    47,     2,     6,
       4,     5,     0,     0,    29,    42,    39,     0,    40,     0,
       0,    81,    80,     0,     0,    82,    39,    92,    93,    94,
      95,    86,    90,     0,    38,    50,    51,    53,    55,    57,
      60,     0,    76,    83,    88,    87,     0,     0,    43,     0,
      77,    78,     0,    19,    30,     0,     0,    64,    65,    66,
      67,    68,    69,     0,     0,     0,     0,     0,     0,    70,
      71,    72,    73,    74,    75,     0,    79,    84,    85,    41,
      28,    36,     7,     9,    91,    89,     0,    17,    52,    60,
      54,    56,    58,    59,    61,    62,    63,    49,     0,     0,
      16,     0,     0,     0,    22,    37,    39,    86,     8,    14,
      20,    15,    13,    12,    10,    11,    35,     0,     0,    18,
       0,    39,    39,     0,    39,    21,     0,     0,     0,     0,
       0,     0,    24,     0,     0,     0,     0,     0,     0,    23,
       0,    27,    26,    34,    31,     0,     0,    25,    33,    32
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,
    -128,  -128,  -128,    48,  -128,     4,  -127,  -128,  -128,   -26,
    -128,   101,     1,   -52,  -128,    93,    95,    89,   -40,  -128,
      42,   -15,  -128,  -128,  -128,  -128,    34
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     8,     9,    98,   108,    32,    86,   109,   110,
     111,   112,    10,    11,   114,   115,    82,    83,   116,    33,
      17,    18,    19,    34,    35,    36,    37,    38,    39,    63,
      75,    40,    41,    42,    43,    44,    45
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      52,    87,    12,    14,    14,    49,    80,   102,    50,    51,
     143,   144,    13,    46,    66,    67,    68,    99,    48,   149,
      64,    65,    15,    97,    92,    93,    76,    81,    20,    21,
      22,    81,    47,     2,    23,    24,   100,    53,    54,   127,
      89,    89,    16,    16,    25,    26,    56,   119,    89,    89,
      89,    94,    95,    96,     3,     4,     5,     6,     7,    27,
      28,    55,    29,    30,    31,     3,     4,     5,     6,     7,
      27,    28,   117,    29,    30,   128,    77,    78,   101,   102,
     123,   103,   104,    84,    20,    21,    22,    85,   120,   121,
      23,    24,   122,   125,   126,   130,   131,   132,   133,   118,
      25,    26,    53,   139,   105,   135,   134,     3,     4,     5,
       6,     7,   106,   140,   136,    27,    28,   141,    29,    30,
     107,   137,    69,    70,    71,    72,    73,    74,    57,    58,
      59,    60,    61,    62,    69,    70,    71,    72,    73,    74,
     138,   142,    81,   145,   146,   147,   113,    79,    88,   124,
     148,    90,    91,     0,   129
};

static const yytype_int16 yycheck[] =
{
      26,    53,     1,     7,     7,    42,     7,     4,    23,    24,
     137,   138,    45,     8,    12,    13,    14,     8,    45,   146,
      10,    11,    26,    75,    64,    65,    41,    28,     9,    10,
      11,    28,    27,     0,    15,    16,    27,    26,     7,     9,
      55,    56,    46,    46,    25,    26,    23,    99,    63,    64,
      65,    66,    67,    68,    32,    33,    34,    35,    36,    40,
      41,    24,    43,    44,    45,    32,    33,    34,    35,    36,
      40,    41,    98,    43,    44,    45,    15,    16,     3,     4,
     106,     6,     7,     9,     9,    10,    11,    27,    26,    26,
      15,    16,    26,     7,    45,   121,   122,     7,   124,    98,
      25,    26,    26,     7,    29,    27,    42,    32,    33,    34,
      35,    36,    37,     9,    27,    40,    41,     7,    43,    44,
      45,    27,    46,    47,    48,    49,    50,    51,    17,    18,
      19,    20,    21,    22,    46,    47,    48,    49,    50,    51,
      27,     7,    28,    27,     5,     7,    98,    46,    55,   107,
     146,    56,    63,    -1,   120
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    53,     0,    32,    33,    34,    35,    36,    54,    55,
      64,    65,    74,    45,     7,    26,    46,    72,    73,    74,
       9,    10,    11,    15,    16,    25,    26,    40,    41,    43,
      44,    45,    58,    71,    75,    76,    77,    78,    79,    80,
      83,    84,    85,    86,    87,    88,     8,    27,    45,    42,
      83,    83,    71,    26,     7,    24,    23,    17,    18,    19,
      20,    21,    22,    81,    10,    11,    12,    13,    14,    46,
      47,    48,    49,    50,    51,    82,    83,    15,    16,    73,
       7,    28,    68,    69,     9,    27,    59,    75,    77,    83,
      78,    79,    80,    80,    83,    83,    83,    75,    56,     8,
      27,     3,     4,     6,     7,    29,    37,    45,    57,    60,
      61,    62,    63,    65,    66,    67,    70,    71,    74,    75,
      26,    26,    26,    71,    82,     7,    45,     9,    45,    88,
      71,    71,     7,    71,    42,    27,    27,    27,    27,     7,
       9,     7,     7,    68,    68,    27,     5,     7,    67,    68
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    53,    54,    54,    54,    55,    56,    56,
      57,    57,    57,    57,    57,    57,    58,    59,    59,    59,
      60,    60,    60,    61,    62,    63,    63,    63,    64,    65,
      65,    66,    67,    67,    67,    68,    69,    70,    71,    71,
      72,    72,    72,    73,    74,    74,    74,    74,    74,    75,
      75,    76,    76,    77,    77,    78,    78,    79,    79,    79,
      80,    80,    80,    80,    81,    81,    81,    81,    81,    81,
      82,    82,    82,    82,    82,    82,    83,    83,    83,    83,
      84,    84,    84,    85,    85,    85,    86,    86,    86,    86,
      86,    87,    88,    88,    88,    88
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     1,     1,     1,     6,     2,     0,
       1,     1,     1,     1,     1,     1,     4,     1,     3,     0,
       1,     2,     1,     4,     3,     7,     5,     5,     6,     3,
       5,     5,     7,     7,     5,     3,     1,     1,     1,     0,
       1,     3,     0,     2,     1,     1,     1,     1,     1,     3,
       1,     1,     3,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       1,     1,     1,     1,     2,     2,     1,     1,     1,     3,
       1,     3,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
            else
              goto append;

          append:
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

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
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
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:
#line 126 "compiler_hw3.y" /* yacc.c:1652  */
    { printStatementStack(); clearStatementStack(); }
#line 1497 "y.tab.c" /* yacc.c:1652  */
    break;

  case 5:
#line 127 "compiler_hw3.y" /* yacc.c:1652  */
    { printStatementStack(); clearStatementStack(); }
#line 1503 "y.tab.c" /* yacc.c:1652  */
    break;

  case 7:
#line 132 "compiler_hw3.y" /* yacc.c:1652  */
    {
        if(!forward_flag) {
            if(!lookup_symbol(scope, (yyvsp[-4].string), FUNCTION)) {
                int max_reg = lookup_reg(scope);
                insert_symbol(&table[scope], scope_index[scope], (yyvsp[-4].string), FUNCTION, (yyvsp[-5].i_val), scope, (yyvsp[-2].string), 0, max_reg + 1);
                strcpy((yyvsp[-2].string), "");
                scope_index[scope]++;
            } else if(lookup_symbol(scope, (yyvsp[-4].string), FUNCTION) == 1){
                semantic_flag = 1;
                strcpy(error_str, "Redeclared function ");
                strcat(error_str, (yyvsp[-4].string));
            }
        }
        strcpy((yyvsp[-2].string), "");
        forward_flag = 0;
    }
#line 1524 "y.tab.c" /* yacc.c:1652  */
    break;

  case 12:
#line 157 "compiler_hw3.y" /* yacc.c:1652  */
    { printStatementStack(); clearStatementStack(); }
#line 1530 "y.tab.c" /* yacc.c:1652  */
    break;

  case 14:
#line 159 "compiler_hw3.y" /* yacc.c:1652  */
    { printStatementStack(); clearStatementStack(); }
#line 1536 "y.tab.c" /* yacc.c:1652  */
    break;

  case 16:
#line 164 "compiler_hw3.y" /* yacc.c:1652  */
    {     
            if(!lookup_symbol(scope, (yyvsp[-3].string), FUNCTION)) {
                semantic_flag = 1;
                strcpy(error_str, "Undeclared function ");
                strcat(error_str, (yyvsp[-3].string));
            }
        }
#line 1548 "y.tab.c" /* yacc.c:1652  */
    break;

  case 23:
#line 186 "compiler_hw3.y" /* yacc.c:1652  */
    {
            strcpy(statement_stack[stack_num++],(yyvsp[-2].string));
            strcpy(statement_stack[stack_num++],(yyvsp[-3].string));
            if(!lookup_symbol(scope, (yyvsp[-3].string), VARIABLE)) {
                semantic_flag = 1;
                strcpy(error_str, "Undeclared variable ");
                strcat(error_str, (yyvsp[-3].string));
            }
        }
#line 1562 "y.tab.c" /* yacc.c:1652  */
    break;

  case 25:
#line 201 "compiler_hw3.y" /* yacc.c:1652  */
    { genPrintStrConst((yyvsp[-3].string)); }
#line 1568 "y.tab.c" /* yacc.c:1652  */
    break;

  case 26:
#line 202 "compiler_hw3.y" /* yacc.c:1652  */
    { genPrintConst((yyvsp[-2].string)); }
#line 1574 "y.tab.c" /* yacc.c:1652  */
    break;

  case 27:
#line 203 "compiler_hw3.y" /* yacc.c:1652  */
    {
            if(!lookup_symbol(scope, (yyvsp[-2].string), VARIABLE)) {
                semantic_flag = 1;
                strcpy(error_str, "Undeclared variable ");
                strcat(error_str, (yyvsp[-2].string));
            } else {              
                ID_INFO * id_info = get_id_info(scope, (yyvsp[-2].string));
                if(id_info != NULL) {                
                    genPrintID(id_info->reg_num, id_info->type, id_info->scope, (yyvsp[-2].string));   
                    genPrint("print here");
                }
            }
        }
#line 1592 "y.tab.c" /* yacc.c:1652  */
    break;

  case 28:
#line 219 "compiler_hw3.y" /* yacc.c:1652  */
    {
        if(!lookup_symbol(scope, (yyvsp[-4].string), FUNCTION)) {
            int max_reg = lookup_reg(scope);
            insert_symbol(&table[scope], scope_index[scope], (yyvsp[-4].string), FUNCTION, (yyvsp[-5].i_val), scope, (yyvsp[-2].string), 1, max_reg + 1);
            strcpy((yyvsp[-2].string), "");
            scope_index[scope]++;
        } else {
            semantic_flag = 1;
            strcpy(error_str, "Redeclared function ");
            strcat(error_str, (yyvsp[-4].string));
        }
        forward_flag = 1;
    }
#line 1610 "y.tab.c" /* yacc.c:1652  */
    break;

  case 29:
#line 235 "compiler_hw3.y" /* yacc.c:1652  */
    {
            if(!lookup_symbol(scope, (yyvsp[-1].string), VARIABLE)) {
                printf("IM IN VARIABLE DECLRATION WITHOUT VALUE\n");
                int max_reg = lookup_reg(scope);
                insert_symbol(&table[scope], scope_index[scope], (yyvsp[-1].string), VARIABLE, (yyvsp[-2].i_val), scope, "", 0, max_reg + 1);
                if(scope == 0) {
                    printf("id = %s, type = %d\n", (yyvsp[-1].string), (yyvsp[-2].i_val));
                    genVarDeclr((yyvsp[-1].string), (yyvsp[-2].i_val));
                }
                scope_index[scope]++;
            } else {
                semantic_flag = 1;
                strcpy(error_str, "Redeclared variable ");
                strcat(error_str, (yyvsp[-1].string));
            }
        }
#line 1631 "y.tab.c" /* yacc.c:1652  */
    break;

  case 30:
#line 251 "compiler_hw3.y" /* yacc.c:1652  */
    {
            if(!lookup_symbol(scope, (yyvsp[-3].string), VARIABLE)) {
                printf("IM IN VARIABLE DECLRATION WITH VALUE\n");
                int max_reg = lookup_reg(scope);
                insert_symbol(&table[scope], scope_index[scope], (yyvsp[-3].string), VARIABLE, (yyvsp[-4].i_val), scope, "", 0, max_reg + 1);
                if(scope == 0) {
                    genVarDeclrVal((yyvsp[-3].string), (yyvsp[-4].i_val), global_value);
                } else {
                    strcpy(statement_stack[stack_num++],"ASGN");
                    strcpy(statement_stack[stack_num++],(yyvsp[-3].string));
                }
                scope_index[scope]++;
            } else {
                semantic_flag = 1;
                strcpy(error_str, "Redeclared variable ");
                strcat(error_str, (yyvsp[-3].string));
            }
        }
#line 1654 "y.tab.c" /* yacc.c:1652  */
    break;

  case 36:
#line 285 "compiler_hw3.y" /* yacc.c:1652  */
    { scope++; }
#line 1660 "y.tab.c" /* yacc.c:1652  */
    break;

  case 37:
#line 289 "compiler_hw3.y" /* yacc.c:1652  */
    { dump_flag = 1; scope--; }
#line 1666 "y.tab.c" /* yacc.c:1652  */
    break;

  case 40:
#line 298 "compiler_hw3.y" /* yacc.c:1652  */
    { (yyval.string) = strdup((yyvsp[0].string)); }
#line 1672 "y.tab.c" /* yacc.c:1652  */
    break;

  case 41:
#line 299 "compiler_hw3.y" /* yacc.c:1652  */
    {
            char * tmp;
            tmp = strdup(", ");
            strcat(tmp, (yyvsp[0].string));
            strcat((yyvsp[-2].string), tmp);
            (yyval.string) = (yyvsp[-2].string);
        }
#line 1684 "y.tab.c" /* yacc.c:1652  */
    break;

  case 42:
#line 306 "compiler_hw3.y" /* yacc.c:1652  */
    { (yyval.string) = strdup(""); }
#line 1690 "y.tab.c" /* yacc.c:1652  */
    break;

  case 43:
#line 310 "compiler_hw3.y" /* yacc.c:1652  */
    {
        if(!forward_flag){
            int max_reg = lookup_reg(scope + 1);
            insert_symbol(&table[scope+1], scope_index[scope+1], (yyvsp[0].string), PARAMETER, (yyvsp[-1].i_val), scope+1, "", 0, max_reg + 1);
        }
        switch((yyvsp[-1].i_val)) {
            case VOID:
                (yyval.string) = strdup("void");
                break;
            case FLOAT:
                (yyval.string) = strdup("float");
                break;
            case INT:
                (yyval.string) = strdup("int");
                break;
            case STRING:
                (yyval.string) = strdup("string");
                break;
            case BOOL:
                (yyval.string) = strdup("bool");
                break;
            default: break;
        }
        scope_index[scope+1]++;
    }
#line 1720 "y.tab.c" /* yacc.c:1652  */
    break;

  case 44:
#line 338 "compiler_hw3.y" /* yacc.c:1652  */
    { (yyval.i_val) = VOID; }
#line 1726 "y.tab.c" /* yacc.c:1652  */
    break;

  case 45:
#line 339 "compiler_hw3.y" /* yacc.c:1652  */
    { (yyval.i_val) = INT; }
#line 1732 "y.tab.c" /* yacc.c:1652  */
    break;

  case 46:
#line 340 "compiler_hw3.y" /* yacc.c:1652  */
    { (yyval.i_val) = FLOAT; }
#line 1738 "y.tab.c" /* yacc.c:1652  */
    break;

  case 47:
#line 341 "compiler_hw3.y" /* yacc.c:1652  */
    { (yyval.i_val) = BOOL; }
#line 1744 "y.tab.c" /* yacc.c:1652  */
    break;

  case 48:
#line 342 "compiler_hw3.y" /* yacc.c:1652  */
    { (yyval.i_val) = STRING; }
#line 1750 "y.tab.c" /* yacc.c:1652  */
    break;

  case 49:
#line 346 "compiler_hw3.y" /* yacc.c:1652  */
    { strcpy(statement_stack[stack_num++],(yyvsp[-1].string)); }
#line 1756 "y.tab.c" /* yacc.c:1652  */
    break;

  case 58:
#line 367 "compiler_hw3.y" /* yacc.c:1652  */
    { strcpy(statement_stack[stack_num++],"ADD"); }
#line 1762 "y.tab.c" /* yacc.c:1652  */
    break;

  case 59:
#line 368 "compiler_hw3.y" /* yacc.c:1652  */
    { strcpy(statement_stack[stack_num++],"SUB"); }
#line 1768 "y.tab.c" /* yacc.c:1652  */
    break;

  case 61:
#line 373 "compiler_hw3.y" /* yacc.c:1652  */
    { strcpy(statement_stack[stack_num++],"MUL"); }
#line 1774 "y.tab.c" /* yacc.c:1652  */
    break;

  case 62:
#line 374 "compiler_hw3.y" /* yacc.c:1652  */
    { strcpy(statement_stack[stack_num++],"DIV"); }
#line 1780 "y.tab.c" /* yacc.c:1652  */
    break;

  case 63:
#line 375 "compiler_hw3.y" /* yacc.c:1652  */
    { strcpy(statement_stack[stack_num++],"MOD"); }
#line 1786 "y.tab.c" /* yacc.c:1652  */
    break;

  case 70:
#line 388 "compiler_hw3.y" /* yacc.c:1652  */
    { (yyval.string) = strdup((yyvsp[0].string)); }
#line 1792 "y.tab.c" /* yacc.c:1652  */
    break;

  case 71:
#line 389 "compiler_hw3.y" /* yacc.c:1652  */
    { (yyval.string) = strdup((yyvsp[0].string)); }
#line 1798 "y.tab.c" /* yacc.c:1652  */
    break;

  case 72:
#line 390 "compiler_hw3.y" /* yacc.c:1652  */
    { (yyval.string) = strdup((yyvsp[0].string)); }
#line 1804 "y.tab.c" /* yacc.c:1652  */
    break;

  case 73:
#line 391 "compiler_hw3.y" /* yacc.c:1652  */
    { (yyval.string) = strdup((yyvsp[0].string)); }
#line 1810 "y.tab.c" /* yacc.c:1652  */
    break;

  case 74:
#line 392 "compiler_hw3.y" /* yacc.c:1652  */
    { (yyval.string) = strdup((yyvsp[0].string)); }
#line 1816 "y.tab.c" /* yacc.c:1652  */
    break;

  case 75:
#line 393 "compiler_hw3.y" /* yacc.c:1652  */
    { (yyval.string) = strdup((yyvsp[0].string)); }
#line 1822 "y.tab.c" /* yacc.c:1652  */
    break;

  case 77:
#line 398 "compiler_hw3.y" /* yacc.c:1652  */
    { strcpy(statement_stack[stack_num++],"INC"); }
#line 1828 "y.tab.c" /* yacc.c:1652  */
    break;

  case 78:
#line 399 "compiler_hw3.y" /* yacc.c:1652  */
    { strcpy(statement_stack[stack_num++],"DEC"); }
#line 1834 "y.tab.c" /* yacc.c:1652  */
    break;

  case 80:
#line 404 "compiler_hw3.y" /* yacc.c:1652  */
    { strcpy(statement_stack[stack_num++],"SUB"); }
#line 1840 "y.tab.c" /* yacc.c:1652  */
    break;

  case 81:
#line 405 "compiler_hw3.y" /* yacc.c:1652  */
    { strcpy(statement_stack[stack_num++],"ADD"); }
#line 1846 "y.tab.c" /* yacc.c:1652  */
    break;

  case 82:
#line 406 "compiler_hw3.y" /* yacc.c:1652  */
    { strcpy(statement_stack[stack_num++],"NOT"); }
#line 1852 "y.tab.c" /* yacc.c:1652  */
    break;

  case 84:
#line 412 "compiler_hw3.y" /* yacc.c:1652  */
    { strcpy(statement_stack[stack_num++],"INC"); }
#line 1858 "y.tab.c" /* yacc.c:1652  */
    break;

  case 85:
#line 413 "compiler_hw3.y" /* yacc.c:1652  */
    { strcpy(statement_stack[stack_num++],"DEC"); }
#line 1864 "y.tab.c" /* yacc.c:1652  */
    break;

  case 86:
#line 417 "compiler_hw3.y" /* yacc.c:1652  */
    {  
            strcpy(statement_stack[stack_num++],(yyvsp[0].string));
            if(!lookup_symbol(scope, (yyvsp[0].string), VARIABLE)) {
                semantic_flag = 1;
                strcpy(error_str, "Undeclared variable ");
                strcat(error_str, (yyvsp[0].string));
            }
        }
#line 1877 "y.tab.c" /* yacc.c:1652  */
    break;

  case 92:
#line 437 "compiler_hw3.y" /* yacc.c:1652  */
    { strcpy(global_value, (yyvsp[0].string)); (yyval.string) = strdup((yyvsp[0].string)); strcpy(statement_stack[stack_num++],(yyvsp[0].string)); }
#line 1883 "y.tab.c" /* yacc.c:1652  */
    break;

  case 93:
#line 438 "compiler_hw3.y" /* yacc.c:1652  */
    { strcpy(global_value, (yyvsp[0].string)); (yyval.string) = strdup((yyvsp[0].string)); strcpy(statement_stack[stack_num++],(yyvsp[0].string)); }
#line 1889 "y.tab.c" /* yacc.c:1652  */
    break;

  case 94:
#line 439 "compiler_hw3.y" /* yacc.c:1652  */
    { strcpy(global_value, (yyvsp[0].string)); (yyval.string) = strdup((yyvsp[0].string)); strcpy(statement_stack[stack_num++],(yyvsp[0].string)); }
#line 1895 "y.tab.c" /* yacc.c:1652  */
    break;

  case 95:
#line 440 "compiler_hw3.y" /* yacc.c:1652  */
    { strcpy(global_value, (yyvsp[0].string)); (yyval.string) = strdup((yyvsp[0].string)); strcpy(statement_stack[stack_num++],(yyvsp[0].string)); }
#line 1901 "y.tab.c" /* yacc.c:1652  */
    break;


#line 1905 "y.tab.c" /* yacc.c:1652  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



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
                      yytoken, &yylval);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
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
  return yyresult;
}
#line 443 "compiler_hw3.y" /* yacc.c:1918  */


/* C code section */
int main(int argc, char** argv)
{
    yylineno = 0;

    file = fopen("compiler_hw3.j","w");

    fprintf(file,   ".class public compiler_hw3\n"
                    ".super java/lang/Object\n"
                    // ".method public static main([Ljava/lang/String;)V\n"
                    );

    fclose(file);

    yyparse();
    if(!syntactic_flag) {
        dump_symbol(0);
        printf("\nTotal lines: %d \n",yylineno);
    }

    return 0;
}

void yyerror(char *s)
{
    syntactic_flag = 1;
    if(semantic_flag) {
        custom_yyerror(error_str);
    }
    printf("\n|-----------------------------------------------|\n");
    printf("| Error found in line %d: %s\n", yylineno + 1, buf);
    printf("| %s", s);
    printf("\n|-----------------------------------------------|\n\n");
}

void custom_yyerror(char *s)
{
    if(syntactic_flag) {
        printf("%d: %s\n", yylineno + 1, buf);
        printf("\n|-----------------------------------------------|\n");
        printf("| Error found in line %d: %s\n", yylineno + 1, buf);
    } else {
        // it is because the normal semantic error is done in the lex
        printf("%d: %s", yylineno, buf);
        printf("\n|-----------------------------------------------|\n");
        printf("| Error found in line %d: %s", yylineno, buf);
    }
    printf("| %s", s);
    printf("\n|-----------------------------------------------|\n\n");
}

void insert_symbol(Node** head_ref, int index, char * name, kindEnum kind, int type, int scope, char * attribute, int func_flag, int reg_num)
{
    Node *last = *head_ref;
    Node * new_node = (Node *)malloc(sizeof(Node));
    new_node->index = index;
    new_node->name = name;
    new_node->kind = kind;
    new_node->type = type;
    new_node->scope = scope;
    new_node->func_flag = func_flag;
    new_node->attribute = strdup(attribute);
    new_node->reg_num = reg_num;
    new_node->next = NULL; 
  
    if (*head_ref == NULL) 
    {  
        *head_ref = new_node; 
        return; 
    }   
       
    while (last->next != NULL) 
        last = last->next; 
   
    last->next = new_node; 
    return;   
}

int lookup_reg(int scope)
{
    int max_reg = -1;
    int i;
    for(i = 1; i <= scope; i++) {
        if(table[i] != NULL) {
            Node* tmp = table[i];
            while(tmp->next != NULL) {
                if(tmp->reg_num > max_reg) {
                    max_reg = tmp->reg_num;
                }
                tmp = tmp->next;
            }
            if(tmp->reg_num > max_reg) {
                max_reg = tmp->reg_num;
            }
        }
    }
    return max_reg;
}

int lookup_symbol(int scope, char * name, kindEnum kind)
{   
    int i = 0;
    int flag = 0;
    while(!flag && i <= scope) {
        if(flag == 1) return flag;
        if(table[i] == NULL) {
            i++;
            continue;
        } 
        else {
            Node* tmp = table[i];
            while(tmp->next != NULL) {
                if(!strcmp(tmp->name, name) && (tmp->kind == kind || tmp->kind==PARAMETER)) {
                    if(tmp->func_flag == 1) {
                        flag = 2;
                    } else {
                        flag = 1;
                    }
                    break;
                }
                tmp = tmp->next;
            }
            if(!strcmp(tmp->name, name) && (tmp->kind == kind || tmp->kind==PARAMETER)) {
                if(tmp->func_flag == 1) {
                    flag = 2;
                } else {
                    flag = 1;
                }
                flag = 1;
                break;
            }
        }
        i++;
    }
    return flag;
}

void dump_symbol(int scope) {
    char stringkind[100];
    char stringtype[100];
    if(table[scope] == NULL) {
        return;
    }
    printf("\n%-10s%-10s%-12s%-10s%-10s%-10s%-10s\n\n",
           "Index", "Name", "Kind", "Type", "Scope", "Attribute", "Register");
    Node * tmp = table[scope];
    while(tmp->next != NULL) {
        enum_to_string(stringkind, stringtype, tmp->kind, tmp->type);
        printf("%-10d%-10s%-12s%-10s%-10d%-10s%-10d\n",
           tmp->index, tmp->name, stringkind, stringtype, tmp->scope, tmp->attribute, tmp->reg_num);
        free(tmp);
        tmp = tmp->next;
    }
    enum_to_string(stringkind, stringtype, tmp->kind, tmp->type);
    printf("%-10d%-10s%-12s%-10s%-10d%-10s%-10d\n\n",
        tmp->index, tmp->name, stringkind, stringtype, tmp->scope, tmp->attribute, tmp->reg_num);
    free(tmp);
    table[scope] = NULL;
    scope_index[scope] = 0;
}

void enum_to_string(char * stringkind, char * stringtype, int kind, int type)
{
    switch(kind) {
        case PARAMETER:
            strcpy(stringkind, "parameter");
            break;
        case FUNCTION:
            strcpy(stringkind, "function");
            break;
        case VARIABLE:          
            strcpy(stringkind, "variable");
            break;
        default: break;
    }
    switch(type) {
        case VOID:
            strcpy(stringtype, "void");
            break;
        case FLOAT:
            strcpy(stringtype, "float");
            break;
        case INT:
            strcpy(stringtype, "int");
            break;
        case STRING:
            strcpy(stringtype, "string");
            break;
        case BOOL:
            strcpy(stringtype, "bool");
            break;
        default: break;
    }
}

ID_INFO * get_id_info(int curr_scope, char * id)
{
    int i;
    file = fopen("compiler_hw3.j","a");    
    ID_INFO * the_node = NULL;
    for(i = curr_scope; i >= 0; i--) {
        if(table[i] != NULL) {
            Node * tmp = table[i];
            while(tmp->next != NULL) {
                if(!strcmp(tmp->name, id)) {
                    the_node = (ID_INFO *)malloc(sizeof(ID_INFO));
                    the_node->type = tmp->type;
                    the_node->reg_num = tmp->reg_num;
                    the_node->scope = tmp->scope;
                }
                tmp = tmp->next;
            }
            if(!strcmp(tmp->name, id)) {
                the_node = (ID_INFO *)malloc(sizeof(ID_INFO));
                the_node->type = tmp->type;
                the_node->reg_num = tmp->reg_num;
                the_node->scope = tmp->scope;
            }
        }
    }
    return the_node;
}

void clearStatementStack()
{
    int i;
    for(i = 0; i < stack_num; i++) {
        strcpy(statement_stack[i], "");
    }
    stack_num = 0;
}

void printStatementStack()
{
    char buf[100];
    if(scope && stack_num > 0 && !semantic_flag) {     
        printf("--------------------------------\n");
        printf("Scope %d\n\n", scope);
        int float_flag = 0;
        ID_INFO * id_info;
        for(int i = 0; i < stack_num; i++) {
            printf("%s ", statement_stack[i]);
        }
        printf("\n\nStack Size %d\n", stack_num);
        printf("Semantic flag %d\n", semantic_flag);
        for(int i = 0; i < stack_num - 2; i++) {
            if((id_info = get_id_info(scope, statement_stack[i])) != NULL) {
                if(id_info->type == FLOAT) {
                    float_flag = 1;
                    break;
                }          
            } else {           
                for(int j  = 0; j < strlen(statement_stack[i]); j++) {
                    if(statement_stack[i][j] == '.') {
                        float_flag = 1;
                        break;
                    }
                }                               
            }
        }
        printf("float flag %d\n", float_flag);
        for(int i = 0; i < stack_num - 2; i++) {                 
            if(float_flag) {
                if((id_info = get_id_info(scope, statement_stack[i])) != NULL) {
                    switch(id_info->type) {
                        case INT:
                            // fprintf(file, "iload %d\n", id_info->reg_num);
                            // fprintf(file, "i2f\n");                           
                            break;
                        case FLOAT:
                            // fprintf(file, "fload %d\n", id_info->reg_num);
                            break;
                        default:
                            break;
                    }
                } else {
                    int is_float = 0;
                    for(int j  = 0; j < strlen(statement_stack[i]); j++) {
                        if(statement_stack[i][j] == '.') {
                            is_float = 1;
                            break;
                        }
                    }
                    if(is_float) {
                        // fprintf(file, "ldc %s\n", statement_stack[i]);                        
                    } else {
                        // fprintf(file, "ldc %s\n", statement_stack[i]);
                        // fprintf(file, "i2f\n");                                                                                                  
                    }
                }
            } else {
                sprintf(buf, "%s\n", statement_stack[i]);
                genPrint(buf);
                if((id_info = get_id_info(scope, statement_stack[i])) != NULL) {
                    switch(id_info->type) {
                        case INT:
                            sprintf(buf, "iload %d", id_info->reg_num);
                            genPrint(buf);
                            break;
                        default:
                            break;
                    }
                } else if (!strcmp(statement_stack[i], "ADD")){
                    sprintf(buf, "iadd");
                    genPrint(buf);
                } else {
                    sprintf(buf, "ldc %s", statement_stack[i]);
                    genPrint(buf);
                }
            }
        }
        if((id_info = get_id_info(scope, statement_stack[stack_num - 1])) != NULL) {
            if(id_info->type == FLOAT) {
                if(!float_flag) {
                    sprintf(buf, "i2f");
                    genPrint(buf);
                }
                if(!strcmp(statement_stack[stack_num - 2], "ASGN")) {
                    sprintf(buf, "fstore %s", id_info->reg_num);
                    genPrint(buf);
                }
            } else if(id_info->type == INT) {
                if(float_flag) {
                    sprintf(buf, "f2i");
                    genPrint(buf);
                }
                if(!strcmp(statement_stack[stack_num - 2], "ASGN")) {
                    sprintf(buf, "istore %d", id_info->reg_num);
                    genPrint(buf);
                }
            }
        }
        printf("--------------------------------\n");    
    }
}
