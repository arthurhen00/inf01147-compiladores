// Compiladores - Etapa 6 - Marcelo Johann - 2024/01
// Arthur Hendges da Silva - 00332968
// 

#ifndef TAC_HEADER
#define TAC_HEADER

#include "hash_table.h"
#include "ast.h"

#define TAC_SYMBOL     1
#define TAC_ADD        2
#define TAC_SUB        3
#define TAC_MUL        4
#define TAC_DIV        5
#define TAC_GT         6
#define TAC_LT         7
#define TAC_GE         8
#define TAC_LE         9
#define TAC_EQ         10
#define TAC_DIF        11
#define TAC_AND        12
#define TAC_OR         13
#define TAC_NOT        14
#define TAC_ASSIGN     15
#define TAC_VEC_ASSIGN 16
#define TAC_JF         17 // JMP FALSE
#define TAC_J          18 // JMP TRUE
#define TAC_LABEL      19
#define TAC_BEGINFUNC  20
#define TAC_ENDFUNC    21
#define TAC_ARG        22
#define TAC_RETURN     23
#define TAC_CALL       24
#define TAC_PRINT      25
#define TAC_READ       26
#define TAC_PARAM      27
#define TAC_VEC_READ   28

extern const char *tacNames[];
extern const int ASTTOTAC[];

typedef struct tacNode {
    int type;
    hash_t *op0;
    hash_t *op1;
    hash_t *op2;
    struct tacNode *prev;
    struct tacNode *next;
} tac_t;

tac_t *tacCreate(int type, hash_t *res, hash_t *op1, hash_t *op2);
tac_t *generateCode(ast_t *astNode);
tac_t *tacJoin(tac_t *tac1, tac_t *tac2);
tac_t *tacReverse(tac_t *node);

void tacPrint(tac_t *tacNode);
void tacPrintBackward(tac_t *tacNode);

#endif // TAC_HEADER