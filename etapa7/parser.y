%{
// Compiladores - Etapa 7 - Marcelo Johann - 2024/01
// Arthur Hendges da Silva - 00332968
// 

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "hash_table.h"
    #include "ast.h"
    #include "semantic.h"
    #include "tac.h"
    #include "asm.h"

    extern int getLineNumber();
    extern int yylex();
    extern int yyerror();
    extern hash_t *hashTable[HASH_SIZE];

    int getSyntaxErrors();
    void reportSyntaxErrors(const char *str);
    int syntaxErrors = 0;
    int syntaxErrorsMessages = 0;
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

%left '|' 
%left '&' 
%left '<' '>' OPERATOR_DIF OPERATOR_EQ OPERATOR_GE OPERATOR_LE '~'
%left '+' '-'
%left '*' '/'

%%
program: decl   {   
                    // astPrint($1, 0);
                    checkSemantic($1, hashTable);
                    if (!getSyntaxErrors()) {
                        tac_t *code;
                        code = generateCode($1);
                        tacPrintBackward(code);
                        generateAsm(tacReverse(code));
                    }
                }
       ;

decl: dec decl { $$ = astCreate(AST_DEC_LIST, NULL, $1, $2  , NULL, NULL); }
    | dec      { $$ = astCreate(AST_DEC_LIST, NULL, $1, NULL, NULL, NULL); }
    ;
dec: type TK_IDENTIFIER arg_dec ';'     { $$ = astCreate(AST_VAR_DEC, $2  , $1, $3, NULL, NULL); }
   | type arr_call ':' list_literal ';' { $$ = astCreate(AST_VEC_DEC, NULL, $1, $2, $4  , NULL); }
   | type arr_call ';'                  { $$ = astCreate(AST_VEC_DEC, NULL, $1, $2, NULL, NULL); }
   | func_dec                           { $$ = $1; }
   | error TK_IDENTIFIER arg_dec ';'      { $$ = NULL; reportSyntaxErrors("Missing type in variable declaration.");    }
   | error arr_call ':' list_literal ';'  { $$ = NULL; reportSyntaxErrors("Missing type in vector declaration.");      }
   | error arr_call ';'                   { $$ = NULL; reportSyntaxErrors("Missing type in vector declaration.");      }
   | type TK_IDENTIFIER arg_dec error     { $$ = NULL; reportSyntaxErrors("Missing ';' in variable declaration.");     }
   | type arr_call ':' list_literal error { $$ = NULL; reportSyntaxErrors("Missing ';' in vector declaration.");     }
   | type arr_call error                  { $$ = NULL; reportSyntaxErrors("Missing ';' in vector declaration.");     }
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
              | expr error call_args_list { $$ = NULL; reportSyntaxErrors("Missing ',' between arguments."); }
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
        | error TK_IDENTIFIER '(' arg_list ')' block { $$ = NULL; reportSyntaxErrors("Missing return type in function declaration."); }
        | error TK_IDENTIFIER '('  ')' block         { $$ = NULL; reportSyntaxErrors("Missing return type in function declaration."); }
        | type TK_IDENTIFIER '(' arg_list ')' error  { $$ = NULL; reportSyntaxErrors("Missing function body."); }
        | type TK_IDENTIFIER '('  ')' error          { $$ = NULL; reportSyntaxErrors("Missing function body."); }
        ;
arg_list: arg ',' arg_list { $$ = astCreate(AST_ARG_LIST, NULL, $1, $3  , NULL, NULL); }
        | arg              { $$ = astCreate(AST_ARG_LIST, NULL, $1, NULL, NULL, NULL); }
        | arg error arg_list { $$ = NULL; reportSyntaxErrors("Missing ',' between parameters."); }
        ;
arg: type TK_IDENTIFIER { $$ = astCreate(AST_ARG, $2, $1, NULL, NULL, NULL); }
   | error TK_IDENTIFIER { $$ = NULL; reportSyntaxErrors("Missing param type"); }
   | type error          { $$ = NULL; reportSyntaxErrors("Missing param name"); }
   ;

block: '{' cmd_list '}' { $$ = astCreate(AST_BLOCK, NULL, $2  , NULL, NULL, NULL); }
     | '{'  '}'         { $$ = astCreate(AST_BLOCK, NULL, NULL, NULL, NULL, NULL); }
     | '{'  cmd_list error { $$ = NULL; reportSyntaxErrors("Missing '}' to close the block."); }
     | '{'  error          { $$ = NULL; reportSyntaxErrors("Missing '}' to close the block."); }
     ;

cmd_list: cmd cmd_list { $$ = astCreate(AST_CMD_LIST, NULL, $1, $2  , NULL, NULL); }
        | cmd          { $$ = astCreate(AST_CMD_LIST, NULL, $1, NULL, NULL, NULL); }
        ;
cmd: ';'                                     { $$ = astCreate(AST_EMPTY_CMD , NULL, NULL, NULL, NULL, NULL); }
   | block                                   { $$ = $1; }
   | TK_IDENTIFIER '=' expr ';'              { $$ = astCreate(AST_ASSIGN    , $1  , $3  , NULL, NULL, NULL); }
   | TK_IDENTIFIER '[' expr ']' '=' expr ';' { $$ = astCreate(AST_VEC_ASSIGN, $1  , $3  , $6  , NULL, NULL); }
   | KW_PRINT type expr ';'                  { $$ = astCreate(AST_PRINT     , NULL, $2  , $3  , NULL, NULL); }
   | KW_PRINT LIT_STRING ';'                 { $$ = astCreate(AST_PRINT     , $2  , NULL, NULL, NULL, NULL); }
   | KW_READ type TK_IDENTIFIER ';'          { $$ = astCreate(AST_READ      , $3  , $2  , NULL, NULL, NULL); }
   | KW_RETURN expr ';'                      { $$ = astCreate(AST_RETURN    , NULL, $2  , NULL, NULL, NULL); }
   | KW_IF '(' expr ')' cmd KW_ELSE cmd      { $$ = astCreate(AST_IF        , NULL, $3  , $5  , $7  , NULL); }
   | KW_IF '(' expr ')' cmd                  { $$ = astCreate(AST_IF        , NULL, $3  , $5  , NULL, NULL); }
   | KW_WHILE '(' expr ')' cmd               { $$ = astCreate(AST_WHILE     , NULL, $3  , $5  , NULL, NULL); }
   | TK_IDENTIFIER '=' expr error              { $$ = NULL; reportSyntaxErrors("Missing ';'.");                                         }
   | TK_IDENTIFIER '[' expr ']' '=' expr error { $$ = NULL; reportSyntaxErrors("Missing ';'.");                                         }
   | KW_PRINT type expr error                  { $$ = NULL; reportSyntaxErrors("Missing ';'.");                                         }
   | KW_PRINT LIT_STRING error                 { $$ = NULL; reportSyntaxErrors("Missing ';'.");                                         }
   | KW_PRINT error expr ';'                   { $$ = NULL; reportSyntaxErrors("Missing type before print statement.");                 }
   | KW_PRINT error ';'                        { $$ = NULL; reportSyntaxErrors("Missing expression or argument in print statement.");   }
   | KW_READ type TK_IDENTIFIER error          { $$ = NULL; reportSyntaxErrors("Missing ';'.");                                         }
   | KW_READ error TK_IDENTIFIER ';'           { $$ = NULL; reportSyntaxErrors("Missing type before variable in read statement.");      }
   | KW_READ type error ';'                    { $$ = NULL; reportSyntaxErrors("Missing variable name in read statement.");             }
   | KW_RETURN expr error                      { $$ = NULL; reportSyntaxErrors("Missing ';'.");           }
   | KW_RETURN error ';'                       { $$ = NULL; reportSyntaxErrors("Missing expression after return statement.");           }
   | KW_IF '(' error ')' cmd KW_ELSE cmd       { $$ = NULL; reportSyntaxErrors("Missing conditional expression in if-else statement."); }
   | KW_IF '(' error ')' cmd                   { $$ = NULL; reportSyntaxErrors("Missing conditional expression in if statement.");      }
   | KW_WHILE '(' error ')' cmd                { $$ = NULL; reportSyntaxErrors("Missing conditional expression in while statement.");   }
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
    | '~' expr               { $$ = astCreate(AST_NOT   , NULL, $2  , NULL, NULL, NULL); }
    | '(' expr ')'           { $$ = astCreate(AST_OPEN_BR,NULL, $2  , NULL, NULL, NULL); }
    ;

%%

int yyerror() {
    fprintf(stderr, "Syntax error at line %d.\n", getLineNumber());
    syntaxErrors++;
    // exit(3);
    return 3;
} 

void reportSyntaxErrors(const char *str) {
    fprintf(stderr, "\t%s\n", str);
    syntaxErrorsMessages++;
} 

int getSyntaxErrors() {
    return syntaxErrors;
}
