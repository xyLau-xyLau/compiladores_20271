%option noyywrap yylineno

%{
#include "scanner.h"

int profundidad = 0;
%}

%x COMMENT

ID          [a-zA-Z_][a-zA-Z0-9_]*
INT         [0-9]+
FLOAT       ({INT}\.[0-9]*([eE][+-]?{INT})?|{INT}[eE][+-]?{INT})
WS          [ \t\r\n]+

%%

"/*" { BEGIN(COMMENT); }

<COMMENT>{
    "/*"               {profundidad++;}
    "*"+"/"            {if (profundidad) 
                            profundidad--;
                        else
                            BEGIN(INITIAL);
                        }
    "*"+                ;
    [^/*\n]+            ;
    [/]                 ;
    \n                  ;
    <<EOF>>             {BEGIN(INITIAL);
                         printf("Error, Fin de archivo y comentario abierto\n");
                         return TOK_ERROR_UNCLOSED_COMMENT;}   
}
"//"[^\n]*             { /* comentario de línea */ }

{WS}                    { /* ignorar espacios */ }


"int"                   { return TOK_KW_INT; }
"float"                 { return TOK_KW_FLOAT; }
"double"                { return TOK_KW_DOUBLE; }
"char"                  { return TOK_KW_CHAR; }
"void"                  { return TOK_KW_VOID; }
"if"                    { return TOK_KW_IF; }
"else"                  { return TOK_KW_ELSE; }
"while"                 { return TOK_KW_WHILE; }
"foreach"               { return TOK_KW_FOREACH; }
"for"                   { return TOK_KW_FOR; }
"return"                { return TOK_KW_RETURN; }
"break"                 { return TOK_KW_BREAK; }
"continue"              { return TOK_KW_CONTINUE; }
"fun"                   { return TOK_KW_FUN; }
"in"                    { return TOK_KW_IN; }
"out"                   { return TOK_KW_OUT; }
"const"                 { return TOK_KW_CONST; }
"match"                 { return TOK_KW_MATCH; }
"do"                    { return TOK_KW_DO; }
"#t"                    { return TOK_KW_TRUE; }
"#f"                    { return TOK_KW_FALSE; }
"str"                   { return TOK_KW_STR; }
"print"                 { return TOK_KW_PRINT; }
"read"                  { return TOK_KW_READ; }
"exit"                  { return TOK_KW_EXIT; }
"system"                { return TOK_KW_SYSTEM; }

"++"                    { return TOK_INC; }
"--"                    { return TOK_DEC; }
"+="                    { return TOK_PLUS_ASSIGN; }
"-="                    { return TOK_MINUS_ASSIGN; }
"*="                    { return TOK_MUL_ASSIGN; }
"/="                    { return TOK_DIV_ASSIGN; }
"%="                    { return TOK_MOD_ASSIGN; }
"=="                    { return TOK_EQ; }
"!="                    { return TOK_NEQ; }
"&&"                    { return TOK_AND; }
"||"                    { return TOK_OR; }
"<<"                    { return TOK_LEFT_SHIFT; }
">>"                    { return TOK_RIGHT_SHIFT; }
"<="                    { return TOK_LE; }
">="                    { return TOK_GE; }
"<-"                    { return TOK_LEFT_ASSIGN; }
"->"                    { return TOK_RIGHT_ASSIGN; }
"<"                     { return TOK_LT; }
">"                     { return TOK_GT; }
"!"                     { return TOK_NOT; }
"+"                     { return TOK_PLUS; }
"-"                     { return TOK_MINUS; }
"*"                     { return TOK_MUL; }
"/"                     { return TOK_DIV; }
"%"                     { return TOK_MOD; }

"("                     { return TOK_LPAREN; }
")"                     { return TOK_RPAREN; }
"{"                     { return TOK_LBRACE; }
"}"                     { return TOK_RBRACE; }
"["                     { return TOK_LBRACKET; }
"]"                     { return TOK_RBRACKET; }
","                     { return TOK_COMMA; }
";"                     { return TOK_SEMICOLON; }
":"                     { return TOK_COLON; }


{FLOAT}                 { return TOK_FLOAT_LITERAL; }
{INT}                   { return TOK_INT_LITERAL; }
\'([^\\\n]|\\.)\'       { return TOK_CHAR_LITERAL; }
\"([^\\\n]|\\.)*\"      { return TOK_STRING_LITERAL; }
{INT}{ID}               { printf("Variables deben empezar con _ o letras: %s\n", yytext);
                          return TOK_ERROR; }
{ID}                    { return TOK_IDENTIFIER; }

<<EOF>>                 { return TOK_EOF; }

.                       { printf("Caracter no reconocido: %s\n", yytext);
                          return TOK_ERROR; }

%%
