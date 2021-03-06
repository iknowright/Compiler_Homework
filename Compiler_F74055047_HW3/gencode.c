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
        case STRING:
            fprintf(file, ".field public static %s Ljava/lang/String;\n", id);
            break;
        default: break;
    }
    fclose(file);
    return;
}

void genVarDeclrVal(char * id, int type, char * value)
{
    file = fopen("compiler_hw3.j","a");
    int value_float_flag = 0;
    for(int i = 0; i < strlen(value); i++) {
        if(value[i] == '.') {
            value_float_flag = 1;
            break;
        }
    }
    switch(type) {
        case FLOAT:
            if(!value_float_flag) {
                fprintf(file, ".field public static %s F = %s.0\n", id, value);
            } else {
                fprintf(file, ".field public static %s F = %s\n", id, value);                
            }
            break;
        case INT:
            if(value_float_flag) {
                float f = atof(value);
                int i = (int)f;
                fprintf(file, ".field public static %s I = %d\n", id, i);
            } else {
                fprintf(file, ".field public static %s I = %s\n", id, value);                
            }
            break;
        case BOOL:
            fprintf(file, ".field public static %s Z = %s\n", id, value);
            break;
        case STRING:
            fprintf(file, ".field public static %s Ljava/lang/String; = %s\n", id, value);
            break;
        default: break;
    }
    fclose(file);
    return;
}

char *  genPrintConst(char * value)
{
    char buffer[1000];
    char tmp[1000];    
    char buf[100];
    strcpy(buffer, "");
    strcpy(tmp, "");
    strcpy(buf, "");

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
        sprintf(buf, "ldc %s\n", value);
        strcpy(tmp, buffer);
        sprintf(buffer, "%s%s", tmp, buf);
        sprintf(buf, "getstatic java/lang/System/out Ljava/io/PrintStream;\n"
            "swap\n"
        );
        strcpy(tmp, buffer);
        sprintf(buffer, "%s%s", tmp, buf);
        sprintf(buf, "invokevirtual java/io/PrintStream/println(I)V\n");
        strcpy(tmp, buffer);
        sprintf(buffer, "%s%s", tmp, buf);
    } else {
        printf("it is a float number %f\n", atof(value));                
        printf("%s\n", value);
        sprintf(buf, "ldc %s\n", value);
        strcpy(tmp, buffer);
        sprintf(buffer, "%s%s", tmp, buf);
        sprintf(buf, "getstatic java/lang/System/out Ljava/io/PrintStream;\n"
            "swap\n"
        );
        strcpy(tmp, buffer);
        sprintf(buffer, "%s%s", tmp, buf);
        sprintf(buf, "invokevirtual java/io/PrintStream/println(F)V\n");
        strcpy(tmp, buffer);
        sprintf(buffer, "%s%s", tmp, buf);
    }
    return strdup(buffer);
}

char * genPrintStrConst(char * value)
{
    char buffer[1000];
    char tmp[1000];    
    char buf[100];
    strcpy(buffer, "");
    strcpy(tmp, "");
    strcpy(buf, "");

    sprintf(buf, "ldc \"%s\"\n", value);
    strcpy(tmp, buffer);
    sprintf(buffer, "%s%s", tmp, buf);
    sprintf(buf, "getstatic java/lang/System/out Ljava/io/PrintStream;\n"
        "swap\n"
    );
    strcpy(tmp, buffer);
    sprintf(buffer, "%s%s", tmp, buf);
    sprintf(buf, "invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
    strcpy(tmp, buffer);
    sprintf(buffer, "%s%s", tmp, buf);
    return strdup(buffer);
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
                sprintf(buf, "aload %d\n", reg);
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
    return strdup(buffer);
}

void genFunction(char * id, char * body, int type, char * param)
{
    file = fopen("compiler_hw3.j","a");
    if(!strcmp(id, "main")) {
        fprintf(file, ".method public static main([Ljava/lang/String;)V\n.limit stack 50\n.limit locals 50\n");
        fprintf(file, "%s\n", body);
        fprintf(file, "return\n");        
        fprintf(file, ".end method\n");        
    } else {
        if(type == INT) {
            fprintf(file, ".method public static %s(%s)I\n.limit stack 50\n.limit locals 50\n", id, param);
        } else if(type == FLOAT) {
            fprintf(file, ".method public static %s(%s)F\n.limit stack 50\n.limit locals 50\n", id, param);
        } else if(type == STRING) {
            fprintf(file, ".method public static %s(%s)Ljava/lang/String;\n.limit stack 50\n.limit locals 50\n", id, param);
        } else if(type == BOOL) {
            fprintf(file, ".method public static %s(%s)Z\n.limit stack 50\n.limit locals 50\n", id, param);
        } else if(type == VOID) {
            fprintf(file, ".method public static %s(%s)V\n.limit stack 50\n.limit locals 50\n", id, param);
        }
        fprintf(file, "%s\n", body);
        if(type == INT) {
            fprintf(file, "ireturn\n"); 
        } else if(type == FLOAT) {
            fprintf(file, "freturn\n"); 
        } else if(type == STRING) {
            fprintf(file, "areturn\n"); 
        } else if(type == BOOL) {
            fprintf(file, "ireturn\n"); 
        } else if(type == VOID) {
            fprintf(file, "return\n");        
        }
        fprintf(file, ".end method\n\n\n");    
    }
    fclose(file);
}
