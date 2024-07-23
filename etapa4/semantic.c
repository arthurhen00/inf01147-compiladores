#include "semantic.h"
#include "stdlib.h"

int semanticErrors = 0;

void checkAndSetDeclarations(ast_t *astNode) {
    if(astNode == NULL) {
        return;
    }

    switch (astNode->type) {
        case AST_VAR_DEC:
        case AST_ARG:
            if (astNode->symbol->type != SYMBOL_IDENTIFIER) {
                semanticErrors++;
                fprintf(stderr, "Semantic ERROR: Variable '%s' already declared.\n", astNode->symbol->str);
            }
            astNode->symbol->type = SYMBOL_VAR;
            astNode->symbol->datatype = inferDataType2(astNode); break; case AST_VEC_DEC:
            if (astNode->children[1]->symbol->type != SYMBOL_IDENTIFIER) {
                semanticErrors++;
                fprintf(stderr, "Semantic ERROR: Vector '%s' already declared.\n", astNode->children[1]->symbol->str);
            }
            astNode->children[1]->symbol->type = SYMBOL_VEC;
            astNode->children[1]->symbol->datatype = inferDataType2(astNode);
            // Hash points to AST
            astNode->children[1]->symbol->ast = astNode;
            break;
        case AST_FUNC_DEC:
            if (astNode->symbol->type != SYMBOL_IDENTIFIER) {
                semanticErrors++;
                fprintf(stderr, "Semantic ERROR: Function '%s' already declared.\n", astNode->symbol->str);
            }
            astNode->symbol->type = SYMBOL_FUNC;
            astNode->symbol->datatype = inferDataType2(astNode);
            // Hash points to AST
            astNode->symbol->ast = astNode;
            break;
        // They are not declarations, but they need a datatype.
        case AST_SYMBOL:
        case AST_LIT_LIST:
            if (!astNode->symbol->datatype) {
                astNode->symbol->datatype = inferDataTypeFromType(astNode->symbol->type);
            }
            if (astNode->type == AST_LIT_LIST)
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
                    fprintf(stderr, "1Semantic ERROR: invalid type for Arithmetic operator.");
                    fprintf(stderr, " (");
                    astPrintExpression(astNode);
                    fprintf(stderr, ")\n");
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
        case AST_PRINT:
            if (astNode->children[1]) {
                if (nodesDataType[astNode->children[0]->type] == DATATYPE_INT 
                    || nodesDataType[astNode->children[0]->type] == DATATYPE_CHAR) {
                    if (!isNumeric(astNode->children[1])) {
                        fprintf(stderr, "5.1Semantic ERROR: expected numeric type in print.\n");
                        semanticErrors++;
                    }
                } else if (nodesDataType[astNode->children[0]->type] == DATATYPE_FLOAT) {
                    if (!isReal(astNode->children[1])) {
                        fprintf(stderr, "5.2Semantic ERROR: expected real type in print.\n");
                        semanticErrors++;
                    }
                } else if (nodesDataType[astNode->children[0]->type] == DATATYPE_BOOL) {
                    if (!isBoolean(astNode->children[1])) {
                        fprintf(stderr, "5.3Semantic ERROR: expected boolean type in print.\n");
                        semanticErrors++;
                    }
                }
            } else {
                if (astNode->symbol->type != SYMBOL_LIT_STRING) {
                    fprintf(stderr, "6Semantic ERROR: must be a string.\n");
                    semanticErrors++;
                }
            }
            break;
        case AST_READ:
            if (nodesDataType[astNode->children[0]->type] == DATATYPE_INT
                || nodesDataType[astNode->children[0]->type] == DATATYPE_CHAR) {
                if (!isNumeric(astNode)) {
                    fprintf(stderr, "7.1Semantic ERROR: expected numeric type in read.\n");
                    semanticErrors++;
                }
            } else if (nodesDataType[astNode->children[0]->type] == DATATYPE_FLOAT) {
                if (!isReal(astNode)) {
                    fprintf(stderr, "7.2Semantic ERROR: expected real type in read.\n");
                    semanticErrors++;
                }
            } else if (nodesDataType[astNode->children[0]->type] == DATATYPE_BOOL) {
                if (!isBoolean(astNode)) {
                    fprintf(stderr, "7.3Semantic ERROR: expected boolean type in read.\n");
                    semanticErrors++;
                }
            }
            break;
        case AST_FUNC_DEC:
            if (astNode->children[1]->type == AST_BLOCK) {
                checkFunctionReturnType(astNode->children[1], nodesDataType[astNode->children[0]->type]);
            } else {
                checkFunctionReturnType(astNode->children[2], nodesDataType[astNode->children[0]->type]);
            }
            break;
        case AST_FUNC:
            if (astNode->symbol->type == SYMBOL_FUNC) {
                int argsDecSize = 0;
                int argsCallSize = 0;
                if (astNode->children[0]) {
                    argsCallSize = getCArgsListSize(astNode->children[0]);
                }
                if (astNode->symbol->ast->children[1]->type == AST_ARG_LIST) {
                    argsDecSize = getCArgsListSize(astNode->symbol->ast->children[1]);
                }
                if (argsCallSize != argsDecSize) {
                    fprintf(stderr, "Semantic ERROR: expected '%d' arguments but received '%d'.\n", argsDecSize, argsCallSize);
                    semanticErrors++;
                } else {
                    // Check if types are equal
                    ast_t *nodeAux = astNode->symbol->ast->children[1]; // AST_ARG_LIST
                    ast_t *nodeAux2 = astNode->children[0]; // AST_CARG_LIST
                    for (int i = 0; i < argsCallSize; i++) {
                        if (isNumeric(nodeAux->children[0])) {
                            if (!isNumeric(nodeAux2->children[0])) {
                                fprintf(stderr, "Semantic ERROR: %d° arg in function '%s' must be a numeric type.\n", i + 1, astNode->symbol->str);
                                semanticErrors++;
                            }
                        }
                        if (isReal(nodeAux->children[0])) {
                            if (!isReal(nodeAux2->children[0])) {
                                fprintf(stderr, "Semantic ERROR: %d° arg in function '%s' must be a real type.\n", i + 1, astNode->symbol->str);
                                semanticErrors++;
                            }
                        }
                        if (isBoolean(nodeAux->children[0])) {
                            if (!isBoolean(nodeAux2->children[0])) {
                                fprintf(stderr, "Semantic ERROR: %d° arg in function '%s' must be a boolean type.\n", i + 1, astNode->symbol->str);
                                semanticErrors++;
                            }
                        }

                        if (nodeAux->children[1]) {
                            nodeAux = nodeAux->children[1];
                        }
                        if (nodeAux2->children[1]) {
                            nodeAux2 = nodeAux2->children[1];
                        }
                    }
                }
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
    
    if (astNode->type == AST_OPEN_BR
        && isNumeric(astNode->children[0])) {
    	return 1;
    }

    if (astNode->type == AST_LIT_LIST 
        && isNumeric(astNode->children[0])
        && (astNode->symbol->datatype == DATATYPE_INT || astNode->symbol->datatype == DATATYPE_CHAR)) {
        return 1;
    }

    if (astNode->type == AST_SYMBOL
        || astNode->type == AST_VEC
        || astNode->type == AST_FUNC
        || astNode->type == AST_ASSIGN
        || astNode->type == AST_VAR_DEC
        || astNode->type == AST_READ
        || astNode->type == AST_ARG) {
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
    
    if (astNode->type == AST_OPEN_BR
        && isReal(astNode->children[0])) {
    	return 1;
    }

    if (astNode->type == AST_LIT_LIST 
        && isReal(astNode->children[0])
        && astNode->symbol->datatype == DATATYPE_FLOAT) {
        return 1;
    }

    if (astNode->type == AST_SYMBOL
        || astNode->type == AST_VEC
        || astNode->type == AST_FUNC
        || astNode->type == AST_ASSIGN
        || astNode->type == AST_VAR_DEC
        || astNode->type == AST_READ
        || astNode->type == AST_ARG) {
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
    
    if (astNode->type == AST_OPEN_BR
        && isBoolean(astNode->children[0])) {
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

    if (astNode->type == AST_LIT_LIST 
        && isBoolean(astNode->children[0])
        && astNode->symbol->datatype == DATATYPE_BOOL) {
        return 1;
    }

    if (astNode->type == AST_SYMBOL
        || astNode->type == AST_VEC
        || astNode->type == AST_FUNC
        || astNode->type == AST_ASSIGN
        || astNode->type == AST_VAR_DEC
        || astNode->type == AST_READ
        || astNode->type == AST_ARG) {
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
        case AST_READ: // HERE maybe remove
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
            if (!(isBoolean(astNode) && isBoolean(astNode->children[0]))) {   
                if (!(isNumeric(astNode) && isNumeric(astNode->children[0]))) {    
                    if (!(isReal(astNode) && isReal(astNode->children[0]))) {
                        fprintf(stderr, "1Semantic ERROR: incompatible assign types.\n");
                        semanticErrors++;
                    }
                }   
            }
            break;
        case AST_VEC_ASSIGN:
            if (!(isBoolean(astNode->children[0]) && isBoolean(astNode->children[1]))) {
                if (!(isNumeric(astNode->children[0]) && isNumeric(astNode->children[1]))) {    
                    if (!(isReal(astNode->children[0]) && isReal(astNode->children[1]))) {    
                        fprintf(stderr, "2Semantic ERROR: incompatible assign types.\n");
                        semanticErrors++;
                    }
                }
            }
            break;
        // Declarations assign
        case AST_VAR_DEC:
            if (!(isBoolean(astNode) && isBoolean(astNode->children[1]))) {
                if (!(isNumeric(astNode) && isNumeric(astNode->children[1]))) {
                    if (!(isReal(astNode) && isReal(astNode->children[1]))) {
                        fprintf(stderr, "3Semantic ERROR: incompatible type in declaration.\n");
                        semanticErrors++;
                    }
                }
            }
            break;
        case AST_VEC_DEC:
            if (astNode->children[2]) { // with list
                if (nodesDataType[astNode->children[0]->type] == DATATYPE_BOOL) {
                    if (!isBoolean(astNode->children[2])) {
                        fprintf(stderr, "4.1Semantic ERROR: incompatible type in declaration.\n");
                        semanticErrors++;
                    }
                } else if (nodesDataType[astNode->children[0]->type] == DATATYPE_FLOAT) {
                    if (!isReal(astNode->children[2])) {
                        fprintf(stderr, "4.2Semantic ERROR: incompatible type in declaration.\n");
                        semanticErrors++;
                    }
                } if (nodesDataType[astNode->children[0]->type] == DATATYPE_INT
                        || nodesDataType[astNode->children[0]->type] == DATATYPE_CHAR) {
                    if (!isNumeric(astNode->children[2])) {
                        fprintf(stderr, "4.3Semantic ERROR: incompatible type in declaration.\n");
                        semanticErrors++;
                    }
                }

                if (atoi(astNode->children[1]->children[0]->symbol->str) != getLitListSize(astNode->children[2])) {
                    fprintf(stderr, "5Semantic ERROR: incorrect use of vector size.\n");
                    semanticErrors++;
                }
            }
            break;
    }

    for (int i = 0; i < MAX_CHILDREN; i++) {
        checkAssign(astNode->children[i]);
    }
    
}

void checkVector(ast_t *astNode) {
    if (astNode == NULL) {
        return;
    }

    switch (astNode->type) {
        case AST_VEC:
            if (astNode->symbol->type == SYMBOL_VEC) {
                if (!isNumeric(astNode->children[0])) {
                    fprintf(stderr, "Semantic ERROR: invalid type for array index.\n");
                    semanticErrors++;
                }
                if (astNode->children[0]->type != AST_SYMBOL) {
                    // somar expr se for int char
                    if (!isNumeric(astNode->children[0])) {
                        fprintf(stderr, "Semantic ERROR: invalid type for array index.\n");
                        semanticErrors++;
                    } else {
                        // soma
                        fprintf(stderr, "Soma: %d\n", getExprRes(astNode->children[0]));
                        if (( getExprRes(astNode->children[0])  
                            > atoi(astNode->symbol->ast->children[1]->children[0]->symbol->str) - 1)
                                && astNode->symbol->ast->children[1] != astNode) { // O filho do meu pai nao deve ser eu
                            fprintf(stderr, "Semantic ERROR: index out of bounds in Arith.\n");
                            semanticErrors++;
                        }
                    }
                } else {
                    if ((atoi(astNode->children[0]->symbol->str)  
                        > atoi(astNode->symbol->ast->children[1]->children[0]->symbol->str) - 1)
                            && astNode->symbol->ast->children[1] != astNode) { // O filho do meu pai nao deve ser eu
                        fprintf(stderr, "Semantic ERROR: index out of bounds.\n");
                        semanticErrors++;
                    }
                }
                break;
            }
    }

    for (int i = 0; i < MAX_CHILDREN; i++) {
        checkVector(astNode->children[i]);
    }
}

int getExprRes(ast_t *astNode) {
    if (astNode->type == AST_ADD) {
        return getExprRes(astNode->children[0]) + getExprRes(astNode->children[1]);
    }
    if (astNode->type == AST_SUB) {
        return getExprRes(astNode->children[0]) - getExprRes(astNode->children[1]);
    }
    if (astNode->type == AST_MUL) {
        return getExprRes(astNode->children[0]) * getExprRes(astNode->children[1]);
    }
    if (astNode->type == AST_DIV) {
        return getExprRes(astNode->children[0]) / getExprRes(astNode->children[1]);
    }

    if (astNode->type == AST_OPEN_BR) {
        return getExprRes(astNode->children[0]);
    }

    return atoi(astNode->symbol->str);
}
    

int getLitListSize(ast_t *astNode) {
    if (astNode->type == AST_SYMBOL) {
        return 1;
    }

    return 1 + getLitListSize(astNode->children[0]);
}

int getCArgsListSize(ast_t *astNode) {
    if (astNode->type == AST_CARGS_LIST && astNode->children[1] == NULL) {
       return 1;
    }

    if (astNode->type == AST_ARG_LIST && astNode->children[1] == NULL) {
       return 1;
    }

    return 1 + getCArgsListSize(astNode->children[1]);
}

void checkFunctionReturnType(ast_t *astNode, int type) {
    if(astNode == NULL) {
        return;
    }

    if (astNode->type == AST_RETURN) {
        if (type == DATATYPE_INT || type == DATATYPE_CHAR) {
            if (!isNumeric(astNode->children[0])) {
                fprintf(stderr, "Semantic ERROR: return must be a numeric type.\n");
                semanticErrors++;
                return;
            }
        } else if (type == DATATYPE_FLOAT) {
            if (!isReal(astNode->children[0])) {
                fprintf(stderr, "Semantic ERROR: return must be a real type.\n");
                semanticErrors++;
                return;
            }
        } else if (type == DATATYPE_BOOL) {
            if (!isBoolean(astNode->children[0])) {
                fprintf(stderr, "Semantic ERROR: return must be a boolean type.\n");
                semanticErrors++;
                return;
            }
        }
    }

    for (int i = 0; i < MAX_CHILDREN; i++) {
        checkFunctionReturnType(astNode->children[i], type);
    }
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
    checkVector(astNode);
}
