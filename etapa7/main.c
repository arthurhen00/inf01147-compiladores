// Compiladores - Etapa 7 - Marcelo Johann - 2024/01
// Arthur Hendges da Silva - 00332968
// 

#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"
#include "semantic.h"

extern int getLineNumber(void);
extern int isRunning(void);
extern void initMe(void);

extern hash_t *hashTable[HASH_SIZE];

extern char *yytext;
extern FILE *yyin;
extern int yyparse();

char **global_argv;

extern int getSyntaxErrors();

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: ./etapa7 input.txt\n");
        exit(1);
    }

    global_argv = argv;

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "\"%s\" could not be accessed\n", argv[1]);
        exit(2);
    }

    initMe();

    yyparse();

    if (getSyntaxErrors()) {
        fprintf(stderr, "Syntax Errors: %d\n", getSyntaxErrors());
        exit(3);
    }

    if (getSemanticErrors()) {
        fprintf(stderr, "Semantic Errors: %d\n", getSemanticErrors());
        exit(4);
    }
    
    fprintf(stderr, "\nLinhas totais: %d\n", getLineNumber());
    hashPrint(hashTable);
    exit(0);
}