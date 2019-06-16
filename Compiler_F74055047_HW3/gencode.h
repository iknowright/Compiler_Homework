#ifndef GENCODE_H
#define GENCODE_H

#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE * file;

void genVarDeclr(char * id, int type);
void genVarDeclrVal(char * id, int type, char * text);
void genPrintConst(char * value);


#endif