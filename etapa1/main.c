#include <stdio.h>

#include "tokens.h"
#include "hash_table.h"

int getLineNumber(void);
int isRunning(void);
void initMe(void);

extern char *yytext;
extern FILE *yyin;
extern hash_t *hashTable[HASH_SIZE];

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "usage: ./etapa1 path/file_name\n");
        exit(1);
    }

    yyin = fopen(argv[1], "r");

    int token;
    initMe();

    while (isRunning()) {
        token = yylex();

        if (isRunning() == 0) {
            break;
        }
        
        switch (token) {
            case KW_CHAR:
                fprintf(stderr, "KW_CHAR\n");
                break;
            case KW_INT:
                fprintf(stderr, "KW_INT\n");
                break;
            case KW_FLOAT:
                fprintf(stderr, "KW_FLOAT\n");
                break;
            case KW_BOOL:
                fprintf(stderr, "KW_BOOL\n");
                break;
            case KW_IF:
                fprintf(stderr, "KW_IF\n");
                break;
            case KW_ELSE:
                fprintf(stderr, "KW_ELSE\n");
                break;
            case KW_WHILE:
                fprintf(stderr, "KW_WHILE\n");
                break;
            case KW_READ:
                fprintf(stderr, "KW_READ\n");
                break;
            case KW_PRINT:
                fprintf(stderr, "KW_PRINT\n");
                break;
            case KW_RETURN:
                fprintf(stderr, "KW_RETURN\n");
                break;
            case OPERATOR_LE:
                fprintf(stderr, "OPERATOR_LE\n");
                break;
            case OPERATOR_GE:
                fprintf(stderr, "OPERATOR_GE\n");
                break;
            case OPERATOR_EQ:
                fprintf(stderr, "OPERATOR_EQ\n");
                break;
            case OPERATOR_DIF:
                fprintf(stderr, "OPERATOR_DIF\n");
                break;
            case TK_IDENTIFIER:
                fprintf(stderr, "TK_IDENTIFIER\n");
                break;
            case LIT_INT:
                fprintf(stderr, "LIT_INT\n");
                break;
            case LIT_CHAR:
                fprintf(stderr, "LIT_CHAR\n");
                break;
            case LIT_REAL:
                fprintf(stderr, "LIT_REAL\n");
                break;
            case LIT_FALSE:
                fprintf(stderr, "LIT_FALSE\n");
                break;
            case LIT_TRUE:
                fprintf(stderr, "LIT_TRUE\n");
                break;
            case LIT_STRING:
                fprintf(stderr, "LIT_STRING\n");
                break;
            case TOKEN_ERROR:
                fprintf(stderr, "TOKEN_ERROR\n");
                break;
            default:
                fprintf(stderr, "TOK %d\n", token);
                break;
        }
    }
    fprintf(stderr, "- Linhas totais: %d\n", getLineNumber());
    hashPrint(hashTable);
}