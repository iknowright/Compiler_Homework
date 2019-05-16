/*	Definition section */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void insert_symbol(Node** head_ref, int index, char * name, kindEnum kind, int type, int scope, char * attribute);
void dump_symbol(int scope);
int lookup_symbol(int scope);

extern int dump_flag;

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
%token <i_val> I_CONST
%token <f_val> F_CONST
%token <string> STR_CONST
%token <i_val> TRUE
%token <i_val> FALSE
%token <string> ID
// code added


/* Nonterminal with return, which need to sepcify type */
%type <i_val> type

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
    : type ID LB parameter_list RB block_body
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
    | function_call
    | return_statement 
;

function_call
    : ID LB argument_list RB SEMICOLON
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
    : ID assignment_operator expression SEMICOLON
;

return_statement
    : RETURN expression SEMICOLON

printf_statement
    : PRINT LB QUOTA STR_CONST QUOTA RB SEMICOLON
    | PRINT LB ID RB SEMICOLON
;

function_declaration
    : type ID LB parameter_list RB SEMICOLON
;

variable_declaration
    : type ID SEMICOLON
    | type ID ASGN expression SEMICOLON

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
    : LCB { scope++; printf(" (----Scope Start---- %d)\n", scope);}
;

right_brace
    : RCB { printf(" (----Scope End---- %d)\n", scope); dump_flag = 1; scope--; }
;

expression
    : assignment_expression
    |
;

parameter_list
    : parameter
    | parameter_list COMMA parameter
    |
;

parameter
    : type ID { 
        printf(" (----%d %s scope-%d----)\n", $1, $2, scope+1);
        insert_symbol(&table[scope+1], scope_index[scope+1], $2, PARAMETER, $1, scope+1, "");
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
	: ID { printf("( ID = %s )\n", yytext); }
	| constant
    | string
	| LB expression RB
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
int main(int argc, char** argv)
{
    yylineno = 0;
        
    yyparse();
	printf("\nTotal lines: %d \n",yylineno);

    return 0;
}

void yyerror(char *s)
{
    printf("%d: %s\n", yylineno + 1, buf);
    printf("\n|-----------------------------------------------|\n");
    printf("| Error found in line %d: %s\n", yylineno + 1, buf);
    printf("| %s", s);
    printf("\n|-----------------------------------------------|\n\n");
}

void insert_symbol(Node** head_ref, int index, char * name, kindEnum kind, int type, int scope, char * attribute)
{
    Node *last = *head_ref;
    Node * new_node = (Node *)malloc(sizeof(Node));
    new_node->index = index;
    new_node->name = name;
    new_node->kind = kind;
    new_node->type = type;
    new_node->scope = scope;
    new_node->attribute = attribute;
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

int lookup_symbol(int scope)
{

}

void dump_symbol(int scope) {
    if(table[scope] == NULL) {
        return;
    }
    printf("\n%-10s%-10s%-12s%-10s%-10s%-10s\n\n",
           "Index", "Name", "Kind", "Type", "Scope", "Attribute");
    Node * tmp = table[scope];
    while(tmp->next != NULL) {
        printf("%-10d%-10s%-12d%-10d%-10d%-10s\n",
           tmp->index, tmp->name, tmp->kind, tmp->type, tmp->scope, tmp->attribute);
        free(tmp);
        tmp = tmp->next;
    }
    printf("%-10d%-10s%-12d%-10d%-10d%-10s\n\n",
        tmp->index, tmp->name, tmp->kind, tmp->type, tmp->scope, tmp->attribute);
    free(tmp);
    table[scope] = NULL;
}
