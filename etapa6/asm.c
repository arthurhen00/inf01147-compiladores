// Compiladores - Etapa 6 - Marcelo Johann - 2024/01
// Arthur Hendges da Silva - 00332968
// 

#include "asm.h"
#include "semantic.h"
#include "stdlib.h"

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
};

void generateAsm(tac_t *node) {
    FILE *file = fopen(FILE_OUT, "w");
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
                fprintf(file,
                    "\t" "movl _%s(%%rip), %%edx" "\n"
                    "\t" "movl _%s(%%rip), %%eax" "\n"
                    "\t" "addl %%edx, %%eax"      "\n"
                    "\t" "movl %%eax, _%s(%%rip)" "\n"
                                                  "\n"
                , aux->op1->str
                , aux->op2->str
                , aux->op0->str);
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
                //
                break;
            case TAC_VEC_READ:
                fprintf(file,
                    "\t" "movl %d+_%s(%%rip), %%eax" "\n"
                    "\t" "movl %%eax, _%s(%%rip)"    "\n"
                                                     "\n"
                , atoi(aux->op2->str) * 4
                , aux->op1->str, aux->op0->str);
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
                	"\t" "movl %d+_%s(%%rip), %%eax" "\n"
	                "\t" "movl %%eax, _%s(%%rip)"    "\n"
                                                     "\n"
                , atoi(aux->op1->str) * 4
                , aux->op2->str
                , aux->op0->str);
                break;
            case TAC_PRINT:
                fprintf(file,
                    "\t" "movl _%s(%%rip), %%esi" "\n"
                    "\t" "leaq .%s(%%rip), %%rax" "\n"
                    "\t" "movq %%rax, %%rdi"      "\n"
                    "\t" "call printf@PLT"        "\n"
                                                  "\n"
                , aux->op0->str
                , aux->op0->datatype ? stringType[aux->op0->datatype] : "LC0");
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
            if (hashNode->type == SYMBOL_VAR 
                || hashNode->type == SYMBOL_LIT_INT
                || hashNode->type == SYMBOL_LIT_CHAR
                || hashNode->type == SYMBOL_LIT_REAL
                || hashNode->type == SYMBOL_LIT_FALSE
                || hashNode->type == SYMBOL_LIT_TRUE) {
                fprintf(file,
                    "_%s:"          "\n"
                    "\t" ".long %s" "\n"
                , hashNode->str, hashNode->ast ? hashNode->ast->children[1]->symbol->str : hashNode->str);
            }

            if (hashNode->type == SYMBOL_TEMP) {
                fprintf(file,
                    "_%s:"          "\n"
                    "\t" ".long %d" "\n" // Dont need init
                , hashNode->str, 0);
            }
            
            if (hashNode->type == SYMBOL_VEC) {
                fprintf(file, "_%s:" "\n", hashNode->str);
                if (hashNode->ast->children[2]) {
                    for(ast_t *i = hashNode->ast->children[2]; i; i = i->children[0]) {
                        fprintf(file, 
                            "\t" ".long %s" "\n"
                        , i->symbol->str);
                    }
                } else {
                    fprintf(file, 
                        "\t" ".zero %d" "\n"
                    , atoi(hashNode->ast->children[1]->children[0]->symbol->str) * 4);
                }
            }
        }
    }
}