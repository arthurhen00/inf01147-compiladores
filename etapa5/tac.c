// Compiladores - Etapa 5 - Marcelo Johann - 2024/01
// Arthur Hendges da Silva - 00332968
// 

#include "tac.h"
#include <stdlib.h>

tac_t *tacCreate(int type, hash_t *res, hash_t *op1, hash_t *op2) {
    tac_t *newNode;
    newNode = (tac_t*)malloc(sizeof(tac_t));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }

    newNode->type = type;
    newNode->op0 = res;
    newNode->op1 = op1;
    newNode->op2 = op2;
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

tac_t *generateCode(ast_t *astNode) {
    if (astNode == NULL) {
        return NULL;
    }

    tac_t *res = NULL;
    tac_t *code[MAX_CHILDREN];

    for (int i = 0; i < MAX_CHILDREN; i++) {
        code[i] = generateCode(astNode->children[i]);
    }

    switch (astNode->type) {
        case AST_SYMBOL:
            res = tacCreate(TAC_SYMBOL, astNode->symbol, NULL, NULL);
            break;
        case AST_ADD:
        case AST_SUB:
        case AST_MUL:
        case AST_DIV:
        case AST_GT:
        case AST_LT:
        case AST_GE:
        case AST_LE:
        case AST_EQ:
        case AST_DIF:
        case AST_AND:
        case AST_OR:
        case AST_NOT:        
            res = tacJoin(tacJoin(code[0], code[1]), tacCreate(ASTTOTAC[astNode->type], makeTemp(), code[0]->op0, code[1]->op0));
            break;
        case AST_ASSIGN:
            res = tacJoin(code[0], tacCreate(TAC_ASSIGN, astNode->symbol, code[0]->op0, NULL));
            break;
        case AST_VEC_ASSIGN:
            // HERE
            res = tacJoin(code[1], tacCreate(TAC_VEC_ASSIGN, astNode->symbol, code[0]->op0, code[1]->op0));
            break;
        case AST_IF:
            if (astNode->children[2]) { // IFTHENELSE
                tac_t *jumpFTac = NULL;
                tac_t *labelFTac = NULL;

                tac_t *jumpTTac = NULL;
                tac_t *labelTTac = NULL;

                hash_t *falseLabel = makeLabel();
                hash_t *jumpLabel = makeLabel();

                jumpFTac = tacCreate(TAC_JF, falseLabel, code[0]->op0, NULL);
                res = tacJoin(code[0], jumpFTac);

                res = tacJoin(res, code[1]);
                jumpTTac = tacCreate(TAC_J, jumpLabel, NULL, NULL);
                res = tacJoin(res, jumpTTac);

                labelFTac = tacCreate(TAC_LABEL, falseLabel, NULL, NULL);
                res = tacJoin(res, labelFTac);
                res = tacJoin(res, code[2]);

                labelTTac = tacCreate(TAC_LABEL, jumpLabel, NULL, NULL);
                res = tacJoin(res, labelTTac);
            } else { // IFTHEN
                tac_t *jumpTac = NULL;
                tac_t *labelTac = NULL;
                hash_t *falseLabel = makeLabel();

                jumpTac = tacCreate(TAC_JF, falseLabel, code[0]->op0, NULL);
                jumpTac->prev = code[0];

                labelTac = tacCreate(TAC_LABEL, falseLabel, NULL, NULL);
                labelTac->prev = code[1];

                res = tacJoin(jumpTac, labelTac);
            }
            break;
        case AST_FUNC_DEC:
            if (astNode->children[2]) { // args, block in children 2
                res = tacJoin(code[1], tacCreate(TAC_BEGINFUNC, astNode->symbol, NULL, NULL)); // args after beginfunc
                //res = tacJoin(res, code[1]);
                res = tacJoin(res, code[2]);
                res = tacJoin(res, tacCreate(TAC_ENDFUNC, astNode->symbol, NULL, NULL));
            } else {
                res = tacCreate(TAC_BEGINFUNC, astNode->symbol, NULL, NULL);
                res = tacJoin(res, code[1]);
                res = tacJoin(res, tacCreate(TAC_ENDFUNC, astNode->symbol, NULL, NULL));
            }
            break;
        case AST_ARG:
            res = tacCreate(TAC_PARAM, astNode->symbol, NULL, NULL);
            break;
        case AST_ARG_LIST:
            // HERE
            if (astNode->children[1]) {
                res = tacJoin(code[0], code[1]); // ordem args
            } else {
                res = code[0];
            }
            break;
        case AST_RETURN:
            res = tacJoin(code[0], tacCreate(TAC_RETURN, code[0]->op0, NULL, NULL));
            break;
        case AST_FUNC:
            //res = tacJoin(tacCreate(TAC_CALL, makeTemp(), astNode->symbol, NULL), code[0]); // args after call
            res = tacJoin(code[0], tacCreate(TAC_CALL, makeTemp(), astNode->symbol, NULL));
            break;
        case AST_CARGS_LIST:
            res = tacJoin(tacCreate(TAC_ARG, code[0]->op0, NULL, NULL), code[1]); // ordem dos args call
            break;
        case AST_PRINT:
            if (astNode->children[1]) {
                res = tacJoin(code[1], tacCreate(TAC_PRINT, code[1]->op0, NULL, NULL));
            } else { // str
                res = tacCreate(TAC_PRINT, astNode->symbol, NULL, NULL);
            }
            break;
        case AST_READ:
            res = tacCreate(TAC_READ, astNode->symbol, NULL, NULL);
            break;
        case AST_WHILE:
            hash_t *falseLabel = makeLabel();
            hash_t *jmpLabel = makeLabel();

            res = tacJoin(tacCreate(TAC_LABEL, jmpLabel, NULL, NULL), code[0]);

            res = tacJoin(res, tacCreate(TAC_JF, falseLabel, code[0]->op0, NULL));

            res = tacJoin(res, code[1]);

            res = tacJoin(res, tacCreate(TAC_J, jmpLabel, NULL, NULL));

            res = tacJoin(res, tacCreate(TAC_LABEL, falseLabel, NULL, NULL));

            break;
        case AST_VEC:
            if (astNode->symbol->ast->children[1] != astNode) {
                res = tacCreate(TAC_VEC_READ, makeTemp(), astNode->symbol, code[0]->op0);
            }
            break;
        default:
            res = tacJoin(tacJoin(tacJoin(code[0], code[1]), code[2]), code[3]);
            break;
    }
    // func call, print, read
    return res;
}

tac_t *tacJoin(tac_t *tac1, tac_t *tac2) {
    if (tac1 == NULL) {
        return tac2;
    }

    if (tac2 == NULL) {
        return tac1;
    }

    tac_t *aux;
    for (aux = tac2; aux->prev; aux = aux->prev) {
        // reaches the end
    }
    
    aux->prev = tac1;
    return tac2;
}

void tacPrint(tac_t *tacNode) {
    if(tacNode == NULL 
        || tacNode->type == TAC_SYMBOL) {
        return;
    }

    fprintf(stderr, "TAC(%s", tacNames[tacNode->type]);

    if (tacNode->op0) {
        fprintf(stderr, ", %s", tacNode->op0->str);
    } else {
        fprintf(stderr, ", NULL");
    }

    if (tacNode->op1) {
        fprintf(stderr, ", %s", tacNode->op1->str);
    } else {
        fprintf(stderr, ", NULL");
    }

    if (tacNode->op2) {
        fprintf(stderr, ", %s", tacNode->op2->str);
    } else {
        fprintf(stderr, ", NULL");
    }
    
    fprintf(stderr, ")\n");
}

void tacPrintBackward(tac_t *tacNode) {
    /*
    tac_t *node;
    for (node = tacNode; node; node = node->prev) {
        tacPrint(node);
    }
    */
    if (tacNode == NULL) {
        return;
    }
    tacPrintBackward(tacNode->prev);
    tacPrint(tacNode);
}