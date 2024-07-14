%{
    // Etapa 2
    // Arthur Hendges da Silva - 00332968
    // 2024/01

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    extern int getLineNumber();
    extern int yylex();
    extern int yyerror();
%}

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

%token TK_IDENTIFIER

%token LIT_INT
%token LIT_CHAR
%token LIT_REAL
%token LIT_FALSE
%token LIT_TRUE
%token LIT_STRING

%token TOKEN_ERROR

%left '&' '|' '~'
%left OPERATOR_EQ OPERATOR_DIF
%left '<' '>' OPERATOR_LE OPERATOR_GE
%left '+' '-'
%left '*' '/'

%%
program: decl ;

// Programa eh uma lista de declaracoes
decl: decl dec 
    | dec 
    ;
dec: var_dec ';' 
   | func_dec 
   ;

// inicializacao de variaveis ( nao ocorre dentro de funcoes ) e vetores, linha 62
var_dec: type TK_IDENTIFIER ':' literal
       | type arr_call opt_arr_init 
       ;

// formato do vetor: nome[expressao]
arr_call: TK_IDENTIFIER '[' expr ']' 
        ;
// formato da chamada de funcao: nome(lista de expr) -> soma4(1,2,3,4)
// func_call_args: lista de expr separada por ',', ou vazio
func_call: TK_IDENTIFIER '(' func_call_args ')' 
         ;
func_call_args: call_args_list 
              | 
              ;
call_args_list: expr ',' call_args_list 
              | expr
              ;

type: KW_CHAR 
    | KW_INT 
    | KW_FLOAT 
    | KW_BOOL 
    ;
literal: LIT_INT 
       | LIT_CHAR 
       | LIT_REAL 
       | LIT_TRUE 
       | LIT_FALSE 
       ;
arr_literal: LIT_INT 
           | LIT_CHAR 
           | LIT_REAL 
           | LIT_TRUE 
           | LIT_FALSE 
           | arr_literal literal 
           ;
// inicializar um vetor: vetor[2]; ou vetor[2]: 1 2 
opt_arr_init: ':' arr_literal 
            | 
            ;

// declaracao de funcao: tipo nome(int a, float b) {}
// argumentos podem ser uma lista com separador ',' ou vazio
func_dec: type TK_IDENTIFIER '(' args_func_dec ')' block 
        ;
args_func_dec: arg_list 
             | 
             ;
arg_list: arg ',' arg_list 
        | arg
        ;
arg: type TK_IDENTIFIER 
   ;

// blocos de funcoes podem conter listas de comandos, ou nada
block: '{' cmd_list '}' 
     | '{'  '}' 
     ;

// listas de comandos
// bloco
// vazio ';'
// simples atribuicao, read tipo , print, return
// controles lacos e if
cmd_list: cmd_list cmd 
        | cmd
        ;
cmd: ';' 
   | block 
   | TK_IDENTIFIER '=' expr ';' 
   | arr_call '=' expr ';' 
   | KW_PRINT arg_print ';' 
   | KW_READ arg_read ';' 
   | KW_RETURN expr ';' 
   | KW_IF '(' expr ')' cmd opt_else 
   | KW_WHILE '(' expr ')' cmd 
   ;
arg_print: type expr 
         | LIT_STRING 
         ;
arg_read: type TK_IDENTIFIER 
        ;
opt_else: KW_ELSE cmd 
        | 
        ;

// expr literal eh um valor nao em memoria 9 == 9
// TK_IDENTIFIER eh uma var ja declarada arthur == joao, onde int arthur: 1, int joao: 2
// arr_call eh uma posicao de um vetor ja declarado notas[2], onde int notas[3]: 1 2 3
// func_call eh uma chamada de uma funcao ja declarada
expr: literal 
    | TK_IDENTIFIER 
    | arr_call 
    | func_call 
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr '>' expr
    | expr '<' expr
    | expr OPERATOR_LE expr
    | expr OPERATOR_GE expr
    | expr OPERATOR_EQ expr
    | expr OPERATOR_DIF expr
    | expr '&' expr
    | expr '|' expr
    | expr '~' expr 
    | '(' expr ')'
    ;

%%

int yyerror() {
    fprintf(stderr, "Syntax error at line %d\n", getLineNumber());
    exit(3);
} 
