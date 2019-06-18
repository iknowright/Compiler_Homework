#ifndef GENCODE_H
#define GENCODE_H

#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE * file;

void genVarDeclr(char * id, int type);
void genVarDeclrVal(char * id, int type, char * text);
char * genPrintConst(char * value);
char * genPrintStrConst(char * value);
void genPrint(char * value);
char * genPrintID(int reg, int type, int scope, char * id);
void genFunction(char * id, char * body, int type);


#endif