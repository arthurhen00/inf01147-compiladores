// Compiladores - Etapa 7 - Marcelo Johann - 2024/01
// Arthur Hendges da Silva - 00332968
// 
#ifndef ASM_HEADER
#define ASM_HEADER

#include "tac.h"
#include "hash_table.h"

#define FILE_OUT "out.s"

extern const char *stringType[];
extern const char *opASM[];

void generateAsm(tac_t *node);
void printAsmFromHT(FILE *file, hash_t *table[]);

char* asciiRepresentation(const char* str);

#endif // ASM_HEADER