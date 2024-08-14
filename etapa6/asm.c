// Compiladores - Etapa 6 - Marcelo Johann - 2024/01
// Arthur Hendges da Silva - 00332968
// 

#include "asm.h"
#include "semantic.h"
#include "stdlib.h"
#include <string.h>

extern hash_t *hashTable[HASH_SIZE];

const char *stringType[] = { 
    [DATATYPE_INT]   = "LC0", 
    [DATATYPE_CHAR]  = "LC1", 
    [DATATYPE_FLOAT] = "LC2", 
    [DATATYPE_BOOL]  = "LC3",
};

const char *opASM[] = {
    [TAC_ADD] = "addl",
    [TAC_SUB] = "subl",
    [TAC_MUL] = "imull",
    [TAC_DIV] = "imull",
    [TAC_GT] = "imull",
    [TAC_LT] = "imull",
    [TAC_GE] = "imull",
    [TAC_LE] = "imull",
    [TAC_EQ] = "imull",
    [TAC_DIF] = "imull",
};

void generateAsm(tac_t *node) {
    FILE *file = fopen(FILE_OUT, "w");
    static int order = 0;

    // Init
    fprintf(file,
             ".LC0:"              "\n"
        "\t" ".string \"%%d\\n\"" "\n"

             ".LC1:"              "\n"
        "\t" ".string \"%%c\\n\"" "\n"

             ".LC2:"              "\n"
        "\t" ".string \"%%f\\n\"" "\n"

             ".LC3:"              "\n"
        "\t" ".string \"%%d\\n\"" "\n"
                                  "\n"
    );
    
    // tac
    tac_t *aux;
    for (aux = node; aux; aux = aux->next) {
        switch (aux->type) {
            case TAC_BEGINFUNC:
                order = 0;
                fprintf(file,
                    "\t" ".globl %s"         "\n"
                         "%s:"               "\n"
                    "\t" "pushq %%rbp"       "\n"
                    "\t" "movq %%rsp, %%rbp" "\n"
                                             "\n"
                , aux->op0->str
                , aux->op0->str);
                break;
            case TAC_ENDFUNC:
                fprintf(file,
                    "\t" "popq %%rbp" "\n"
                    "\t" "ret"        "\n"
                                      "\n"
                );
                break;
            case TAC_ADD:
                if (aux->op1->datatype == DATATYPE_INT
                    || aux->op1->datatype == DATATYPE_CHAR) {
                    fprintf(stderr, ".....................%s %s %s\n", aux->op1->str, aux->op2->str, aux->op0->str);
                    fprintf(file,
                        "\t" "movl _%s(%%rip), %%edx" "\n"
                        "\t" "movl _%s(%%rip), %%eax" "\n"
                        "\t" "addl %%edx, %%eax"      "\n"
                        "\t" "movl %%eax, _%s(%%rip)" "\n"
                                                      "\n"
                    , aux->op1->str
                    , aux->op2->str
                    , aux->op0->str);
                } else {
                    fprintf(file,
                        "\t" "movss _%s(%%rip), %%xmm1" "\n"
                        "\t" "movss _%s(%%rip), %%xmm0" "\n"
                        "\t" "addss %%xmm1, %%xmm0"     "\n"
                        "\t" "movss %%xmm0, _%s(%%rip)" "\n"
                                                        "\n"
                    , aux->op1->str
                    , aux->op2->str
                    , aux->op0->str);
                }
                break;
            case TAC_SUB:
                fprintf(file,
                    "\t" "movl _%s(%%rip), %%eax" "\n"
                    "\t" "movl _%s(%%rip), %%edx" "\n"
                    "\t" "subl %%edx, %%eax"      "\n"
                    "\t" "movl %%eax, _%s(%%rip)" "\n"
                                                  "\n"
                , aux->op1->str
                , aux->op2->str
                , aux->op0->str);
                break;
            case TAC_MUL:
                fprintf(file,
                    "\t" "movl _%s(%%rip), %%edx" "\n"
                    "\t" "movl _%s(%%rip), %%eax" "\n"
                    "\t" "imul %%edx, %%eax"      "\n"
                    "\t" "movl %%eax, _%s(%%rip)" "\n"
                                                  "\n"
                , aux->op1->str
                , aux->op2->str
                , aux->op0->str);
                break;
            case TAC_DIV:
                fprintf(file,
                    "\t" "movl _%s(%%rip), %%eax" "\n"
                    "\t" "movl _%s(%%rip), %%ecx" "\n"
                    "\t" "cltd"                   "\n"
                    "\t" "idivl	%%ecx"            "\n"
                    "\t" "movl %%eax, _%s(%%rip)" "\n"
                                                  "\n"
                , aux->op1->str
                , aux->op2->str
                , aux->op0->str);
                break;
            case TAC_GT:
                fprintf(file,
                    "\t" "movl _%s(%%rip), %%edx" "\n"
                    "\t" "movl _%s(%%rip), %%eax" "\n"
                    "\t" "cmpl %%eax, %%edx"      "\n"
                    "\t" "setg %%al"              "\n"
	                "\t" "movzbl %%al, %%eax"     "\n"
	                "\t" "movl %%eax, _%s(%%rip)" "\n"
                                                  "\n"
                , aux->op1->str
                , aux->op2->str
                , aux->op0->str);
                break;
            case TAC_LT:
                fprintf(file,
                    "\t" "movl _%s(%%rip), %%edx" "\n"
                    "\t" "movl _%s(%%rip), %%eax" "\n"
                    "\t" "cmpl %%eax, %%edx"      "\n"
                    "\t" "setl %%al"              "\n"
	                "\t" "movzbl %%al, %%eax"     "\n"
	                "\t" "movl %%eax, _%s(%%rip)" "\n"
                                                  "\n"
                , aux->op1->str
                , aux->op2->str
                , aux->op0->str);
                break;
            case TAC_GE:
                fprintf(file,
                    "\t" "movl _%s(%%rip), %%edx" "\n"
                    "\t" "movl _%s(%%rip), %%eax" "\n"
                    "\t" "cmpl %%eax, %%edx"      "\n"
                    "\t" "setge %%al"             "\n"
	                "\t" "movzbl %%al, %%eax"     "\n"
	                "\t" "movl %%eax, _%s(%%rip)" "\n"
                                                  "\n"
                , aux->op1->str
                , aux->op2->str
                , aux->op0->str);
                break;
            case TAC_LE:
                fprintf(file,
                    "\t" "movl _%s(%%rip), %%edx" "\n"
                    "\t" "movl _%s(%%rip), %%eax" "\n"
                    "\t" "cmpl %%eax, %%edx"      "\n"
                    "\t" "setle %%al"             "\n"
	                "\t" "movzbl %%al, %%eax"     "\n"
	                "\t" "movl %%eax, _%s(%%rip)" "\n"
                                                  "\n"
                , aux->op1->str
                , aux->op2->str
                , aux->op0->str);
                break;
            case TAC_EQ:
                fprintf(file,
                    "\t" "movl _%s(%%rip), %%edx" "\n"
                    "\t" "movl _%s(%%rip), %%eax" "\n"
                    "\t" "cmpl %%eax, %%edx"      "\n"
                    "\t" "sete %%al"              "\n"
                    "\t" "movzbl %%al, %%eax"     "\n"
                    "\t" "movl %%eax, _%s(%%rip)" "\n"
                                                  "\n"
                , aux->op1->str
                , aux->op2->str
                , aux->op0->str);
                break;
            case TAC_DIF:
                fprintf(file,
                    "\t" "movl _%s(%%rip), %%edx" "\n"
                    "\t" "movl _%s(%%rip), %%eax" "\n"
                    "\t" "cmpl %%eax, %%edx"      "\n"
                    "\t" "setne %%al"             "\n"
                    "\t" "movzbl %%al, %%eax"     "\n"
                    "\t" "movl %%eax, _%s(%%rip)" "\n"
                                                  "\n"
                , aux->op1->str
                , aux->op2->str
                , aux->op0->str);
                break;
            case TAC_AND:
                fprintf(file,
                    "\t" "movl _%s(%%rip), %%eax" "\n"
                    "\t" "movl _%s(%%rip), %%edx" "\n"
                    "\t" "andl %%edx, %%eax"      "\n"
                    "\t" "movl %%eax, _%s(%%rip)" "\n"
                                                  "\n"
                , aux->op1->str
                , aux->op2->str
                , aux->op0->str);
                break;
            case TAC_OR:
                fprintf(file,
                    "\t" "movl _%s(%%rip), %%eax" "\n"
                    "\t" "movl _%s(%%rip), %%edx" "\n"
                    "\t" "orl %%edx, %%eax"       "\n"
                    "\t" "movl %%eax, _%s(%%rip)" "\n"
                                                  "\n"
                , aux->op1->str
                , aux->op2->str
                , aux->op0->str);
                break;
            case TAC_NOT:
                fprintf(file,
                    "\t" "movl _%s(%%rip), %%eax" "\n"
                    "\t" "cmpl $0, %%eax"         "\n"
                    "\t" "sete %%al"              "\n"
                    "\t" "movzbl %%al, %%eax"     "\n"
                    "\t" "movl %%eax, _%s(%%rip)" "\n"
                                                  "\n"
                , aux->op1->str
                , aux->op0->str);
                break;
            case TAC_VEC_READ:
                fprintf(file,
                    "\t" "movl _%s(%%rip), %%eax"    "\n"
                    "\t" "cltq"                      "\n"
                    "\t" "leaq 0(,%%rax,4), %%rdx"   "\n"
                    "\t" "leaq _%s(%%rip), %%rax"    "\n"
                    "\t" "movl (%%rdx,%%rax), %%eax" "\n"
                    "\t" "movl %%eax, _%s(%%rip)"    "\n"
                    "\n",
                    aux->op2->str,
                    aux->op1->str,
                    aux->op0->str
                );
                break;
            case TAC_ASSIGN:
                fprintf(file, 
                	"\t" "movl _%s(%%rip), %%eax" "\n"
	                "\t" "movl %%eax, _%s(%%rip)" "\n"
                                                  "\n"
                , aux->op1->str
                , aux->op0->str);
                break;
            case TAC_VEC_ASSIGN:
                fprintf(file, 
                	"\t" "movl _%s(%%rip), %%eax"     "\n"
                	"\t" "cltq"                       "\n"
                	"\t" "leaq 0(,%%rax, %d), %%rdx"  "\n"
                	"\t" "leaq _%s(%%rip), %%rax"     "\n"
                	"\t" "movl _%s(%%rip), %%ebx"     "\n"
	                "\t" "movl %%ebx, (%%rdx, %%rax)" "\n"
                                                      "\n"
                , aux->op1->str
                , 4
                , aux->op0->str
                , aux->op2->str);
                break;
            case TAC_PRINT:
                if (aux->op0->type == SYMBOL_LIT_STRING) {
                    fprintf(file,
                        "\t" "leaq _%s(%%rip), %%rax" "\n"
                        "\t" "movq %%rax, %%rdi"      "\n"
                        "\t" "call printf@PLT"        "\n"
                                                      "\n"
                    , aux->op0->str);
                } else if (aux->op0->datatype == DATATYPE_FLOAT) {
                    fprintf(file,
                        "\t" "movss	_%s(%%rip), %%xmm0" "\n"
                        "\t" "pxor %%xmm1, %%xmm1"      "\n"
                        "\t" "cvtss2sd %%xmm0, %%xmm1"  "\n"
                        "\t" "movq %%xmm1, %%rax"       "\n"
                        "\t" "movq %%rax, %%xmm0"       "\n"
                        "\t" "leaq .LC2(%%rip), %%rax"  "\n"
                        "\t" "movq %%rax, %%rdi"        "\n"
                        "\t" "movl $1, %%eax"           "\n"
                        "\t" "call printf@PLT"          "\n"
                                                        "\n"
                    , aux->op0->str);
                } else {
                    fprintf(file,
                        "\t" "movl _%s(%%rip), %%esi" "\n"
                        "\t" "leaq .%s(%%rip), %%rax" "\n"
                        "\t" "movq %%rax, %%rdi"      "\n"
                        "\t" "call printf@PLT"        "\n"
                                                      "\n"
                    , aux->op0->str
                    , stringType[aux->op0->datatype]);
                }
                break;
            case TAC_LABEL:
                fprintf(file,
                    "_%s:" "\n"
                           "\n"
                , aux->op0->str);
                break;
            case TAC_JF:
                fprintf(file,
                    "\t" "cmpl $0, _%s(%%rip)" "\n"
                    "\t" "je _%s"              "\n"
                                               "\n"
                , aux->op1->str
                , aux->op0->str);
                break;
            case TAC_J:
                fprintf(file,
                    "\t" "jmp _%s" "\n"
                                   "\n"
                , aux->op0->str);
                break;
            case TAC_ARG:
                order++;
                break;
            case TAC_PARAM:
                order++;
                break;
            case TAC_CALL:
                order = 0;
                break;
            case TAC_READ:
                break;
            case TAC_RETURN:
                break;
            default:
                break;
        }
    }

    // hash_table
    printAsmFromHT(file, hashTable);
}

void printAsmFromHT(FILE *file, hash_t *table[]) {
    hash_t *hashNode;
    fprintf(file,
        "\t" ".data" "\n"
    );
    for (int i = 0; i < HASH_SIZE; i++) {
        for (hashNode = table[i]; hashNode; hashNode = hashNode->next) {
            if (hashNode->type == SYMBOL_VAR) {
                fprintf(file, "_%s:" "\n", hashNode->str);
                if (hashNode->ast->children[1]->symbol->type == SYMBOL_LIT_INT) {
                    fprintf(file,
                        "\t" ".long %s" "\n"
                    , hashNode->ast->children[1]->symbol->str);
                } else if (hashNode->ast->children[1]->symbol->type == SYMBOL_LIT_REAL) {
                    int binRep;
                    float f = strtof(hashNode->ast->children[1]->symbol->str, NULL);
                    memcpy(&binRep, &f, sizeof(int));
                    fprintf(file,
                        "\t" ".long %d" "\n"
                    , binRep);
                } else if (hashNode->ast->children[1]->symbol->type == SYMBOL_LIT_CHAR) {
                    fprintf(file,
                        "\t" ".long %d" "\n"
                    , (int)hashNode->ast->children[1]->symbol->str[1]);
                } else if (hashNode->ast->children[1]->symbol->type == SYMBOL_LIT_TRUE
                            || hashNode->ast->children[1]->symbol->type == SYMBOL_LIT_FALSE) {
                    fprintf(file,
                        "\t" ".long %d" "\n"
                    , hashNode->ast->children[1]->symbol->type == SYMBOL_LIT_TRUE 
                        ? 1 
                        : 0);
                }
            } else if (hashNode->type == SYMBOL_VEC) {
                fprintf(file, "_%s:" "\n", hashNode->str);
                if (hashNode->ast->children[2]) {
                    for(ast_t *i = hashNode->ast->children[2]; i; i = i->children[0]) {
                        if (i->symbol->type == SYMBOL_LIT_INT) {
                            fprintf(file,
                                "\t" ".long %s" "\n"
                            , i->symbol->str);
                        } else if (i->symbol->type == SYMBOL_LIT_REAL) {
                            int binRep;
                            float f = strtof(i->symbol->str, NULL);
                            memcpy(&binRep, &f, sizeof(int));
                            fprintf(file,
                                "\t" ".long %d" "\n"
                            , binRep);
                        } else if (i->symbol->type == SYMBOL_LIT_CHAR) {
                            fprintf(file,
                                "\t" ".long %d" "\n"
                            , (int)i->symbol->str[1]);
                        } else if (i->symbol->type == SYMBOL_LIT_TRUE
                                    || i->symbol->type == SYMBOL_LIT_FALSE) {
                            fprintf(file,
                                "\t" ".long %d" "\n"
                            , i->symbol->type == SYMBOL_LIT_TRUE 
                                ? 1 
                                : 0);
                        }
                    }
                } else {
                    fprintf(file, 
                        "\t" ".zero %d" "\n"
                    , atoi(hashNode->ast->children[1]->children[0]->symbol->str) * 4);
                }
            } else if (hashNode->type == SYMBOL_LIT_INT) {
                fprintf(file,
                    "_%s:"          "\n"
                    "\t" ".long %s" "\n"
                , hashNode->str
                , hashNode->str);
            } else if (hashNode->type == SYMBOL_LIT_REAL) {
                int binRep;
                float f = strtof(hashNode->str, NULL);
                memcpy(&binRep, &f, sizeof(int));
                fprintf(file,
                    "_%s:"          "\n"
                    "\t" ".long %d" "\n"
                , hashNode->str
                , binRep);
            } else if (hashNode->type == SYMBOL_LIT_CHAR) {
                fprintf(file,
                    "_%s:"          "\n"
                    "\t" ".long %d" "\n"
                , hashNode->str
                , (int)hashNode->str[1]);
            } else if (hashNode->type == SYMBOL_LIT_TRUE
                || hashNode->type == SYMBOL_LIT_FALSE) {
                fprintf(file,
                    "_%s:"          "\n"
                    "\t" ".long %d" "\n"
                , hashNode->str
                , hashNode->type == SYMBOL_LIT_TRUE 
                    ? 1 
                    : 0);
            } else if (hashNode->type == SYMBOL_LIT_STRING) {
                int binRep;
                memcpy(&binRep, hashNode->str, sizeof(int));
                fprintf(file,
                    "_%s:"          "\n"
                    "\t" ".string %s" "\n"
                , hashNode->str
                , hashNode->str);
            }
            
            if (hashNode->type == SYMBOL_TEMP) {
                fprintf(file,
                    "_%s:"          "\n"
                    "\t" ".long %d" "\n" // Dont need init
                , hashNode->str
                , 0);
            }
        }
    }
}