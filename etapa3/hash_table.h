// Compiladores - Etapa 3 - Marcelo Johann - 2024/01
// Arthur Hendges da Silva - 00332968
// 

#ifndef HASH_TABLE_HEADER
#define HASH_TABLE_HEADER

#define HASH_SIZE 997

#define SYMBOL_CHAR
#define SYMBOL_INT
#define SYMBOL_FLOAT
#define SYMBOL_BOOL

#define SYMBOL_IF
#define SYMBOL_ELSE
#define SYMBOL_WHILE
#define SYMBOL_READ
#define SYMBOL_PRINT
#define SYMBOL_RETURN

#define SYMBOL_OPERATOR_LE
#define SYMBOL_OPERATOR_GE
#define SYMBOL_OPERATOR_EQ
#define SYMBOL_OPERATOR_DIF

#define SYMBOL_IDENTIFIER

#define SYMBOL_LIT_INT
#define SYMBOL_LIT_CHAR
#define SYMBOL_LIT_REAL
#define SYMBOL_LIT_FALSE
#define SYMBOL_LIT_TRUE
#define SYMBOL_LIT_STRING

#define SYMBOL_ERROR

typedef struct hashNode {
    char *str;
    int type;
    struct hashNode *next;
} hash_t;

void hashInit(hash_t *table[]);
int hashHorner(char *str);
hash_t *hashSearch(hash_t *table[], char *str);
hash_t *hashInsert(hash_t *table[], char *str, int type);
void hashPrint(hash_t *table[]);

#endif // HASH_TABLE_HEADER