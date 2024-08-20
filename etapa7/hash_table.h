// Compiladores - Etapa 7 - Marcelo Johann - 2024/01
// Arthur Hendges da Silva - 00332968
// 

#ifndef HASH_TABLE_HEADER
#define HASH_TABLE_HEADER

#define HASH_SIZE 997

#define SYMBOL_IDENTIFIER   1
#define SYMBOL_VAR          2
#define SYMBOL_VEC          3
#define SYMBOL_FUNC         4

#define SYMBOL_LIT_INT      5
#define SYMBOL_LIT_CHAR     6
#define SYMBOL_LIT_REAL     7
#define SYMBOL_LIT_FALSE    8
#define SYMBOL_LIT_TRUE     9
#define SYMBOL_LIT_STRING   10

#define SYMBOL_CHAR         11
#define SYMBOL_INT          12
#define SYMBOL_FLOAT        13
#define SYMBOL_BOOL         14

#define SYMBOL_IF           15
#define SYMBOL_ELSE         16
#define SYMBOL_WHILE        17
#define SYMBOL_READ         18
#define SYMBOL_PRINT        19
#define SYMBOL_RETURN       20

#define SYMBOL_OPERATOR_LE  21
#define SYMBOL_OPERATOR_GE  22
#define SYMBOL_OPERATOR_EQ  23
#define SYMBOL_OPERATOR_DIF 24

#define SYMBOL_ERROR        25

#define SYMBOL_LABEL        26
#define SYMBOL_TEMP         27
#define SYMBOL_ARG          28

#define DATATYPE_INT   1
#define DATATYPE_FLOAT 2
#define DATATYPE_CHAR  3
#define DATATYPE_BOOL  4

typedef struct hashNode {
    char *str;
    int type;
    int datatype;
    struct hashNode *next;
    struct astNode *ast;
} hash_t;

void hashInit();
int hashHorner(char *str);
hash_t *hashSearch(char *str);
hash_t *hashInsert(char *str, int type);
void hashPrint();
hash_t *makeTemp(int dataType);
hash_t *makeLabel();

#endif // HASH_TABLE_HEADER