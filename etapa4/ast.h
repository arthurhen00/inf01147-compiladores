// Compiladores - Etapa 4 - Marcelo Johann - 2024/01
// Arthur Hendges da Silva - 00332968
// 

#ifndef AST_HEADER
#define AST_HEADER

#define MAX_CHILDREN 4

#define AST_SYMBOL     1
#define AST_ADD        2
#define AST_SUB        3
#define AST_MUL        4
#define AST_DIV        5
#define AST_GT         6
#define AST_LT         7
#define AST_GE         8
#define AST_LE         9
#define AST_EQ         10
#define AST_DIF        11
#define AST_AND        12
#define AST_OR         13
#define AST_NOT        14
#define AST_ASSIGN     15
#define AST_VEC_ASSIGN 16
#define AST_CMD        17
#define AST_CMD_LIST   18
#define AST_VEC        19
#define AST_PRINT      20
#define AST_INT        21
#define AST_FLOAT      22
#define AST_CHAR       23
#define AST_BOOL       24
#define AST_READ       25
#define AST_RETURN     26
#define AST_IF         27
#define AST_BLOCK      28
#define AST_WHILE      29
#define AST_EMPTY_CMD  30
#define AST_DEC_LIST   31
#define AST_DEC        32
#define AST_LIT_LIST   33
#define AST_VAR_DEC    34
#define AST_VEC_DEC    35
#define AST_FUNC_DEC   36
#define AST_ARG_LIST   37
#define AST_ARG        38
#define AST_FUNC       39
#define AST_CARGS_LIST 40

#include "hash_table.h"
#include <stdio.h>

extern char **global_argv; //

typedef struct astNode {
    struct astNode *children[MAX_CHILDREN];
    struct hashNode *symbol;
    int type;
} ast_t;

typedef struct astInfos {
    int value;
    const char *name;
    const char *expr;
} astinfos_t;

const static astinfos_t AST_INFOS[] = {
    { 0             , NULL            , NULL    },
    { AST_SYMBOL    , "AST_SYMBOL"    , NULL    },
    { AST_ADD       , "AST_ADD"       , "+"     },
    { AST_SUB       , "AST_SUB"       , "-"     },
    { AST_MUL       , "AST_MUL"       , "*"     },
    { AST_DIV       , "AST_DIV"       , "/"     },
    { AST_GT        , "AST_GT"        , ">"     },
    { AST_LT        , "AST_LT"        , "<"     },
    { AST_GE        , "AST_GE"        , ">="    },
    { AST_LE        , "AST_LE"        , "<="    },
    { AST_EQ        , "AST_EQ"        , "=="    },
    { AST_DIF       , "AST_DIF"       , "!="    },
    { AST_AND       , "AST_AND"       , "&"     },
    { AST_OR        , "AST_OR"        , "|"     },
    { AST_NOT       , "AST_NOT"       , "~"     },
    { AST_ASSIGN    , "AST_ASSIGN"    , "="     },
    { AST_VEC_ASSIGN, "AST_VEC_ASSIGN", NULL    },
    { AST_CMD       , "AST_CMD"       , NULL    },
    { AST_CMD_LIST  , "AST_CMD_LIST"  , NULL    },
    { AST_VEC       , "AST_VEC"       , NULL    },
    { AST_PRINT     , "AST_PRINT"     , NULL    },
    { AST_INT       , "AST_INT"       , "int"   },
    { AST_FLOAT     , "AST_FLOAT"     , "float" },
    { AST_CHAR      , "AST_CHAR"      , "char"  },
    { AST_BOOL      , "AST_BOOL"      , "bool"  },
    { AST_READ      , "AST_READ"      , NULL    },
    { AST_RETURN    , "AST_RETURN"    , NULL    },
    { AST_IF        , "AST_IF"        , NULL    },
    { AST_BLOCK     , "AST_BLOCK"     , NULL    },
    { AST_WHILE     , "AST_WHILE"     , NULL    },
    { AST_EMPTY_CMD , "AST_EMPTY_CMD" , ";"     },
    { AST_DEC_LIST  , "AST_DEC_LIST"  , NULL    },
    { AST_DEC       , "AST_DEC"       , NULL    },
    { AST_LIT_LIST  , "AST_LIT_LIST"  , NULL    },
    { AST_VAR_DEC   , "AST_VAR_DEC"   , NULL    },
    { AST_VEC_DEC   , "AST_VEC_DEC"   , NULL    },
    { AST_FUNC_DEC  , "AST_FUNC_DEC"  , NULL    },
    { AST_ARG_LIST  , "AST_ARG_LIST"  , NULL    },
    { AST_ARG       , "AST_ARG"       , NULL    },
    { AST_FUNC      , "AST_FUNC"      , NULL    },
    { AST_CARGS_LIST, "AST_CARGS_LIST", NULL    },
};

ast_t *astCreate(int type, hash_t *symbol, ast_t *c0, ast_t *c1, ast_t *c2, ast_t *c3);
void astPrint(ast_t *astNode, int level);
void astOutput(ast_t *astNode);
void astOutputRec(FILE *arq, ast_t *astNode);
void astPrintExpression(ast_t *astNode);

#endif // AST_HEADER