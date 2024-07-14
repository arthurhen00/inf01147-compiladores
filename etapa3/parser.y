%{
// Compiladores - Etapa 3 - Marcelo Johann - 2024/01
// Arthur Hendges da Silva - 00332968
// 

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "hash_table.h"
    #include "ast.h"

    extern int getLineNumber();
    extern int yylex();
    extern int yyerror();
%}

%union {
    hash_t *symbol;
    ast_t *ast;
}

%token KW_CHAR
%token KW_INT
%token KW_FLOAT
%token KW_BOOL

%token KW_IF
%token KW_ELSE
%token KW_WHILE
%token KW_READ
%token KW_PRINT
%token KW_RETURN

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_DIF

%token<symbol> TK_IDENTIFIER

%token<symbol> LIT_INT
%token<symbol> LIT_CHAR
%token<symbol> LIT_REAL
%token<symbol> LIT_FALSE
%token<symbol> LIT_TRUE
%token<symbol> LIT_STRING

%token TOKEN_ERROR

%type<symbol> literal
%type<ast> type expr arr_call func_call cmd cmd_list block dec decl list_literal arg_dec func_dec arg arg_list call_args_list

%left '&' '|' '~'
%left OPERATOR_EQ OPERATOR_DIF
%left '<' '>' OPERATOR_LE OPERATOR_GE
%left '+' '-'
%left '*' '/'

%%
program: decl  { astPrint($1, 0); printf("\n***\n"); astOutput($1); }
       ;

decl: dec decl { $$ = astCreate(AST_DEC_LIST, NULL, $1, $2  , NULL, NULL); }
    | dec      { $$ = astCreate(AST_DEC     , NULL, $1, NULL, NULL, NULL); }
    ;
dec: type TK_IDENTIFIER arg_dec ';'     { $$ = astCreate(AST_VAR_DEC, $2  , $1, $3, NULL, NULL); }
   | type arr_call ':' list_literal ';' { $$ = astCreate(AST_VEC_DEC, NULL, $1, $2, $4  , NULL); }
   | type arr_call ';'                  { $$ = astCreate(AST_VEC_DEC, NULL, $1, $2, NULL, NULL); }
   | func_dec                           { $$ = $1; }
   ;
arg_dec: ':' literal { $$ = astCreate(AST_SYMBOL, $2, NULL, NULL, NULL, NULL); }
       ;
arr_call: TK_IDENTIFIER '[' expr ']' { $$ = astCreate(AST_VEC, $1, $3, NULL, NULL, NULL); }
        ;
func_call: TK_IDENTIFIER '(' call_args_list ')' { $$ = astCreate(AST_FUNC, $1, $3  , NULL, NULL, NULL); }
         | TK_IDENTIFIER '('  ')'               { $$ = astCreate(AST_FUNC, $1, NULL, NULL, NULL, NULL); }
         ;
call_args_list: expr ',' call_args_list { $$ = astCreate(AST_CARGS_LIST, NULL, $1, $3  , NULL, NULL); }
              | expr                    { $$ = astCreate(AST_CARGS_LIST, NULL, $1, NULL, NULL, NULL); }
              ;

type: KW_CHAR  { $$ = astCreate(AST_CHAR , NULL, NULL, NULL, NULL, NULL); }
    | KW_INT   { $$ = astCreate(AST_INT  , NULL, NULL, NULL, NULL, NULL); }
    | KW_FLOAT { $$ = astCreate(AST_FLOAT, NULL, NULL, NULL, NULL, NULL); }
    | KW_BOOL  { $$ = astCreate(AST_BOOL , NULL, NULL, NULL, NULL, NULL); }
    ;
literal: LIT_INT   { $$ = $1; }
       | LIT_CHAR  { $$ = $1; }
       | LIT_REAL  { $$ = $1; }
       | LIT_TRUE  { $$ = $1; }
       | LIT_FALSE { $$ = $1; }
       ;
list_literal: literal list_literal { $$ = astCreate(AST_LIT_LIST, $1, $2  , NULL, NULL, NULL); }
           | literal               { $$ = astCreate(AST_SYMBOL  , $1, NULL, NULL, NULL, NULL); }
           ; 

func_dec: type TK_IDENTIFIER '(' arg_list ')' block { $$ = astCreate(AST_FUNC_DEC, $2, $1, $4, $6  , NULL); }
        | type TK_IDENTIFIER '('  ')' block         { $$ = astCreate(AST_FUNC_DEC, $2, $1, $5, NULL, NULL); }
        ;
arg_list: arg ',' arg_list { $$ = astCreate(AST_ARG_LIST, NULL, $1, $3  , NULL, NULL); }
        | arg              { $$ = astCreate(AST_ARG_LIST, NULL, $1, NULL, NULL, NULL); }
        ;
arg: type TK_IDENTIFIER { $$ = astCreate(AST_ARG, $2, $1, NULL, NULL, NULL); }
   ;

block: '{' cmd_list '}' { $$ = astCreate(AST_BLOCK, NULL, $2  , NULL, NULL, NULL); }
     | '{'  '}'         { $$ = astCreate(AST_BLOCK, NULL, NULL, NULL, NULL, NULL); }
     ;

cmd_list: cmd cmd_list { $$ = astCreate(AST_CMD_LIST, NULL, $1, $2  , NULL, NULL); }
        | cmd          { $$ = astCreate(AST_CMD_LIST, NULL, $1, NULL, NULL, NULL); }
        ;
cmd: ';'                                { $$ = astCreate(AST_EMPTY_CMD , NULL, NULL, NULL, NULL, NULL); }
   | block                              { $$ = $1; }
   | TK_IDENTIFIER '=' expr ';'         { $$ = astCreate(AST_ASSIGN    , $1  , $3  , NULL, NULL, NULL); }
   | arr_call '=' expr ';'              { $$ = astCreate(AST_VEC_ASSIGN, NULL, $1  , $3  , NULL, NULL); }
   | KW_PRINT type expr ';'             { $$ = astCreate(AST_PRINT     , NULL, $2  , $3  , NULL, NULL); }
   | KW_PRINT LIT_STRING ';'            { $$ = astCreate(AST_PRINT     , $2  , NULL, NULL, NULL, NULL); }
   | KW_READ type TK_IDENTIFIER ';'     { $$ = astCreate(AST_READ      , $3  , $2  , NULL, NULL, NULL); }
   | KW_RETURN expr ';'                 { $$ = astCreate(AST_RETURN    , NULL, $2  , NULL, NULL, NULL); }
   | KW_IF '(' expr ')' cmd KW_ELSE cmd { $$ = astCreate(AST_IF        , NULL, $3  , $5  , $7  , NULL); }
   | KW_IF '(' expr ')' cmd             { $$ = astCreate(AST_IF        , NULL, $3  , $5  , NULL, NULL); }
   | KW_WHILE '(' expr ')' cmd          { $$ = astCreate(AST_WHILE     , NULL, $3  , $5  , NULL, NULL); }
   ;

expr: literal                { $$ = astCreate(AST_SYMBOL, $1  , NULL, NULL, NULL, NULL); }
    | TK_IDENTIFIER          { $$ = astCreate(AST_SYMBOL, $1  , NULL, NULL, NULL, NULL); }
    | arr_call               { $$ = $1; }
    | func_call              { $$ = $1; }
    | expr '+' expr          { $$ = astCreate(AST_ADD   , NULL, $1  , $3  , NULL, NULL); }
    | expr '-' expr          { $$ = astCreate(AST_SUB   , NULL, $1  , $3  , NULL, NULL); }
    | expr '*' expr          { $$ = astCreate(AST_MUL   , NULL, $1  , $3  , NULL, NULL); }
    | expr '/' expr          { $$ = astCreate(AST_DIV   , NULL, $1  , $3  , NULL, NULL); }
    | expr '>' expr          { $$ = astCreate(AST_GT    , NULL, $1  , $3  , NULL, NULL); }
    | expr '<' expr          { $$ = astCreate(AST_LT    , NULL, $1  , $3  , NULL, NULL); }
    | expr OPERATOR_LE expr  { $$ = astCreate(AST_LE    , NULL, $1  , $3  , NULL, NULL); } 
    | expr OPERATOR_GE expr  { $$ = astCreate(AST_GE    , NULL, $1  , $3  , NULL, NULL); }
    | expr OPERATOR_EQ expr  { $$ = astCreate(AST_EQ    , NULL, $1  , $3  , NULL, NULL); }
    | expr OPERATOR_DIF expr { $$ = astCreate(AST_DIF   , NULL, $1  , $3  , NULL, NULL); }
    | expr '&' expr          { $$ = astCreate(AST_AND   , NULL, $1  , $3  , NULL, NULL); }
    | expr '|' expr          { $$ = astCreate(AST_OR    , NULL, $1  , $3  , NULL, NULL); }
    | expr '~' expr          { $$ = astCreate(AST_NOT   , NULL, $1  , $3  , NULL, NULL); }
    | '(' expr ')'           { $$ = $2; }
    ;

%%

int yyerror() {
    fprintf(stderr, "Syntax error at line %d\n", getLineNumber());
    exit(3);
} 
