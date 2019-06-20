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
    int reg_num;
} Node;

int scope;

Node * table[100] = { NULL };

int scope_index[100];

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
Node * get_id_info(int curr_scope, char * id);
void clearStatementStack();
char * printStatementStack(char * method);
int is_global(char * id);
char * getParamTypes(int scope);
char * get_attribute(char * attr);
char * doRelational();
char * printWhile(char * relation, char * body);

int stack_num = 0;
int while_index = 0;

extern int dump_flag;
extern void yyerror(char * s);
extern int semantic_flag;
int syntactic_flag;
char error_str[100];
int forward_flag;

char global_value[100];

char statement_stack[100][100];
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
// %token ASGN ADDASGN SUBASGN MULASGN DIVASGN MODASGN
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
%token <string> ASGN
%token <string> MULASGN
%token <string> DIVASGN 
%token <string> MODASGN
%token <string> ADDASGN
%token <string> SUBASGN
// code added


/* Nonterminal with return, which need to sepcify type */
%type <i_val> type
%type <string> parameter_list parameter
%type <string> constant assignment_operator
%type <string> stat stats printf_statement block_body expression_statement return_statement relation
%type <string> while_statement

/* Yacc will start at this nonterminal */
%start program

/* Grammar section */
%%

program 
    : program program_body
    |
;

program_body
    : function_declaration { clearStatementStack(); }
    | variable_declaration { clearStatementStack(); }
    | function
;

function
    : type ID LB parameter_list RB block_body {
        if(!forward_flag) {
            if(!lookup_symbol(scope, $2, FUNCTION)) {
                int max_reg = lookup_reg(scope);
                insert_symbol(&table[scope], scope_index[scope], $2, FUNCTION, $1, scope, $4, 0, max_reg + 1);
                scope_index[scope]++;
                char  * param = getParamTypes(scope + 1);
                printf("PARAMETER = %s\n", param);
                genFunction($2, $6, $1, param);
                strcpy($4, "");
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
    : stats stat {
            char buffer_total[3000];
            strcpy(buffer_total, "");
            sprintf(buffer_total, "%s%s", $1, $2);
            $$ = strdup(buffer_total); 
        }
    | { $$ = strdup(""); }

stat
    : while_statement { $$ = $1; clearStatementStack();}
    | if_statement { $$ = strdup(""); clearStatementStack();}
    | variable_declaration { $$=printStatementStack("assignment"); clearStatementStack(); }
    | printf_statement { $$ = $1; }
    | expression_statement { $$=$1; clearStatementStack(); }
    | return_statement { 
        $$=$1;
        clearStatementStack();}
;

function_call
    : ID LB argument_list RB {     
            if(!lookup_symbol(scope, $1, FUNCTION)) {
                semantic_flag = 1;
                strcpy(error_str, "Undeclared function ");
                strcat(error_str, $1);

            } else {
                strcpy(statement_stack[stack_num++],$1);
            }
        }
;

argument_list
    : assignment_expression
    | argument_list COMMA assignment_expression
    |
;

expression_statement
    : assign_statement { 
        $$=printStatementStack("assignment");clearStatementStack();
    }
    | expression SEMICOLON {
            $$=printStatementStack("expression"); clearStatementStack();
        }
    | SEMICOLON { $$=strdup(""); }
;

assign_statement
    : ID assignment_operator expression SEMICOLON {
            strcpy(statement_stack[stack_num++],$2);
            strcpy(statement_stack[stack_num++],$1);
            if(!lookup_symbol(scope, $1, VARIABLE)) {
                semantic_flag = 1;
                strcpy(error_str, "Undeclared variable ");
                strcat(error_str, $1);
            }
        }
;

return_statement
    : RETURN expression SEMICOLON {
        $$ =printStatementStack("expression");
    }

printf_statement
    : PRINT LB QUOTA STR_CONST QUOTA RB SEMICOLON { $$ = genPrintStrConst($4); }
    | PRINT LB constant RB SEMICOLON { $$ = genPrintConst($3);  }
    | PRINT LB ID RB SEMICOLON {
            if(!lookup_symbol(scope, $3, VARIABLE)) {
                semantic_flag = 1;
                strcpy(error_str, "Undeclared variable ");
                strcat(error_str, $3);
                $$ = strdup("");
            } else {              
                Node * id_info = get_id_info(scope, $3);
                if(id_info != NULL) {                
                    $$ = genPrintID(id_info->reg_num, id_info->type, id_info->scope, $3);
                }
            }
        }
;

function_declaration
    : type ID LB parameter_list RB SEMICOLON {
        if(!lookup_symbol(scope, $2, FUNCTION)) {
            int max_reg = lookup_reg(scope);
            insert_symbol(&table[scope], scope_index[scope], $2, FUNCTION, $1, scope, $4, 1, max_reg + 1);
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
                int max_reg = lookup_reg(scope);
                insert_symbol(&table[scope], scope_index[scope], $2, VARIABLE, $1, scope, "", 0, max_reg + 1);
                if(scope == 0) {
                    genVarDeclr($2, $1);
                } else {
                    strcpy(statement_stack[stack_num++],$2);
                }
                scope_index[scope]++;
            } else {
                semantic_flag = 1;
                strcpy(error_str, "Redeclared variable ");
                strcat(error_str, $2);
            }
        }
    | type ID ASGN expression SEMICOLON {
            if(!lookup_symbol(scope, $2, VARIABLE)) {
                int max_reg = lookup_reg(scope);
                insert_symbol(&table[scope], scope_index[scope], $2, VARIABLE, $1, scope, "", 0, max_reg + 1);
                if(scope == 0) {
                    genVarDeclrVal($2, $1, global_value);
                } else {
                    strcpy(statement_stack[stack_num++],"ASGN");
                    strcpy(statement_stack[stack_num++],$2);
                }
                scope_index[scope]++;
            } else {
                semantic_flag = 1;
                strcpy(error_str, "Redeclared variable ");
                strcat(error_str, $2);
            }
        }

while_statement
    : WHILE LB relation RB block_body {
        $$=printWhile($3, $5);
        while_index --;
    }
;

relation
    : expression {
        $$=doRelational(); clearStatementStack();
    }
;

if_statement
	: IF LB expression RB block_body ELSE block_body
    | IF LB expression RB block_body ELSE if_statement
	| IF LB expression RB block_body
;

block_body
    : left_brace stats right_brace { 
        printf("where are you stats : \n%s\n", $2);$$ = $2;    
    }
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
        if(!forward_flag){
            int max_reg = lookup_reg(scope + 1);
            insert_symbol(&table[scope+1], scope_index[scope+1], $2, PARAMETER, $1, scope+1, "", 0, max_reg + 1);
        }
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
    : unary_expression assignment_operator assignment_expression { strcpy(statement_stack[stack_num++],$2); }
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
    | additive_expression ADD multiplicative_expression { strcpy(statement_stack[stack_num++],"ADD"); }
    | additive_expression SUB multiplicative_expression { strcpy(statement_stack[stack_num++],"SUB"); }
;

multiplicative_expression
    : unary_expression
    | multiplicative_expression MUL unary_expression { strcpy(statement_stack[stack_num++],"MUL"); }
    | multiplicative_expression DIV unary_expression { strcpy(statement_stack[stack_num++],"DIV"); }
    | multiplicative_expression MOD unary_expression { strcpy(statement_stack[stack_num++],"MOD"); }
;

relational_operator
    : MT { strcpy(statement_stack[stack_num++],"MT"); }
    | LT { strcpy(statement_stack[stack_num++],"LT"); }
    | MTE { strcpy(statement_stack[stack_num++],"MTE"); }
    | LTE { strcpy(statement_stack[stack_num++],"LTE"); }
    | EQ { strcpy(statement_stack[stack_num++],"EQ"); }
    | NE { strcpy(statement_stack[stack_num++],"NE"); }
;

assignment_operator
	: ASGN { $$ = strdup($1); }
	| MULASGN { $$ = strdup($1); }
	| DIVASGN { $$ = strdup($1); }
	| MODASGN { $$ = strdup($1); }
	| ADDASGN { $$ = strdup($1); }
	| SUBASGN { $$ = strdup($1); }
	;

unary_expression
    : postfix_expression
	| INC unary_expression { strcpy(statement_stack[stack_num++],"preINC"); }
	| DEC unary_expression { strcpy(statement_stack[stack_num++],"preDEC"); }
    | unary_operator unary_expression
;

unary_operator
    : SUB { strcpy(statement_stack[stack_num++],"SUB"); }
    | ADD { strcpy(statement_stack[stack_num++],"ADD"); }
    | NOT { strcpy(statement_stack[stack_num++],"NOT"); }
;


postfix_expression
    : primary_expression
    | postfix_expression INC { strcpy(statement_stack[stack_num++],"postINC"); }
	| postfix_expression DEC { strcpy(statement_stack[stack_num++],"postDEC"); }
;

primary_expression
	: ID {  
            strcpy(statement_stack[stack_num++],$1);
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
    : QUOTA STR_CONST QUOTA {
        char the_string[100];
        sprintf(the_string, "\"%s\"", $2);
        strcpy(global_value, the_string);
        strcpy(statement_stack[stack_num++],the_string);
    }
;

constant
    : I_CONST { strcpy(global_value, $1); $$ = strdup($1); strcpy(statement_stack[stack_num++],$1); }
    | F_CONST { strcpy(global_value, $1); $$ = strdup($1); strcpy(statement_stack[stack_num++],$1); }
    | TRUE { strcpy(global_value, $1); $$ = strdup($1); strcpy(statement_stack[stack_num++],$1); }
    | FALSE { strcpy(global_value, $1); $$ = strdup($1); strcpy(statement_stack[stack_num++],$1); }
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

Node * get_id_info(int curr_scope, char * id)
{
    int i;   
    Node * the_node = NULL;
    for(i = curr_scope; i >= 0; i--) {
        if(table[i] != NULL) {
            Node * tmp = table[i];
            while(tmp->next != NULL) {
                if(!strcmp(tmp->name, id)) {
                    the_node = tmp;
                }
                tmp = tmp->next;
            }
            if(!strcmp(tmp->name, id)) {
                the_node = tmp;
            }
        }
    }
    return the_node;
}

char * getParamTypes(int scope)
{
    Node * tmp = table[scope];
    char param[10];
    strcpy(param, "");
    if(tmp != NULL) {
        while(tmp->next != NULL) {
            if(tmp->kind == PARAMETER) {
                if(tmp->type == INT) {
                    strcat(param, "I");
                } else if(tmp->type == FLOAT) {
                    strcat(param, "F");                    
                } else if(tmp->type == BOOL) {
                    strcat(param, "Z");                    
                }
            }
            tmp = tmp->next;
        }
        if(tmp->kind == PARAMETER) {
            if(tmp->kind == PARAMETER) {
                if(tmp->type == INT) {
                    strcat(param, "I");                    
                } else if(tmp->type == FLOAT) {
                    strcat(param, "F");                    
                } else if(tmp->type == BOOL) {
                    strcat(param, "Z");                    
                }
            }   
        }
    }
    return strdup(param);
}

void clearStatementStack()
{
    int i;
    for(i = 0; i < stack_num; i++) {
        strcpy(statement_stack[i], "");
    }
    stack_num = 0;
}

int is_global(char * id) {
    int flag = 0;
    int i;
    Node * tmp = table[0];
    while(tmp->next != NULL) {
        if(!strcmp(tmp->name, id)) {
            flag = 1;
            break;
        }
        tmp = tmp->next;
    }
    if(!strcmp(tmp->name, id)) {
        flag = 1;
    }
    return flag;
}

char * printStatementStack(char * method)
{
    int previous_reg = 0;
    char buffer[1000];
    char tmp[1000];    
    char buf[100];
    strcpy(buffer, "");
    strcpy(tmp, "");
    if(scope && stack_num > 0 && !semantic_flag) {     
        printf("---------------open-----------------\n");
        printf("%s\n", method);        
        printf("Scope %d\n\n", scope);
        int float_flag = 0;
        Node * id_info;    
        for(int i = 0; i < stack_num; i++) {
            printf("%s ", statement_stack[i]);
        }
        printf("\n\nStack size %d\n", stack_num);
        printf("Semantic flag %d\n", semantic_flag);
        // Only Declaration
        if(stack_num == 1 && !strcmp(method,"assignment")) {
            if((id_info = get_id_info(scope, statement_stack[0])) != NULL) {
                if(id_info->type == FLOAT) {
                    sprintf(buffer, "ldc 0.0\nfstore %d\n", id_info->reg_num);
                } else if(id_info->type == INT) {
                    sprintf(buffer, "ldc 0\nistore %d\n", id_info->reg_num);
                } else if(id_info->type == BOOL) {
                    sprintf(buffer, "ldc 0\nistore %d\n", id_info->reg_num);
                } else if(id_info->type == STRING) {
                    sprintf(buffer, "ldc \"\"\nastore %d\n", id_info->reg_num);
                }
            }
            printf("---------------close-----------------\n");            
            return strdup(buffer);
        }
        if(stack_num >= 3 && !strcmp(method, "assignment")){
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
            printf("Float flag %d\n", float_flag);
            for(int i = 0; i < stack_num - 2; i++) {                 
                if(float_flag) {
                    if((id_info = get_id_info(scope, statement_stack[i])) != NULL) {
                        switch(id_info->type) {
                            case INT:
                                if(id_info->scope == 0) {
                                    sprintf(buf, "getstatic compiler_hw3/%s I\ni2f\n", statement_stack[i]);
                                    strcpy(tmp, buffer);
                                    sprintf(buffer, "%s%s", tmp, buf);                                
                                } else {
                                    sprintf(buf, "iload %d\ni2f\n", id_info->reg_num);
                                    strcpy(tmp, buffer);
                                    sprintf(buffer, "%s%s", tmp, buf);
                                }
                                break;                       
                            case FLOAT:
                                if(id_info->scope == 0) {
                                    sprintf(buf, "getstatic compiler_hw3/%s F\n", statement_stack[i]);
                                    strcpy(tmp, buffer);
                                    sprintf(buffer, "%s%s", tmp, buf);                                
                                } else {
                                    sprintf(buf, "fload %d\n", id_info->reg_num);
                                    strcpy(tmp, buffer);
                                    sprintf(buffer, "%s%s", tmp, buf);
                                }
                                break;
                            default:
                                break;
                        }
                    } else if (!strcmp(statement_stack[i], "ADD")){
                        sprintf(buf, "fadd\n");
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if (!strcmp(statement_stack[i], "SUB")){
                        sprintf(buf, "fsub\n");
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if (!strcmp(statement_stack[i], "MUL")){
                        sprintf(buf, "fmul\n");
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if (!strcmp(statement_stack[i], "DIV")){
                        sprintf(buf, "fdiv\n");
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else {
                        int is_float = 0;
                        for(int j  = 0; j < strlen(statement_stack[i]); j++) {
                            if(statement_stack[i][j] == '.') {
                                is_float = 1;
                                break;
                            }
                        }
                        if(is_float) {
                            sprintf(buf, "ldc %s\n", statement_stack[i]);
                            strcpy(tmp, buffer);
                            sprintf(buffer, "%s%s", tmp, buf);
                        } else {
                            sprintf(buf, "ldc %s\ni2f\n", statement_stack[i]);
                            strcpy(tmp, buffer);
                            sprintf(buffer, "%s%s", tmp, buf);                                                                                      
                        }
                    }
                } else {
                    if((id_info = get_id_info(scope, statement_stack[i])) != NULL) {
                        switch(id_info->type) {
                            case INT:
                                if(id_info->scope == 0) {
                                    if(id_info->kind = FUNCTION) {
                                        char * param = get_attribute(id_info->attribute);
                                        sprintf(buf, "invokestatic compiler_hw3/%s(%s)I\n", statement_stack[i], param);
                                        strcpy(tmp, buffer);
                                        sprintf(buffer, "%s%s", tmp, buf);
                                    } else {
                                        sprintf(buf, "getstatic compiler_hw3/%s I\n", statement_stack[i]);
                                        strcpy(tmp, buffer);
                                        sprintf(buffer, "%s%s", tmp, buf);                                
                                    }
                                } else {
                                    sprintf(buf, "iload %d\n", id_info->reg_num);
                                    strcpy(tmp, buffer);
                                    sprintf(buffer, "%s%s", tmp, buf);
                                }
                                break;
                            case BOOL:
                                if(id_info->scope == 0) {
                                    if(id_info->kind = FUNCTION) {
                                        char * param = get_attribute(id_info->attribute);
                                        sprintf(buf, "invokestatic compiler_hw3/%s(%s)Z\n", statement_stack[i], param);
                                        strcpy(tmp, buffer);
                                        sprintf(buffer, "%s%s", tmp, buf);
                                    } else {
                                        sprintf(buf, "getstatic compiler_hw3/%s Z\n", statement_stack[i]);
                                        strcpy(tmp, buffer);
                                        sprintf(buffer, "%s%s", tmp, buf);                                
                                    }                                
                                } else {
                                    sprintf(buf, "iload %d\n", id_info->reg_num);
                                    strcpy(tmp, buffer);
                                    sprintf(buffer, "%s%s", tmp, buf);
                                }
                                break;
                            default:
                                break;
                        }
                    } else if (!strcmp(statement_stack[i], "ADD")){
                        sprintf(buf, "iadd\n");
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if (!strcmp(statement_stack[i], "SUB")){
                        sprintf(buf, "isub\n");
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if (!strcmp(statement_stack[i], "MUL")){
                        sprintf(buf, "imul\n");
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if (!strcmp(statement_stack[i], "DIV")){
                        sprintf(buf, "idiv\n");
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if (!strcmp(statement_stack[i], "MOD")){
                        sprintf(buf, "irem\n");
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else {
                        sprintf(buf, "ldc %s\n", statement_stack[i]);
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    }
                }
            }
            if((id_info = get_id_info(scope, statement_stack[stack_num - 1])) != NULL) {
                if(id_info->type == STRING) {
                    if(!strcmp(statement_stack[stack_num - 2], "ASGN")) {
                        sprintf(buf, "astore %d\n", id_info->reg_num);
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    }
                } else if(id_info->type == BOOL) {
                    if(!strcmp(statement_stack[stack_num - 2], "ASGN")) {
                        sprintf(buf, "istore %d\n", id_info->reg_num);
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    }
                } else if(id_info->type == FLOAT) {
                    if(!float_flag) {
                        sprintf(buf, "i2f\n");
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    }
                    if(!strcmp(statement_stack[stack_num - 2], "ASGN")) {
                        sprintf(buf, "fstore %d\n", id_info->reg_num);
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if(!strcmp(statement_stack[stack_num - 2], "ADDASGN")) {
                        sprintf(buf, "fstore 30\nfload %d\nfload 30\nfadd\nfstore %d\n", id_info->reg_num, id_info->reg_num);
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if(!strcmp(statement_stack[stack_num - 2], "SUBASGN")) {
                        sprintf(buf, "fstore 30\nfload %d\nfload 30\nfsub\nfstore %d\n", id_info->reg_num, id_info->reg_num);
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if(!strcmp(statement_stack[stack_num - 2], "MULASGN")) {
                        sprintf(buf, "fstore 30\nfload %d\nfload 30\nfmul\nfstore %d\n", id_info->reg_num, id_info->reg_num);
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if(!strcmp(statement_stack[stack_num - 2], "DIVASGN")) {
                        sprintf(buf, "fstore 30\nfload %d\nfload 30\nfdiv\nfstore %d\n", id_info->reg_num, id_info->reg_num);
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    }
                } else if(id_info->type == INT) {
                    if(float_flag) {
                        sprintf(buf, "f2i\n");
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    }
                    if(!strcmp(statement_stack[stack_num - 2], "ASGN")) {
                        sprintf(buf, "istore %d\n", id_info->reg_num);
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if(!strcmp(statement_stack[stack_num - 2], "ADDASGN")) {
                        sprintf(buf, "istore 40\niload %d\niload 40\niadd\nistore %d\n", id_info->reg_num, id_info->reg_num);
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if(!strcmp(statement_stack[stack_num - 2], "SUBASGN")) {
                        sprintf(buf, "istore 40\niload %d\niload 40\nisub\nistore %d\n", id_info->reg_num, id_info->reg_num);
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if(!strcmp(statement_stack[stack_num - 2], "MULASGN")) {
                        sprintf(buf, "istore 40\niload %d\niload 40\nimul\nistore %d\n", id_info->reg_num, id_info->reg_num);
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if(!strcmp(statement_stack[stack_num - 2], "DIVASGN")) {
                        sprintf(buf, "istore 40\niload %d\niload 40\nidiv\nistore %d\n", id_info->reg_num, id_info->reg_num);
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if(!strcmp(statement_stack[stack_num - 2], "MODASGN")) {
                        sprintf(buf, "istore 40\niload %d\niload 40\nirem\nistore %d\n", id_info->reg_num, id_info->reg_num);
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    }
                }
            }
        } else if(!strcmp(method, "expression")) { 
            for(int i = 0; i < stack_num; i++) {                 
                if(float_flag) {
                    if((id_info = get_id_info(scope, statement_stack[i])) != NULL) {
                        switch(id_info->type) {
                            case INT:
                                if(id_info->scope == 0) {
                                    sprintf(buf, "getstatic compiler_hw3/%s I\ni2f\n", statement_stack[i]);
                                    strcpy(tmp, buffer);
                                    sprintf(buffer, "%s%s", tmp, buf);                                
                                } else {
                                    sprintf(buf, "iload %d\ni2f\n", id_info->reg_num);
                                    strcpy(tmp, buffer);
                                    sprintf(buffer, "%s%s", tmp, buf);
                                }
                                break;                       
                            case FLOAT:
                                if(id_info->scope == 0) {
                                    sprintf(buf, "getstatic compiler_hw3/%s F\n", statement_stack[i]);
                                    strcpy(tmp, buffer);
                                    sprintf(buffer, "%s%s", tmp, buf);                                
                                } else {
                                    sprintf(buf, "fload %d\n", id_info->reg_num);
                                    strcpy(tmp, buffer);
                                    sprintf(buffer, "%s%s", tmp, buf);
                                }
                                break;
                            case VOID:
                                if(id_info->kind = FUNCTION) {
                                    char * param = get_attribute(id_info->attribute);
                                    sprintf(buf, "invokestatic compiler_hw3/%s(%s)I\n", statement_stack[i], param);
                                    strcpy(tmp, buffer);
                                    sprintf(buffer, "%s%s", tmp, buf);
                                } else {
                                    sprintf(buf, "getstatic compiler_hw3/%s I\n", statement_stack[i]);
                                    strcpy(tmp, buffer);
                                    sprintf(buffer, "%s%s", tmp, buf);                                
                                }
                            default:
                                break;
                        }
                    } else if (!strcmp(statement_stack[i], "ADD")){
                        sprintf(buf, "fadd\n");
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if (!strcmp(statement_stack[i], "SUB")){
                        sprintf(buf, "fsub\n");
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if (!strcmp(statement_stack[i], "MUL")){
                        sprintf(buf, "fmul\n");
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if (!strcmp(statement_stack[i], "DIV")){
                        sprintf(buf, "fdiv\n");
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else {
                        int is_float = 0;
                        for(int j  = 0; j < strlen(statement_stack[i]); j++) {
                            if(statement_stack[i][j] == '.') {
                                is_float = 1;
                                break;
                            }
                        }
                        if(is_float) {
                            sprintf(buf, "ldc %s\n", statement_stack[i]);
                            strcpy(tmp, buffer);
                            sprintf(buffer, "%s%s", tmp, buf);
                        } else {
                            sprintf(buf, "ldc %s\ni2f\n", statement_stack[i]);
                            strcpy(tmp, buffer);
                            sprintf(buffer, "%s%s", tmp, buf);                                                                                      
                        }
                    }
                } else {
                    if((id_info = get_id_info(scope, statement_stack[i])) != NULL) {
                        previous_reg = id_info->reg_num;
                        switch(id_info->type) {
                            case INT:
                                if(id_info->scope == 0) {
                                        if(id_info->kind = FUNCTION) {
                                        char * param = get_attribute(id_info->attribute);
                                        sprintf(buf, "invokestatic compiler_hw3/%s(%s)I\n", statement_stack[i], param);
                                        strcpy(tmp, buffer);
                                        sprintf(buffer, "%s%s", tmp, buf);
                                    } else {
                                        sprintf(buf, "getstatic compiler_hw3/%s I\n", statement_stack[i]);
                                        strcpy(tmp, buffer);
                                        sprintf(buffer, "%s%s", tmp, buf);                                
                                    }                                
                                } else {
                                    sprintf(buf, "iload %d\n", id_info->reg_num);
                                    strcpy(tmp, buffer);
                                    sprintf(buffer, "%s%s", tmp, buf);
                                }
                                break;
                            case BOOL:
                                if(id_info->scope == 0) {
                                    if(id_info->kind = FUNCTION) {
                                        char * param = get_attribute(id_info->attribute);
                                        sprintf(buf, "invokestatic compiler_hw3/%s(%s)Z\n", statement_stack[i], param);
                                        strcpy(tmp, buffer);
                                        sprintf(buffer, "%s%s", tmp, buf);
                                    } else {
                                        sprintf(buf, "getstatic compiler_hw3/%s Z\n", statement_stack[i]);
                                        strcpy(tmp, buffer);
                                        sprintf(buffer, "%s%s", tmp, buf);                                
                                    }                          
                                } else {
                                    sprintf(buf, "iload %d\n", id_info->reg_num);
                                    strcpy(tmp, buffer);
                                    sprintf(buffer, "%s%s", tmp, buf);
                                }
                                break;
                            case VOID:
                                if(id_info->kind = FUNCTION) {
                                    char * param = get_attribute(id_info->attribute);
                                    sprintf(buf, "invokestatic compiler_hw3/%s(%s)V\n", statement_stack[i], param);
                                    strcpy(tmp, buffer);
                                    sprintf(buffer, "%s%s", tmp, buf);
                                } else {
                                    sprintf(buf, "getstatic compiler_hw3/%s I\n", statement_stack[i]);
                                    strcpy(tmp, buffer);
                                    sprintf(buffer, "%s%s", tmp, buf);                                
                                }
                            default:
                                break;
                        }
                    } else if (!strcmp(statement_stack[i], "ADD")){
                        sprintf(buf, "iadd\n");
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if (!strcmp(statement_stack[i], "SUB")){
                        sprintf(buf, "isub\n");
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if (!strcmp(statement_stack[i], "MUL")){
                        sprintf(buf, "imul\n");
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if (!strcmp(statement_stack[i], "DIV")){
                        sprintf(buf, "idiv\n");
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if (!strcmp(statement_stack[i], "MOD")){
                        sprintf(buf, "irem\n");
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if (!strcmp(statement_stack[i], "postINC")){
                        sprintf(buf, "istore 40\nldc 1\niload 40\niadd\nistore %d\n", previous_reg, previous_reg);
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if (!strcmp(statement_stack[i], "postSUB")){
                        sprintf(buf, "istore 40\nldc 1\niload 40\nisub\nistore %d\n", previous_reg, previous_reg);
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if (!strcmp(statement_stack[i], "preINC")){
                        sprintf(buf, "istore 40\nldc 1\niload 40\niadd\nistore %d\n", previous_reg, previous_reg);
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    } else if (!strcmp(statement_stack[i], "preSUB")){
                        sprintf(buf, "istore 40\nldc 1\niload 40\nisub\nistore %d\n", previous_reg, previous_reg);
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    }else {
                        sprintf(buf, "ldc %s\n", statement_stack[i]);
                        strcpy(tmp, buffer);
                        sprintf(buffer, "%s%s", tmp, buf);
                    }
                }
            }
        }
        printf("---------------close-----------------\n");    
    }
    return strdup(buffer);
}

char * get_attribute(char * attr)
{
    char * pch;
    char attribute[100];
    char sp_attr[10];
    strcpy(sp_attr, "");
    strcpy(attribute, attr);
    pch = strtok (attribute," ,.-");
    while (pch != NULL)
    {
        if(!strcmp(pch,"int")) {
            strcat(sp_attr, "I");               
        } else if(!strcmp(pch,"float")) {
            strcat(sp_attr, "F");
        } else if(!strcmp(pch,"bool")) {
            strcat(sp_attr, "Z");
        } else if(!strcmp(pch,"string")) {
            strcat(sp_attr, "Ljava/lang/String;");
        }
        pch = strtok (NULL, " ,.-");
    }
    return strdup(sp_attr);
}

char * doRelational()
{
    char buffer[1000];
    char tmp[1000];    
    char buf[100];
    strcpy(buffer, "");
    strcpy(tmp, "");   
    printf("---------------open-----------------\n");      
    printf("Scope %d\n\n", scope);
    int float_flag = 0;
    Node * id_info; 
    for(int i = 0; i < stack_num; i++) {
        printf("%s ", statement_stack[i]);
    }
    printf("\n\nStack size %d\n", stack_num);
    printf("Semantic flag %d\n", semantic_flag);
    for(int i = 0; i < stack_num; i++) {
        if((id_info = get_id_info(scope, statement_stack[0])) != NULL) {
            if(id_info->type == FLOAT) {
                float_flag = 1;
                break;
            }          
        } else {           
            for(int j  = 0; j < strlen(statement_stack[0]); j++) {
                if(statement_stack[0][j] == '.') {
                    float_flag = 1;
                    break;
                }
            }                               
        }
    }
    printf("Float flag %d\n", float_flag);
    // while label
    sprintf(buf, "LABEL_BEGIN:\n");
    strcpy(tmp, buffer);
    sprintf(buffer, "%s%s", tmp, buf);
    // latter
    // Former
    if(float_flag) {
        if((id_info = get_id_info(scope, statement_stack[0])) != NULL) {
            if(id_info->type == FLOAT) {
                sprintf(buf, "fload %d\n", id_info->reg_num);
                strcpy(tmp, buffer);
                sprintf(buffer, "%s%s", tmp, buf);
            } else if(id_info->type == INT){
                sprintf(buf, "i2f\nfload %d\n", id_info->reg_num);
                strcpy(tmp, buffer);
                sprintf(buffer, "%s%s", tmp, buf);
            }
        } else {
            int flag = 0;
            for(int j  = 0; j < strlen(statement_stack[0]); j++) {
                if(statement_stack[0][j] == '.') {
                    flag = 1;
                    break;
                }
            }
            if(flag) {
                sprintf(buf, "ldc %s\n", statement_stack[0]);
                strcpy(tmp, buffer);
                sprintf(buffer, "%s%s", tmp, buf);
            } else {
                sprintf(buf, "ldc %s\ni2f\n", statement_stack[0]);
                strcpy(tmp, buffer);
                sprintf(buffer, "%s%s", tmp, buf);
            }
        }
    } else {
        if((id_info = get_id_info(scope, statement_stack[0])) != NULL) {
            if(id_info->type == INT){
                sprintf(buf, "iload %d\n", id_info->reg_num);
                strcpy(tmp, buffer);
                sprintf(buffer, "%s%s", tmp, buf);
            }
        } else {
            sprintf(buf, "ldc\n", statement_stack[0]);
            strcpy(tmp, buffer);
            sprintf(buffer, "%s%s", tmp, buf);
        }
    }
    if(float_flag) {
        if((id_info = get_id_info(scope, statement_stack[2])) != NULL) {
            if(id_info->type == FLOAT) {
                sprintf(buf, "fload %d\n", id_info->reg_num);
                strcpy(tmp, buffer);
                sprintf(buffer, "%s%s", tmp, buf);
            } else if(id_info->type == INT){
                sprintf(buf, "i2f\nfload %d\n", id_info->reg_num);
                strcpy(tmp, buffer);
                sprintf(buffer, "%s%s", tmp, buf);
            }
        } else {
            int flag = 0;
            for(int j  = 0; j < strlen(statement_stack[2]); j++) {
                if(statement_stack[2][j] == '.') {
                    flag = 1;
                    break;
                }
            }
            if(flag) {
                sprintf(buf, "ldc %s\n", statement_stack[2]);
                strcpy(tmp, buffer);
                sprintf(buffer, "%s%s", tmp, buf);
            } else {
                sprintf(buf, "ldc %s\ni2f\n", statement_stack[2]);
                strcpy(tmp, buffer);
                sprintf(buffer, "%s%s", tmp, buf);
            }
        }
    } else {
        if((id_info = get_id_info(scope, statement_stack[2])) != NULL) {
            if(id_info->type == INT){
                sprintf(buf, "iload %d\n", id_info->reg_num);
                strcpy(tmp, buffer);
                sprintf(buffer, "%s%s", tmp, buf);
            }
        } else {
            sprintf(buf, "ldc %s\n", statement_stack[2]);
            strcpy(tmp, buffer);
            sprintf(buffer, "%s%s", tmp, buf);
        }
    }
    // substrate
    if(float_flag) {
        sprintf(buf, "fsub\n", statement_stack[0]);
        strcpy(tmp, buffer);
        sprintf(buffer, "%s%s", tmp, buf);
    } else {
        sprintf(buf, "isub\n", statement_stack[0]);
        strcpy(tmp, buffer);
        sprintf(buffer, "%s%s", tmp, buf);
    }
    // relational
    if (!strcmp(statement_stack[1], "MT")){
        sprintf(buf, "ifle LABEL_FALSE\ngoto LABEL_TRUE\n");
        strcpy(tmp, buffer);
        sprintf(buffer, "%s%s", tmp, buf);
    } else if (!strcmp(statement_stack[1], "LT")){
        sprintf(buf, "ifge LABEL_FALSE\ngoto LABEL_TRUE\n");
        strcpy(tmp, buffer);
        sprintf(buffer, "%s%s", tmp, buf);
    } else if (!strcmp(statement_stack[1], "MTE")){
        sprintf(buf, "iflt LABEL_FALSE\ngoto LABEL_TRUE\n");
        strcpy(tmp, buffer);
        sprintf(buffer, "%s%s", tmp, buf);
    } else if (!strcmp(statement_stack[1], "LTE")){
        sprintf(buf, "ifgt LABEL_FALSE\ngoto LABEL_TRUE\n");
        strcpy(tmp, buffer);
        sprintf(buffer, "%s%s", tmp, buf);
    } else if (!strcmp(statement_stack[1], "EQ")){
        sprintf(buf, "ifne LABEL_FALSE\ngoto LABEL_TRUE\n");
        strcpy(tmp, buffer);
        sprintf(buffer, "%s%s", tmp, buf);
    } else if (!strcmp(statement_stack[1], "NE")){
        sprintf(buf, "ifeg LABEL_FALSE\ngoto LABEL_TRUE\n");
        strcpy(tmp, buffer);
        sprintf(buffer, "%s%s", tmp, buf);
    }
    printf("---------------close-----------------\n");

    return strdup(buffer);
}

char * printWhile(char * relation, char * body) { 
    char buffer[1000];
    char tmp[1000];    
    char buf[100];
    strcpy(buffer, "");
    sprintf(buffer, "%sLABEL_TRUE:\n%sgoto LABEL_BEGIN\nLABEL_FALSE:\ngoto EXIT_0\nEXIT_0:\n", relation, body);
    return strdup(buffer);
}