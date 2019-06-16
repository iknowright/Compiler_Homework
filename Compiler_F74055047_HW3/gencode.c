#include "gencode.h"

void genVarDeclr(char * id, int type)
{
    file = fopen("compiler_hw3.j","a");
    switch(type) {
        case FLOAT:
            fprintf(file, ".field public static %s F\n", id);
            break;
        case INT:
            fprintf(file, ".field public static %s I\n", id);
            break;
        case BOOL:
            fprintf(file, ".field public static %s Z\n", id);
            break;
        default: break;
    }
    fclose(file);
    return;
}

void genVarDeclrVal(char * id, int type, char * value)
{
    file = fopen("compiler_hw3.j","a");
    switch(type) {
        case FLOAT:
            fprintf(file, ".field public static %s F = %s\n", id, value);
            break;
        case INT:
            fprintf(file, ".field public static %s I = %s\n", id, value);
            break;
        case BOOL:
            fprintf(file, ".field public static %s Z = %s\n", id, value);
            break;
        default: break;
    }
    fclose(file);
    return;
}

void genPrintConst(char * value)
{
    file = fopen("compiler_hw3.j","a");
    if(!strcmp(value, "0")) {
        fprintf(file, "ldc %s\n", value);
        fprintf(file, "getstatic java/lang/System/out Ljava/io/PrintStream;\n"
            "swap\n"
        );
        fprintf(file, "invokevirtual java/io/PrintStream/println(I)V\n");
    } else if(atof(value) != 0.0) {
        printf("%s\n", value);
        fprintf(file, "ldc %s\n", value);
        fprintf(file, "getstatic java/lang/System/out Ljava/io/PrintStream;\n"
            "swap\n"
        );
        fprintf(file, "invokevirtual java/io/PrintStream/println(F)V\n");
    } else if(atoi(value) != 0) {
        fprintf(file, "ldc %s\n", value);
        fprintf(file, "getstatic java/lang/System/out Ljava/io/PrintStream;\n"
            "swap\n"
        );
        fprintf(file, "invokevirtual java/io/PrintStream/println(I)V\n");
    }
    fclose(file);
}