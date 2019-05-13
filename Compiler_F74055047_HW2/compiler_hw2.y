/*	Definition section */
%{
#include <stdio.h>
#include <stdlib.h>

extern int yylineno;
extern int yylex();
extern char* yytext;   // Get current token from lex
extern char buf[256];  // Get current code line from lex

/* Symbol table function - you can add new function if needed. */
int lookup_symbol();
void create_symbol();
void insert_symbol();
void dump_symbol();



%}

/* Use variable or self-defined structure to represent
 * nonterminal and token type
 */
%union {
    int i_val;
    double f_val;
    char* string;
}

/* Token without return */
%token PRINT
%token IF ELSE WHILE
%token ID SEMICOLON COMMA QUOTA
%token ADD SUB MUL DIV MOD INC DEC
%token MT LT MTE LTE EQ NE
%token ASGN ADDASGN SUBASGN MULASGN DIVASGN MODASGN
%token AND OR NOT
%token LB RB LCB RCB LSB RSB
%token VOID FLOAT INT STRING BOOL
%token RETURN
%token TRUE FALSE
%token CPP_COMMENT C_COMMENT

/* Token with return, which need to sepcify type */
%token <i_val> I_CONST
%token <f_val> F_CONST
%token <string> STR_CONST
// code added


/* Nonterminal with return, which need to sepcify type */


/* Yacc will start at this nonterminal */
%start program

/* Grammar section */
%%

program
    : program program_body { printf(" ( program_body )\n"); }
    |
;

program_body
    : function_declaration
    | function { printf(" ( function definition )\n"); }
;

function
    : type ID LB parameter_list RB block_body

stats
    : stats stat
    |

stat
    : while_statement { printf(" ( while_statement )\n"); }
    | variable_declaration { printf(" ( variable_declaration )\n"); }
;

declaration
    : function_declaration { printf(" (detected function)");}
;

function_declaration
    : type ID LB parameter_list RB SEMICOLON 
;

variable_declaration
    : type ID SEMICOLON { printf(" (variable declared without initialization)");}
    | type ID ASGN expression SEMICOLON { printf(" (variable declared with initialization)");}

while_statement
    : WHILE LB expression RB block_body
;

block_body
    : LCB stats RCB
;

expression
    :
;

parameter_list
    : parameter
    | parameter_list COMMA parameter
    |
;

parameter
    : type ID
;

type
    : VOID { printf(" (VOID)"); }
    | INT { printf(" (INT)"); }
    | FLOAT { printf(" (FLOAT)"); }
    | BOOL { printf(" (BOOL)"); }
    | STRING { printf(" (STRING)"); }

%%

#include <stdio.h>

/* C code section */
int main(int argc, char** argv)
{
    yylineno = 0;

    yyparse();
	printf("\nTotal lines: %d \n",yylineno+1);

    return 0;
}

void yyerror(char *s)
{
    printf("\n|-----------------------------------------------|\n");
    printf("| Error found in line %d: %s\n", yylineno+1, buf);
    printf("| %s", s);
    printf("\n|-----------------------------------------------|\n\n");
}

void create_symbol() {}
void insert_symbol() {}
int lookup_symbol() {}
void dump_symbol() {
    printf("\n%-10s%-10s%-12s%-10s%-10s%-10s\n\n",
           "Index", "Name", "Kind", "Type", "Scope", "Attribute");
}
