#include "semantic.h"

int semanticErrors = 0;

void checkAndSetDeclarations(ast_t *astNode) {
    if(astNode == NULL) {
        return;
    }

    switch (astNode->type) {
        case AST_VAR_DEC: 
            if (astNode->symbol->type != SYMBOL_IDENTIFIER) {
                semanticErrors++;
                fprintf(stderr, "Semantic ERROR: Variable '%s' already declared.\n", astNode->symbol->str);
            }
            astNode->symbol->type = SYMBOL_VAR;
            astNode->symbol->datatype = inferDataType2(astNode);
            break;
        case AST_VEC_DEC:
            if (astNode->children[1]->symbol->type != SYMBOL_IDENTIFIER) {
                semanticErrors++;
                fprintf(stderr, "Semantic ERROR: Vector '%s' already declared.\n", astNode->children[1]->symbol->str);
            }
            astNode->children[1]->symbol->type = SYMBOL_VEC;
            astNode->children[1]->symbol->datatype = inferDataType2(astNode);
            break;
        case AST_FUNC_DEC:
            if (astNode->symbol->type != SYMBOL_IDENTIFIER) {
                semanticErrors++;
                fprintf(stderr, "Semantic ERROR: Function '%s' already declared.\n", astNode->symbol->str);
            }
            astNode->symbol->type = SYMBOL_FUNC;
            astNode->symbol->datatype = inferDataType2(astNode);
            break;
        // They are not declarations, but they need a datatype.
        case AST_SYMBOL:
            if (!astNode->symbol->datatype) {
                astNode->symbol->datatype = inferDataTypeFromType(astNode->symbol->type);
            }
            break;
    }

    for (int i = 0; i < MAX_CHILDREN; i++) {
        checkAndSetDeclarations(astNode->children[i]);
    }
}

int inferDataType(ast_t *astNode) {
    if (astNode->children[0]->type == AST_INT) {
        return DATATYPE_INT;
    } else if (astNode->children[0]->type == AST_FLOAT) {
        return DATATYPE_FLOAT;
    } else if (astNode->children[0]->type == AST_CHAR) {
        return DATATYPE_CHAR;
    } else {
        return DATATYPE_BOOL;
    }
}

int inferDataType2(ast_t *astNode) {
    return nodesDataType[astNode->children[0]->type];
}

int inferDataTypeFromType(int type) {
    return nodesDataType[type];
}

int checkUndeclared(hash_t *hashNode[]) {
    hash_t *node;
    for (int i = 0; i < HASH_SIZE; i++) {
        for (node = hashNode[i]; node; node = node->next) {
            if (node->type == SYMBOL_IDENTIFIER) {
                fprintf(stderr, "Semantic ERROR: Identifier '%s' undeclared.\n", node->str);
                semanticErrors++;
            }
        }
    }

    return semanticErrors;
}

void checkOperands(ast_t *astNode) {
    if(astNode == NULL) {
        return;
    }

    switch (astNode->type) {
        case AST_ADD:
        case AST_SUB:
        case AST_MUL:
        case AST_DIV:
            if (!isReal(astNode)) {
                if (!isNumeric(astNode)) {
                    fprintf(stderr, "1Semantic ERROR: invalid type for Arithmetic operator.\n");
                    semanticErrors++;
                } 
            }
            break;
        case AST_GT:
        case AST_LT:
        case AST_GE:
        case AST_LE:
            if (!isReal(astNode->children[0]) || !isReal(astNode->children[1])) {
                if (!isNumeric(astNode->children[0]) || !isNumeric(astNode->children[1])) {
                    fprintf(stderr, "2Semantic ERROR: invalid type for operator.\n");
                    semanticErrors++;    
                }
            }
            break;
        case AST_EQ:
        case AST_DIF:
            if (!isReal(astNode->children[0]) || !isReal(astNode->children[1])) {
                if (!isNumeric(astNode->children[0]) || !isNumeric(astNode->children[1])) {
                    if (!isBoolean(astNode->children[0]) || !isBoolean(astNode->children[1])) {
                        fprintf(stderr, "3Semantic ERROR: invalid type for operator.\n");
                        semanticErrors++;    
                    }
                }
            }
            break;
        case AST_AND:
        case AST_OR:
        case AST_NOT:
            if (!isBoolean(astNode->children[0]) || !isBoolean(astNode->children[1])) {
                fprintf(stderr, "4Semantic ERROR: invalid type for operator.\n");
                semanticErrors++;    
            }
            break;
    }

    for (int i = 0; i < MAX_CHILDREN; i++) {
        checkOperands(astNode->children[i]);
    }
    
}

// INT and CHAR are valid as numeric
int isNumeric(ast_t *astNode) {
    if (isArithOp(astNode)
        && isNumeric(astNode->children[0]) 
        && isNumeric(astNode->children[1])) {
        return 1;
    }

    if (astNode->type == AST_SYMBOL
        || astNode->type == AST_VEC
        || astNode->type == AST_FUNC) {
        if (astNode->symbol->datatype == DATATYPE_INT || astNode->symbol->datatype == DATATYPE_CHAR) {
            return 1;
        }
    }

    return 0;
}

// FLOAT is valid as real
int isReal(ast_t *astNode) {
    if (isArithOp(astNode)  
        && isReal(astNode->children[0]) 
        && isReal(astNode->children[1])) {
        return 1;
    }

    if (astNode->type == AST_SYMBOL
        || astNode->type == AST_VEC
        || astNode->type == AST_FUNC) {
        if (astNode->symbol->datatype == DATATYPE_FLOAT) {
            return 1;
        }
    }

    return 0;
}

// TRUE and FALSE are valid as boolean
int isBoolean(ast_t *astNode) {
    if (isRelationalOp(astNode)  
        && ((isNumeric(astNode->children[0]) && isNumeric(astNode->children[1]))
            || (isReal(astNode->children[0]) && isReal(astNode->children[1])))) {
        return 1;
    }

    if (isLogicalOp(astNode)
        && isBoolean(astNode->children[0]) && isBoolean(astNode->children[1])) {
        return 1;
    }

    if (isEqualityOp(astNode)
        && ((isNumeric(astNode->children[0]) && isNumeric(astNode->children[1]))
            || (isReal(astNode->children[0]) && isReal(astNode->children[1]))
            || (isBoolean(astNode->children[0]) && isBoolean(astNode->children[1])))) {
        return 1;
    }

    if (astNode->type == AST_SYMBOL
        || astNode->type == AST_VEC
        || astNode->type == AST_FUNC) {
        if (astNode->symbol->datatype == DATATYPE_BOOL) {
            return 1;
        }
    }
    return 0;
}

int isArithOp(ast_t *astNode) {
    if(astNode->type) {
        if (astNode->type == AST_ADD
            || astNode->type == AST_SUB
            || astNode->type == AST_MUL
            || astNode->type == AST_DIV) {
            return 1;
        }
    }
    return 0;
}

int isEqualityOp(ast_t *astNode) {
    if(astNode->type) {
        if (astNode->type == AST_EQ
            || astNode->type == AST_DIF) {
            return 1;
        }
    }
    return 0;
}

int isLogicalOp(ast_t *astNode) {
    if (astNode->type) {
        if (astNode->type == AST_AND
            || astNode->type == AST_OR
            || astNode->type == AST_NOT) {
            return 1;
        }
    }
    return 0;
}

int isRelationalOp(ast_t *astNode) {
    if (astNode->type) {
        if (astNode->type == AST_GT
            || astNode->type == AST_LT
            || astNode->type == AST_GE
            || astNode->type == AST_LE) {
            return 1;
        }
    }
    return 0;
}

// only count error for declared identifiers.
void checkIdentifiers(ast_t *astNode) {
    if (astNode == NULL) {
        return;
    }

    switch (astNode->type) {
        case AST_ASSIGN:
            if (astNode->symbol->type != SYMBOL_VAR 
                && astNode->symbol->type != SYMBOL_IDENTIFIER) {
                fprintf(stderr, "1Semantic ERROR: Incorrect usage of identifier. '%s' is a vector.\n", astNode->symbol->str);
                semanticErrors++;
            }
            break;
        case AST_FUNC:
            if (astNode->symbol->type != SYMBOL_FUNC 
                && astNode->symbol->type != SYMBOL_IDENTIFIER) {
                fprintf(stderr, "3Semantic ERROR: Incorrect usage of identifier. '%s' is not a function.\n", astNode->symbol->str);
                semanticErrors++;
            }
            break;
        case AST_SYMBOL:
            if (!isLiteral(astNode) 
                && astNode->symbol->type != SYMBOL_IDENTIFIER) {
                fprintf(stderr, "4Semantic ERROR: Incorrect usage of identifier. '%s' is a vector.\n", astNode->symbol->str);
                semanticErrors++;
            }
            if (astNode->symbol->type == SYMBOL_FUNC) {
                fprintf(stderr, "4.1Semantic ERROR: Incorrect usage of identifier. '%s' is a function.\n", astNode->symbol->str);
                semanticErrors++;
            }
            break;
        case AST_VEC:
            if (astNode->symbol->type != SYMBOL_VEC 
                && astNode->symbol->type != SYMBOL_IDENTIFIER) {
                fprintf(stderr, "5Semantic ERROR: Incorrect usage of identifier. '%s' is not a vector.\n", astNode->symbol->str);
                semanticErrors++;
            }
            break;
        default:
            break;
    }

    for (int i = 0; i < MAX_CHILDREN; i++) {
        checkIdentifiers(astNode->children[i]);
    }
}

int isLiteral(ast_t *astNode) { // maybe wrong HERE
    if (astNode->symbol->type == SYMBOL_VAR 
        || astNode->symbol->type == SYMBOL_LIT_INT 
        || astNode->symbol->type == SYMBOL_LIT_CHAR 
        || astNode->symbol->type == SYMBOL_LIT_REAL 
        || astNode->symbol->type == SYMBOL_LIT_FALSE 
        || astNode->symbol->type == SYMBOL_LIT_TRUE 
        || astNode->symbol->type == SYMBOL_FUNC) {
        return 1;
    }
    return 0;
}

void checkAssign(ast_t *astNode) {
    if(astNode == NULL) {
        return;
    }

    switch (astNode->type) {
        case AST_ASSIGN:
            if (astNode->symbol->datatype != getExpressionDataType(astNode->children[0])) {
                if (isNumeric(astNode) && !isNumeric(astNode->children[0])) {    
                    fprintf(stderr, "1Semantic ERROR: incompatible assign types.\n");
                    semanticErrors++;
                }
            }
            break;
        case AST_VEC_ASSIGN:
            if (astNode->children[0]->symbol->datatype != getExpressionDataType(astNode->children[1])) {
                if ((isNumeric(astNode->children[0])) && !isNumeric(astNode->children[1])) {    
                    fprintf(stderr, "2Semantic ERROR: incompatible assign types.\n");
                    semanticErrors++;
                }
            }
            break;
    }

    for (int i = 0; i < MAX_CHILDREN; i++) {
        checkAssign(astNode->children[i]);
    }
    
}

// Returns 0 when expression doesnt have a datatype
// Doesnt reconize Numeric expressions (INT whitch CHAR)
int getExpressionDataType(ast_t *astNode) {
    if(astNode == NULL) {
        return 0;
    }

    int leftDataType = 0;
    int rightDataType = 0;
    
    if (astNode->type == AST_ADD 
        || astNode->type == AST_SUB
        || astNode->type == AST_MUL
        || astNode->type == AST_DIV) {
        leftDataType = getExpressionDataType(astNode->children[0]);
        rightDataType = getExpressionDataType(astNode->children[1]);
    }
    
    if (astNode->type == AST_SYMBOL
        || astNode->type == AST_VEC
        || astNode->type == AST_FUNC) {
        return astNode->symbol->datatype;
    }

    // remove?
    if (rightDataType == 0) {
        rightDataType = leftDataType;
    }

    if (leftDataType != rightDataType) {
        return 0;
    }

    return leftDataType;
}

int getSemanticErrors() {
    return semanticErrors;
}

void checkSemantic(ast_t *astNode, hash_t *hashNode[]) {
    checkAndSetDeclarations(astNode);
    checkUndeclared(hashNode);
    checkOperands(astNode);
    checkIdentifiers(astNode);
    checkAssign(astNode);
}