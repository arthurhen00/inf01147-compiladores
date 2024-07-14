%{
// Compiladores - Etapa 3 - Marcelo Johann - 2024/01
// Arthur Hendges da Silva - 00332968
// 

    #include "hash_table.h"
    #include "ast.h"
    #include "y.tab.h"          // yacc parser.y -d     // --header-file=y.tab.h

    int running = 1;
    int lineCount = 1;

    hash_t *hashTable[HASH_SIZE];
%}

%x COMMENT

%%

"char" { return KW_CHAR; }
"int" { return KW_INT; }
"float" { return KW_FLOAT; }
"bool" { return KW_BOOL; }

"if" { return KW_IF; }
"else" { return KW_ELSE; }
"while" { return KW_WHILE; }
"read" { return KW_READ; }
"print" { return KW_PRINT; }
"return" { return KW_RETURN; }

[-,;:()\[\]{}=+*/%<>&|~] { return yytext[0]; }

"<=" { return OPERATOR_LE; }
">=" { return OPERATOR_GE; }
"==" { return OPERATOR_EQ; }
"!=" { return OPERATOR_DIF; }

[0-9]+ { 
    yylval.symbol = hashInsert(hashTable, yytext, LIT_INT);
    return LIT_INT;
}
['].['] { 
    yylval.symbol = hashInsert(hashTable, yytext, LIT_CHAR);
    return LIT_CHAR; 
}
[0-9]+[.][0-9]+ { 
    yylval.symbol = hashInsert(hashTable, yytext, LIT_REAL);
    return LIT_REAL;
}
[0-9]+[.][0-9]* { 
    yylval.symbol = hashInsert(hashTable, yytext, LIT_REAL);
    return LIT_REAL;
}
[0-9]*[.][0-9]+ { 
    yylval.symbol = hashInsert(hashTable, yytext, LIT_REAL);
    return LIT_REAL;
}
"false" { 
    yylval.symbol = hashInsert(hashTable, yytext, LIT_FALSE);
    return LIT_FALSE;
}
"true" { 
    yylval.symbol = hashInsert(hashTable, yytext, LIT_TRUE);
    return LIT_TRUE;
}
\"(\\.|[^"])*\" {
    yylval.symbol = hashInsert(hashTable, yytext, LIT_STRING);
    return LIT_STRING;
}

[a-zA-Z_]+[a-zA-Z0-9_]* { 
    yylval.symbol = hashInsert(hashTable, yytext, TK_IDENTIFIER);
    return TK_IDENTIFIER;
}

"\n" { lineCount++; }
[ \t]

"//".*
"/*" { BEGIN(COMMENT); }
<COMMENT>"*/" { BEGIN(INITIAL); }
<COMMENT>"\n" { lineCount++; }
<COMMENT>.

. { return TOKEN_ERROR; }

%%

int yywrap() {
    running = 0;
    return 1;
}

int getLineNumber(void) {
    return lineCount;
}

int isRunning(void) {
    return running;
}

void initMe(void) {
    hashInit(hashTable);
}