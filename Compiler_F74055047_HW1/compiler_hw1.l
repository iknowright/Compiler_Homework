/* Definition section */
%{
	#include <stdio.h>
	#include <stdlib.h>
	int commentlines = 0;
	int num_lines = 0;
%}

/* Define regular expression label */

letter [a-zA-Z]
digit [0-9]
id {letter}+({letter}|{digit})*
int_number {digit}+
float_number {digit}*[.]{digit}+
white_space [ \t]
cpp_comment [/][/].*

/* Rules section */
%x IN_COMMENT STR_CONST
%%

"/*"       { commentlines++;BEGIN(IN_COMMENT); ECHO;}
<IN_COMMENT>"*/"      { BEGIN(INITIAL); printf("*/ \t C Comment\n"); }
<IN_COMMENT>[^*\n]+   { ECHO; }
<IN_COMMENT>"*"       { ECHO; }
<IN_COMMENT>\n        { num_lines++; commentlines++; ECHO;}

"\"" 		{ BEGIN(STR_CONST); ECHO; printf(" \t QUOTA\n"); }
<STR_CONST>"\"" {  BEGIN(INITIAL); ECHO; printf(" \t QUOTA\n"); }
<STR_CONST>(\\.|[^"\\])* { ECHO; printf(" \t STR_CONST\n"); }


{cpp_comment} { commentlines++; printf("%s \t C++ Comment\n", yytext); }

"int"	{ printf("%s \t INT\n", yytext); }
"float"	{ printf("%s \t FLOAT\n", yytext); }
"bool"	{ printf("%s \t BOOL\n", yytext); }
"string" 	{ printf("%s \t STRING\n", yytext); }
"void"	{ printf("%s \t VOID\n", yytext); }
"print" { printf("%s \t PRINT\n", yytext); }
"if"	{ printf("%s \t IF\n", yytext); }
"else"	{ printf("%s \t ELSE\n", yytext); }
"for"	{ printf("%s \t FOR\n", yytext); }
"while"	{ printf("%s \t WHILE\n", yytext); }
"true"	{ printf("%s \t TRUE\n", yytext); }
"false"	{ printf("%s \t FALSE\n", yytext); }
"return"	{ printf("%s \t RET\n", yytext); }
"continue"	{ printf("%s \t CONT\n", yytext); }
"break"	{ printf("%s \t BREAK\n", yytext); }

"+" 	{ printf("%s \t ADD\n", yytext); }
"-"		{ printf("%s \t SUB\n", yytext); }
"*"		{ printf("%s \t MUL\n", yytext); }
"/"		{ printf("%s \t DIV\n", yytext); }
"%"		{ printf("%s \t MOD\n", yytext); }
"++"		{ printf("%s \t INC\n", yytext); }
"--"		{ printf("%s \t DEC\n", yytext); }
">"		{ printf("%s \t MT\n", yytext); }
"<"		{ printf("%s \t LT\n", yytext); }
">="		{ printf("%s \t MTE\n", yytext); }
"<="		{ printf("%s \t LTE\n", yytext); }
"=="		{ printf("%s \t EQ\n", yytext); }
"!="		{ printf("%s \t NE\n", yytext); }

"=" 	{ printf("%s \t ASGN\n", yytext); }
"+="		{ printf("%s \t ADDASGN\n", yytext); }
"-="		{ printf("%s \t SUBASGN\n", yytext); }
"*="		{ printf("%s \t MULASGN\n", yytext); }
"/="		{ printf("%s \t DIVASGN\n", yytext); }
"%="		{ printf("%s \t MODASGN\n", yytext); }
"&&"		{ printf("%s \t AND\n", yytext); }
"||"		{ printf("%s \t OR\n", yytext); }
"!"		{ printf("%s \t NOT\n", yytext); }
"("		{ printf("%s \t LB\n", yytext); }
")"		{ printf("%s \t RB\n", yytext); }
"{"		{ printf("%s \t LCB\n", yytext); }
"}"		{ printf("%s \t RCB\n", yytext); }

"["		{ printf("%s \t LSB\n", yytext); }
"]"		{ printf("%s \t RSB\n", yytext); }
","		{ printf("%s \t COMMA\n", yytext); }
";"		{ printf("%s \t SEMICOLON\n", yytext); }


{white_space}		{;}
{int_number} 	{ printf("%s \t I_CONST\n", yytext); }
{float_number} 	{ printf("%s \t F_CONST\n", yytext); }
{id}	{ printf("%s \t ID\n", yytext); }

\n 	{ ++num_lines;}

%%

/*	C Code section */
int yywrap(void)
{
    return 1;
}

int main(int argc,char *argv[])
{
	yyin = fopen(argv[1],"r");
	yylex();
	printf("\nParse over, the line number is %d.\n\n", num_lines);
	printf("comment: %d lines\n\n", commentlines);

	return 0;
}
