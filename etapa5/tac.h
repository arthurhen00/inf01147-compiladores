// Compiladores - Etapa 5 - Marcelo Johann - 2024/01
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

const static char *tacNames[] = {
    [TAC_SYMBOL] = "TAC_SYMBOL",
    [TAC_ADD] = "TAC_ADD",
    [TAC_SUB] = "TAC_SUB",
    [TAC_MUL] = "TAC_MUL",
    [TAC_DIV] = "TAC_DIV",
    [TAC_GT] = "TAC_GT",
    [TAC_LT] = "TAC_LT",
    [TAC_GE] = "TAC_GE",
    [TAC_LE] = "TAC_LE",
    [TAC_EQ] = "TAC_EQ",
    [TAC_DIF] = "TAC_DIF",
    [TAC_AND] = "TAC_AND",
    [TAC_OR] = "TAC_OR",
    [TAC_NOT] = "TAC_NOT",
    [TAC_ASSIGN] = "TAC_ASSIGN",
    [TAC_VEC_ASSIGN] = "TAC_VEC_ASSIGN",
    [TAC_JF] = "TAC_JF",
    [TAC_J] = "TAC_J",
    [TAC_LABEL] = "TAC_LABEL",
    [TAC_BEGINFUNC] = "TAC_BEGINFUNC",
    [TAC_ENDFUNC] = "TAC_ENDFUNC",
    [TAC_ARG] = "TAC_ARG",
    [TAC_RETURN] = "TAC_RETURN",
    [TAC_CALL] = "TAC_CALL",
    [TAC_PRINT] = "TAC_PRINT",
    [TAC_READ] = "TAC_READ",
    [TAC_PARAM] = "TAC_PARAM",
    [TAC_VEC_READ] = "TAC_VEC_READ",
};

const static int ASTTOTAC[] = {
    [AST_ADD] = TAC_ADD,
    [AST_SUB] = TAC_SUB,
    [AST_MUL] = TAC_MUL,
    [AST_DIV] = TAC_DIV,
    [AST_GT] = TAC_GT,
    [AST_LT] = TAC_LT,
    [AST_GE] = TAC_GE,
    [AST_LE] = TAC_LE,
    [AST_EQ] = TAC_EQ,
    [AST_DIF] = TAC_DIF,
    [AST_AND] = TAC_AND,
    [AST_OR] = TAC_OR,
    [AST_NOT] = TAC_NOT,
    [TAC_RETURN] = TAC_RETURN,
};

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

void tacPrint(tac_t *tacNode);
void tacPrintBackward(tac_t *tacNode);

#endif // TAC_HEADER