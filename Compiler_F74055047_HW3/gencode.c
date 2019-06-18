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
    char buffer[1000];
    char tmp[1000];    
    char buf[100];
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

char * genPrintID(int reg, int type, int scope, char * id) {
    char buffer[1000];
    char tmp[1000];    
    char buf[100];
    strcpy(buffer, "");
    strcpy(tmp, "");
    strcpy(buf, "");
    switch(type) {
        case STRING:
            if(!scope) {
                sprintf(buf, "getstatic compiler_hw3/%s Ljava/lang/String;\n", id);
                strcpy(tmp, buffer);
                sprintf(buffer, "%s%s", tmp, buf);               
            } else {
                sprintf(buf, "iload %d\n", reg);
                strcpy(tmp, buffer);
                sprintf(buffer, "%s%s", tmp, buf);
            }
            sprintf(buf, "getstatic java/lang/System/out Ljava/io/PrintStream;\n"
            "swap\n"
            );
            strcpy(tmp, buffer);
            sprintf(buffer, "%s%s", tmp, buf);
            sprintf(buf, "invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
            strcpy(tmp, buffer);
            sprintf(buffer, "%s%s", tmp, buf);
            break;
        case INT:
            if(!scope) {
                sprintf(buf, "getstatic compiler_hw3/%s I\n", id);                
                strcpy(tmp, buffer);
                sprintf(buffer, "%s%s", tmp, buf);
            } else {
                sprintf(buf, "iload %d\n", reg);
                strcpy(tmp, buffer);
                sprintf(buffer, "%s%s", tmp, buf);
            }
            sprintf(buf, "getstatic java/lang/System/out Ljava/io/PrintStream;\n"
                "swap\n"
            );
            strcpy(tmp, buffer);
            sprintf(buffer, "%s%s", tmp, buf);
            sprintf(buf, "invokevirtual java/io/PrintStream/println(I)V\n");
            strcpy(tmp, buffer);
            sprintf(buffer, "%s%s", tmp, buf);
            break;
        case FLOAT:
            if(!scope) {
                sprintf(buf, "getstatic compiler_hw3/%s F\n", id);
                strcpy(tmp, buffer);
                sprintf(buffer, "%s%s", tmp, buf);            
            } else {
                sprintf(buf, "fload %d\n", reg);
                strcpy(tmp, buffer);
                sprintf(buffer, "%s%s", tmp, buf);
            }
            sprintf(buf, "getstatic java/lang/System/out Ljava/io/PrintStream;\n"
                "swap\n"
            );
            strcpy(tmp, buffer);
            sprintf(buffer, "%s%s", tmp, buf);
            sprintf(buf, "invokevirtual java/io/PrintStream/println(F)V\n");
            strcpy(tmp, buffer);
            sprintf(buffer, "%s%s", tmp, buf);
            break;
        case BOOL:
            if(!scope) {
                sprintf(buf, "getstatic compiler_hw3/%s Z\n", id);                
                strcpy(tmp, buffer);
                sprintf(buffer, "%s%s", tmp, buf);
            } else {
                sprintf(buf, "iload %d\n", reg);
                strcpy(tmp, buffer);
                sprintf(buffer, "%s%s", tmp, buf);
            }
            sprintf(buf, "getstatic java/lang/System/out Ljava/io/PrintStream;\n"
                "swap\n"
            );
            strcpy(tmp, buffer);
            sprintf(buffer, "%s%s", tmp, buf);
            sprintf(buf, "invokevirtual java/io/PrintStream/println(Z)V\n");
            strcpy(tmp, buffer);
            sprintf(buffer, "%s%s", tmp, buf);
            break;
    }
    printf("%s\n", buffer);
    return strdup(buffer);
}
