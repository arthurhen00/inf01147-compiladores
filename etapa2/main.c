// Etapa 2
// Arthur Hendges da Silva - 00332968
// 2024/01

#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"

int getLineNumber(void);
int isRunning(void);
void initMe(void);

extern hash_t *hashTable[HASH_SIZE];

extern char *yytext;
extern FILE *yyin;
extern int yyparse();

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: ./etapa2 path/file_name\n");
        exit(1);
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "\"%s\" could not be accessed\n", argv[1]);
        exit(2);
    }

    initMe();

    yyparse();
    
    fprintf(stderr, "- Linhas totais: %d\n", getLineNumber());
    hashPrint(hashTable);
    exit(0);
}