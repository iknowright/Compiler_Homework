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
    int i = 0;
    int is_float = 0;
    for(i = 0; i < strlen(value); i++) {
        if(value[i] == '.') {
            is_float = 1;
            break;
        }
    }
    if(!is_float) {
        printf("it is a integer number %d\n", atoi(value));                
        fprintf(file, "ldc %s\n", value);
        fprintf(file, "getstatic java/lang/System/out Ljava/io/PrintStream;\n"
            "swap\n"
        );
        fprintf(file, "invokevirtual java/io/PrintStream/println(I)V\n");
    } else {
        printf("it is a float number %f\n", atof(value));                
        printf("%s\n", value);
        fprintf(file, "ldc %s\n", value);
        fprintf(file, "getstatic java/lang/System/out Ljava/io/PrintStream;\n"
            "swap\n"
        );
        fprintf(file, "invokevirtual java/io/PrintStream/println(F)V\n");
    }
    fclose(file);
}

void genPrintStrConst(char * value)
{
    file = fopen("compiler_hw3.j","a");             
    fprintf(file, "ldc \"%s\"\n", value);
    fprintf(file, "getstatic java/lang/System/out Ljava/io/PrintStream;\n"
        "swap\n"
    );
    fprintf(file, "invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
    fclose(file);
    return;
}

void genPrint(char * value)
{
    file = fopen("compiler_hw3.j","a");
    fprintf(file, "%s\n", value);    
    fclose(file);
}

void genPrintID(int reg, int type, int scope, char * id) {
    file = fopen("compiler_hw3.j","a");
    switch(type) {
        case STRING:
            if(!scope)
                fprintf(file, "getstatic compiler_hw3/%s Ljava/lang/String;\n", id);                
            else
                fprintf(file, "iload %d\n", reg);
            fprintf(file, "getstatic java/lang/System/out Ljava/io/PrintStream;\n"
                "swap\n"
            );
            fprintf(file, "invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
            break;
        case INT:
            if(!scope)
                fprintf(file, "getstatic compiler_hw3/%s I\n", id);                
            else
                fprintf(file, "iload %d\n", reg);
            fprintf(file, "getstatic java/lang/System/out Ljava/io/PrintStream;\n"
                "swap\n"
            );
            fprintf(file, "invokevirtual java/io/PrintStream/println(I)V\n");
            break;
        case FLOAT:
            if(!scope)
                fprintf(file, "getstatic compiler_hw3/%s F\n", id);                
            else
                fprintf(file, "fload %d\n", reg);
            fprintf(file, "getstatic java/lang/System/out Ljava/io/PrintStream;\n"
                "swap\n"
            );
            fprintf(file, "invokevirtual java/io/PrintStream/println(F)V\n");
            break;
        case BOOL:
            if(!scope)
                fprintf(file, "getstatic compiler_hw3/%s Z\n", id);                
            else
                fprintf(file, "iload %d\n", reg);
            fprintf(file, "getstatic java/lang/System/out Ljava/io/PrintStream;\n"
                "swap\n"
            );
            fprintf(file, "invokevirtual java/io/PrintStream/println(Z)V\n");
            break;
    }
    fclose(file);
}
