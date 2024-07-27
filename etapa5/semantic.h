// Compiladores - Etapa 5 - Marcelo Johann - 2024/01
// Arthur Hendges da Silva - 00332968
// 

#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include "ast.h"
#include "hash_table.h"

const static int nodesDataType[] = {
    [AST_INT] = DATATYPE_INT,
    [AST_FLOAT] = DATATYPE_FLOAT,
    [AST_CHAR] = DATATYPE_CHAR,
    [AST_BOOL] = DATATYPE_BOOL,

    [SYMBOL_LIT_INT] = DATATYPE_INT,
    [SYMBOL_LIT_REAL] = DATATYPE_FLOAT,
    [SYMBOL_LIT_CHAR] = DATATYPE_CHAR,
    [SYMBOL_LIT_TRUE] = DATATYPE_BOOL,
    [SYMBOL_LIT_FALSE] = DATATYPE_BOOL,
};
void checkSemantic(ast_t *astNode, hash_t *hashNode[]);

void checkAndSetDeclarations(ast_t *astNode);
int checkUndeclared(hash_t *hashNode[]);
void checkOperands(ast_t *astNode);
void checkIdentifiers(ast_t *astNode);
void checkAssign(ast_t *astNode);
void checkVector(ast_t *astNode);

int getLitListSize(ast_t *astNode);
int getCArgsListSize(ast_t *astNode);
int getExprRes(ast_t *astNode);
void checkFunctionReturnType(ast_t *astNode, int type);

int isNumeric(ast_t *astNode);
int isReal(ast_t *astNode);
int isBoolean(ast_t *astNode);
int isLiteral(ast_t *astNode);

int isArithOp(ast_t *astNode);
int isEqualityOp(ast_t *astNode);
int isLogicalOp(ast_t *astNode);
int isRelationalOp(ast_t *astNode);

int inferDataType(ast_t *astNode);
int inferDataType2(ast_t *astNode);
int inferDataTypeFromType(int type);

int getSemanticErrors();

#endif // SEMANTIC_HEADER