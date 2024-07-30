// Compiladores - Etapa 4 - Marcelo Johann - 2024/01
// Arthur Hendges da Silva - 00332968
// 

#include <stdlib.h>

#include "ast.h"

ast_t *astCreate(int type, hash_t *symbol, ast_t *c0, ast_t *c1, ast_t *c2, ast_t *c3) {
    ast_t *newNode;
    newNode = (ast_t*)malloc(sizeof(ast_t));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }

    newNode->type = type;
    newNode->symbol = symbol;
    newNode->children[0] = c0;
    newNode->children[1] = c1;
    newNode->children[2] = c2;
    newNode->children[3] = c3;

    return newNode;
}

void astPrint(ast_t *astNode, int level) {
    if(astNode == NULL) {
        return;
    }
    
    for (int i = 0; i < level; i++) {
        fprintf(stderr, "  ");
    }

    fprintf(stderr, "(%s", AST_INFOS[astNode->type].name);

    if (astNode->symbol) {
        fprintf(stderr, ",%s)\n", astNode->symbol->str);
    } else {
        fprintf(stderr, ",NULL)\n");
    }

    for (int i = 0; i < MAX_CHILDREN; i++) {
        astPrint(astNode->children[i], level+1);
    }
}

void astOutput(ast_t *astNode) {
    FILE *arq = fopen(global_argv[2], "w");

    if (!arq) {
        fprintf(arq, "\"%s\" could not be accessed\n", global_argv[2]);
        exit(2);
    }

    astOutputRec(arq, astNode);

    fclose(arq);
}

void astOutputRec(FILE *arq, ast_t *astNode) {
    if(astNode == NULL) {
        return;
    }

    switch (astNode->type) {
        case AST_SYMBOL:
            fprintf(arq, "%s", astNode->symbol->str);
            break;
        case AST_ADD:                               // expr 'operator' expr
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
            // may not have an identifier
            if (astNode->symbol) {
                fprintf(arq, "%s", astNode->symbol->str);
            } else {
                astOutputRec(arq, astNode->children[0]);
                fprintf(arq, "%s", AST_INFOS[astNode->type].expr); 
                astOutputRec(arq, astNode->children[1]);
            }
            break;
        case AST_INT:
        case AST_FLOAT:
        case AST_CHAR:
        case AST_BOOL:
            fprintf(arq, "%s ", AST_INFOS[astNode->type].expr);
            break;
        case AST_ASSIGN:                            // identifier=
            // always has an identifier
            fprintf(arq, "%s=", astNode->symbol->str);
            astOutputRec(arq, astNode->children[0]);
            fprintf(arq, ";");
            break;
        case AST_VEC:                               // identifier[expr]
            // always has an identifier
            fprintf(arq, "%s", astNode->symbol->str);
            fprintf(arq, "[");
            astOutputRec(arq, astNode->children[0]);
            fprintf(arq, "]");
            break;
        case AST_VEC_ASSIGN:                        // AST_VEC=expr;
            // does not have an identifier
            fprintf(arq, "%s", astNode->symbol->str);
            fprintf(arq, "[");
            astOutputRec(arq, astNode->children[0]);
            fprintf(arq, "]");
            fprintf(arq, "=");
            astOutputRec(arq, astNode->children[1]);
            fprintf(arq, ";");
            break;
        case AST_PRINT:
            // may not have an identifier
            fprintf(arq, "print ");
            if (astNode->symbol) {
                fprintf(arq, "%s", astNode->symbol->str);
            } else {
                astOutputRec(arq, astNode->children[0]);
                astOutputRec(arq, astNode->children[1]);
            }
            fprintf(arq, ";");
            break;
        case AST_READ:
            // always has an identifier
            fprintf(arq, "read ");
            astOutputRec(arq, astNode->children[0]);
            fprintf(arq, "%s", astNode->symbol->str);
            fprintf(arq, ";");
            break;
        case AST_RETURN:
            fprintf(arq, "return ");
            astOutputRec(arq, astNode->children[0]);
            fprintf(arq, ";");
            break;
        case AST_IF:
            // can have 2 or 3 children
            fprintf(arq, "if(");
            astOutputRec(arq, astNode->children[0]);
            fprintf(arq, ")");
            astOutputRec(arq, astNode->children[1]);
            if (astNode->children[2]) {
                fprintf(arq, "else ");
                astOutputRec(arq, astNode->children[2]);
            }
            break;
        case AST_BLOCK:
            fprintf(arq, "{");
            if (astNode->children[0]) {
                astOutputRec(arq, astNode->children[0]);
            }
            fprintf(arq, "}");
            break;
        case AST_WHILE:
            fprintf(arq, "while(");
            astOutputRec(arq, astNode->children[0]);
            fprintf(arq, ")");
            astOutputRec(arq, astNode->children[1]);
            break;
        case AST_EMPTY_CMD:
            fprintf(arq, ";");
            break;

        case AST_DEC_LIST:
            if (astNode->children[1]) {
                astOutputRec(arq, astNode->children[0]);
                astOutputRec(arq, astNode->children[1]);
            } else {
                astOutputRec(arq, astNode->children[0]);
            }
            break;
        case AST_VAR_DEC:
            astOutputRec(arq, astNode->children[0]);
            fprintf(arq, "%s", astNode->symbol->str);
            fprintf(arq, ":");
            astOutputRec(arq, astNode->children[1]);
            fprintf(arq, ";");
            break;
        case AST_VEC_DEC:
            if (astNode->children[2]) {
                astOutputRec(arq, astNode->children[0]);
                astOutputRec(arq, astNode->children[1]);
                fprintf(arq, ":");
                astOutputRec(arq, astNode->children[2]);
            } else {
                astOutputRec(arq, astNode->children[0]);
                astOutputRec(arq, astNode->children[1]);
            }
            fprintf(arq, ";");
            break;
        case AST_LIT_LIST:
            fprintf(arq, "%s ", astNode->symbol->str);
            astOutputRec(arq, astNode->children[0]);
            break;
        case AST_FUNC_DEC:
            astOutputRec(arq, astNode->children[0]);
            fprintf(arq, "%s", astNode->symbol->str);
            if (astNode->children[2]) {
                fprintf(arq, "(");
                astOutputRec(arq, astNode->children[1]);
                fprintf(arq, ")");
                astOutputRec(arq, astNode->children[2]);
            } else {
                fprintf(arq, "()");
                astOutputRec(arq, astNode->children[1]);
            }
            break;
        case AST_ARG_LIST:
        case AST_CARGS_LIST:
            if (astNode->children[1]) {
                astOutputRec(arq, astNode->children[0]);
                fprintf(arq, ",");
                astOutputRec(arq, astNode->children[1]);
            } else {
                astOutputRec(arq, astNode->children[0]);
            }
            break;
        case AST_ARG:
            astOutputRec(arq, astNode->children[0]);
            fprintf(arq, "%s", astNode->symbol->str);
            break;
        case AST_FUNC:
            fprintf(arq, "%s", astNode->symbol->str);
            if (astNode->children[0]) {
                fprintf(arq, "(");
                astOutputRec(arq, astNode->children[0]);
                fprintf(arq, ")");
            } else {
                fprintf(arq, "()");
            }
            break;
        case AST_CMD_LIST:
            if (astNode->children[1]) {
                astOutputRec(arq, astNode->children[0]);
                astOutputRec(arq, astNode->children[1]);
            } else {
                astOutputRec(arq, astNode->children[0]);
            }
            break;
        case AST_OPEN_BR:
            fprintf(arq, "(");
            astOutputRec(arq, astNode->children[0]);
            fprintf(arq, ")");
            break;
        default:
            fprintf(arq, "AST_UNKNOWN");
            break;
    }
}

void astPrintExpression(ast_t *astNode) {
    if (astNode == NULL) {
        return;
    }

    switch (astNode->type) {
        case AST_SYMBOL:
            fprintf(stderr, "%s", astNode->symbol->str);
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
            if (astNode->symbol) {
                fprintf(stderr, "%s", astNode->symbol->str);
            } else {
                astPrintExpression(astNode->children[0]);
                fprintf(stderr, " %s ", AST_INFOS[astNode->type].expr); 
                astPrintExpression(astNode->children[1]);
            }
            break;
        case AST_VEC:
            fprintf(stderr, "%s", astNode->symbol->str);
            fprintf(stderr, "[");
            astPrintExpression( astNode->children[0]);
            fprintf(stderr, "]");
            break;
    }
}
