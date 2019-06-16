/*	Definition section */
%{
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
} Node;

int scope;

Node * table[100] = { NULL };

int scope_index[100];

extern int yylineno;
extern int yylex();
extern char* yytext;   // Get current token from lex
extern char buf[256];  // Get current code line from lex

/* Symbol table function - you can add new function if needed. */
void insert_symbol(Node** head_ref, int index, char * name, kindEnum kind, int type, int scope, char * attribute, int func_flag);
void enum_to_string(char * stringkind, char * stringtype, int kind, int type);
void dump_symbol(int scope);
int lookup_symbol(int scope, char * name, kindEnum kind);
void custom_yyerror(char *s);

extern int dump_flag;
extern void yyerror(char * s);
extern int semantic_flag;
int syntactic_flag;
char error_str[100];
int forward_flag;

char global_value[100];
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
%token SEMICOLON COMMA QUOTA
%token ADD SUB MUL DIV MOD INC DEC
%token MT LT MTE LTE EQ NE
%token ASGN ADDASGN SUBASGN MULASGN DIVASGN MODASGN
%token AND OR NOT
%token LB RB LCB RCB LSB RSB
%token VOID FLOAT INT STRING BOOL
%token RETURN
%token CPP_COMMENT C_COMMENT

/* Token with return, which need to sepcify type */
%token <string> I_CONST
%token <string> F_CONST
%token <string> STR_CONST
%token <string> TRUE
%token <string> FALSE
%token <string> ID
// code added


/* Nonterminal with return, which need to sepcify type */
%type <i_val> type
%type <string> parameter_list parameter
// %type <string> unary_expression constant primary_expression postfix_expression
// %type <string> multiplicative_expression  additive_expression relational_expression logical_and_expression logical_or_expression assignment_expression expression
// %type <string> unary_operator

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
                printf("IM IN VARIABLE DECLRATION WITHOUT VALUE\n");
                genVarDeclr($2, $1);
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
                printf("IM IN VARIABLE DECLRATION WITH VALUE\n");
                genVarDeclrVal($2, $1, global_value);
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
    | { $$ = strdup(""); }
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
    : I_CONST { printf("%d ", $1); strcpy(global_value, yytext); printf("%s\n", global_value); }
    | F_CONST { printf("%f ", $1); } 
    | TRUE { printf("%d ", $1); } 
    | FALSE { printf("%d ", $1); } 
;

%%

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

void insert_symbol(Node** head_ref, int index, char * name, kindEnum kind, int type, int scope, char * attribute, int func_flag)
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
    printf("\n%-10s%-10s%-12s%-10s%-10s%-10s\n\n",
           "Index", "Name", "Kind", "Type", "Scope", "Attribute");
    Node * tmp = table[scope];
    while(tmp->next != NULL) {
        enum_to_string(stringkind, stringtype, tmp->kind, tmp->type);
        printf("%-10d%-10s%-12s%-10s%-10d%-s\n",
           tmp->index, tmp->name, stringkind, stringtype, tmp->scope, tmp->attribute);
        free(tmp);
        tmp = tmp->next;
    }
    enum_to_string(stringkind, stringtype, tmp->kind, tmp->type);
    printf("%-10d%-10s%-12s%-10s%-10d%-s\n\n",
        tmp->index, tmp->name, stringkind, stringtype, tmp->scope, tmp->attribute);
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