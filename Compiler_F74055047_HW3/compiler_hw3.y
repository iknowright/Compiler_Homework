/*	Definition section */
%{
#include "xxxx.h" // include header if needed

extern int yylineno;
extern int yylex();
extern char *yytext; // Get current token from lex
extern char buf[BUF_SIZE]; // Get current code line from lex

FILE *file; // To generate .j file for Jasmin

void yyerror(char *s);

/* symbol table functions */
int lookup_symbol();
void create_symbol_table();
void free_symbol_table();
void insert_symbol();
void dump_symbol();

/* code generation functions, just an example! */
void gencode_function();

%}

%union {
}

/* Token without return */
%token INC DEC
%token MTE LTE EQ NE
%token ADDASGN SUBASGN MULASGN DIVASGN MODASGN
%token PRINT IF ELSE
%token ID SEMICOLON
%token I_CONST F_CONST STRING

/* Yacc will start at this nonterminal */
%start program

/* Grammar section */
%%

program 
    : program program_body
    |
;

program_body
    : function_declaration
    | variable_declaration
    | function
;

function
    : type ID LB parameter_list RB block_body {
        if(!forward_flag) {
            if(!lookup_symbol(scope, $2, FUNCTION)) {
                insert_symbol(&table[scope], scope_index[scope], $2, FUNCTION, $1, scope, $4, 0);
                strcpy($4, "");
                scope_index[scope]++;
            } else if(lookup_symbol(scope, $2, FUNCTION) == 1){
                semantic_flag = 1;
                strcpy(error_str, "Redeclared function ");
                strcat(error_str, $2);
            }
        }
        strcpy($4, "");
        forward_flag = 0;
    }
;

stats
    : stats stat
    |

stat
    : while_statement
    | if_statement 
    | variable_declaration
    | printf_statement 
    | expression_statement 
    | return_statement 
;

function_call
    : ID LB argument_list RB {     
            if(!lookup_symbol(scope, $1, FUNCTION)) {
                semantic_flag = 1;
                strcpy(error_str, "Undeclared function ");
                strcat(error_str, $1);
            }
        }
;

argument_list
    : assignment_expression
    | argument_list COMMA assignment_expression
    |
;

expression_statement
    : assign_statement
    | expression SEMICOLON
    | SEMICOLON
;

assign_statement
    : ID assignment_operator expression SEMICOLON {        
            if(!lookup_symbol(scope, $1, VARIABLE)) {
                semantic_flag = 1;
                strcpy(error_str, "Undeclared variable ");
                strcat(error_str, $1);
            }
        }
;

return_statement
    : RETURN expression SEMICOLON

printf_statement
    : PRINT LB QUOTA STR_CONST QUOTA RB SEMICOLON
    | PRINT LB ID RB SEMICOLON {          
            if(!lookup_symbol(scope, $3, VARIABLE)) {
                semantic_flag = 1;
                strcpy(error_str, "Undeclared variable ");
                strcat(error_str, $3);
            }
        }
;

function_declaration
    : type ID LB parameter_list RB SEMICOLON {
        if(!lookup_symbol(scope, $2, FUNCTION)) {
            insert_symbol(&table[scope], scope_index[scope], $2, FUNCTION, $1, scope, $4, 1);
            strcpy($4, "");
            scope_index[scope]++;
        } else {
            semantic_flag = 1;
            strcpy(error_str, "Redeclared function ");
            strcat(error_str, $2);
        }
        forward_flag = 1;
    }
;

variable_declaration
    : type ID SEMICOLON {
            if(!lookup_symbol(scope, $2, VARIABLE)) {
                insert_symbol(&table[scope], scope_index[scope], $2, VARIABLE, $1, scope, "", 0);
                scope_index[scope]++;
            } else {
                semantic_flag = 1;
                strcpy(error_str, "Redeclared variable ");
                strcat(error_str, $2);
            }
        }
    | type ID ASGN expression SEMICOLON {
            if(!lookup_symbol(scope, $2, VARIABLE)) {
                insert_symbol(&table[scope], scope_index[scope], $2, VARIABLE, $1, scope, "", 0);
                scope_index[scope]++;
            } else {
                semantic_flag = 1;
                strcpy(error_str, "Redeclared variable ");
                strcat(error_str, $2);
            }
        }

while_statement
    : WHILE LB expression RB block_body
;

if_statement
	: IF LB expression RB block_body ELSE block_body
    | IF LB expression RB block_body ELSE if_statement
	| IF LB expression RB block_body
;

block_body
    : left_brace stats right_brace
;

left_brace
    : LCB { scope++; }
;

right_brace
    : RCB { dump_flag = 1; scope--; }
;

expression
    : assignment_expression
    |
;

parameter_list
    : parameter { $$ = strdup($1); }
    | parameter_list COMMA parameter {
            char * tmp;
            tmp = strdup(", ");
            strcat(tmp, $3);
            strcat($1, tmp);
            $$ = $1;
        }
    | { strcat($$, ""); }
;

parameter
    : type ID {
        if(!forward_flag) insert_symbol(&table[scope+1], scope_index[scope+1], $2, PARAMETER, $1, scope+1, "", 0);
        switch($1) {
            case VOID:
                $$ = strdup("void");
                break;
            case FLOAT:
                $$ = strdup("float");
                break;
            case INT:
                $$ = strdup("int");
                break;
            case STRING:
                $$ = strdup("string");
                break;
            case BOOL:
                $$ = strdup("bool");
                break;
            default: break;
        }
        scope_index[scope+1]++;
    }
;

type
    : VOID { $$ = VOID; }
    | INT { $$ = INT; }
    | FLOAT { $$ = FLOAT; }
    | BOOL { $$ = BOOL; }
    | STRING { $$ = STRING; }
;

assignment_expression
    : unary_expression assignment_operator assignment_expression
    | logical_or_expression
;

logical_or_expression
    : logical_and_expression
	| logical_or_expression OR logical_and_expression
;

logical_and_expression
    : relational_expression
	| logical_and_expression AND relational_expression
;

relational_expression
    : additive_expression
    | relational_expression relational_operator additive_expression 
;

additive_expression
    : multiplicative_expression
    | additive_expression ADD multiplicative_expression
    | additive_expression SUB multiplicative_expression
;

multiplicative_expression
    : unary_expression
    | multiplicative_expression MUL unary_expression
    | multiplicative_expression DIV unary_expression
    | multiplicative_expression MOD unary_expression
;

relational_operator
    : MT
    | LT
    | MTE
    | LTE
    | EQ
    | NE
;

assignment_operator
	: ASGN
	| MULASGN
	| DIVASGN
	| MODASGN
	| ADDASGN
	| SUBASGN
	;

unary_expression
    : postfix_expression
	| INC unary_expression
	| DEC unary_expression
    | unary_operator unary_expression
;

unary_operator
    : SUB
    | ADD
    | NOT
;


postfix_expression
    : primary_expression
    | postfix_expression INC
	| postfix_expression DEC
;

primary_expression
	: ID {    
            if(!lookup_symbol(scope, $1, VARIABLE)) {
                semantic_flag = 1;
                strcpy(error_str, "Undeclared variable ");
                strcat(error_str, $1);
            }
        }
	| constant
    | string
	| LB expression RB
    | function_call
	;
;

string
    : QUOTA STR_CONST QUOTA
;


constant
    : I_CONST 
    | F_CONST
    | TRUE
    | FALSE
;

%%

/* C code section */

/* C code section */
int main(int argc, char** argv)
{
    yylineno = 0;

    file = fopen("compiler_hw3.j","w");

    fprintf(file,   ".class public compiler_hw3\n"
                    ".super java/lang/Object\n"
                    ".method public static main([Ljava/lang/String;)V\n");

    yyparse();
    printf("\nTotal lines: %d \n",yylineno);

    fprintf(file, "\treturn\n"
                  ".end method\n");

    fclose(file);

    return 0;
}

void yyerror(char *s)
{
    printf("\n|-----------------------------------------------|\n");
    printf("| Error found in line %d: %s\n", yylineno, buf);
    printf("| %s", s);
    printf("\n| Unmatched token: %s", yytext);
    printf("\n|-----------------------------------------------|\n");
    exit(-1);
}

/* stmbol table functions */
void create_symbol() {}
void insert_symbol() {}
int lookup_symbol() {}
void dump_symbol() {}

/* code generation functions */
void gencode_function() {}
