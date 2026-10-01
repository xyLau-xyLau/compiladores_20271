#include <stdio.h>

#include "scanner.h"

extern int yylex(void);
extern char *yytext;

int main(void)
{	
	int token;
	while ((token = yylex()) != TOK_EOF) {
		if (token == TOK_ERROR || token == TOK_ERROR_UNCLOSED_COMMENT){
			continue;
		} else {
			printf("[%s:%s]\n", scanner_token_name(token), yytext);
		}
	}
	return 0;
}

const char *scanner_token_name(int token)
{
	switch (token) {
		case TOK_EOF: return "EOF";
		case TOK_ERROR: return "ERROR";

		case TOK_KW_INT: return "KW_INT";
		case TOK_KW_FLOAT: return "KW_FLOAT";
		case TOK_KW_DOUBLE: return "KW_DOUBLE";
		case TOK_KW_CHAR: return "KW_CHAR";
		case TOK_KW_VOID: return "KW_VOID";
		case TOK_KW_IF: return "KW_IF";
		case TOK_KW_ELSE: return "KW_ELSE";
		case TOK_KW_WHILE: return "KW_WHILE";
		case TOK_KW_FOR: return "KW_FOR";
		case TOK_KW_FOREACH: return "KW_FOREACH";
		case TOK_KW_RETURN: return "KW_RETURN";
		case TOK_KW_BREAK: return "KW_BREAK";
		case TOK_KW_CONTINUE: return "KW_CONTINUE";
		case TOK_KW_FUN: return "KW_FUN";
		case TOK_KW_IN: return "KW_IN";
		case TOK_KW_OUT: return "KW_OUT";
		case TOK_KW_CONST: return "KW_CONST";
		case TOK_KW_MATCH: return "KW_WATCH";
		case TOK_KW_DO: return "KW_DO";
		case TOK_KW_TRUE: return "KW_TRUE";
		case TOK_KW_FALSE: return "KW_FALSE";
		case TOK_KW_STR: return "KW_STR";
		case TOK_KW_PRINT: return "KW_PRINT";
		case TOK_KW_READ: return "KW_READ";
		case TOK_KW_EXIT: return "KW_EXIT";
		case TOK_KW_SYSTEM: return "KW_SYSTEM";

		case TOK_IDENTIFIER: return "IDENTIFIER";
		case TOK_INT_LITERAL: return "INT_LITERAL";
		case TOK_FLOAT_LITERAL: return "FLOAT_LITERAL";
		case TOK_STRING_LITERAL: return "STRING_LITERAL";
		case TOK_CHAR_LITERAL: return "CHAR_LITERAL";

		case TOK_LEFT_SHIFT: return "LEFT_SHIFT";
		case TOK_RIGHT_SHIFT: return "RIGHT_SHIFT";
		case TOK_INC: return "INC";
		case TOK_DEC: return "DEC";
		case TOK_PLUS_ASSIGN: return "PLUS_ASSIGN";
		case TOK_MINUS_ASSIGN: return "MINUS_ASSIGN";
		case TOK_MUL_ASSIGN: return "MUL_ASSIGN";
		case TOK_DIV_ASSIGN: return "DIV_ASSIGN";
		case TOK_MOD_ASSIGN: return "MOD_ASSIGN";
		case TOK_LEFT_ASSIGN: return "LEFT_ASSIGN";
		case TOK_RIGHT_ASSIGN: return "RIGHT_ASSIGN";

		case TOK_EQ: return "EQ";
		case TOK_NEQ: return "NEQ";
		case TOK_LT: return "LT";
		case TOK_LE: return "LE";
		case TOK_GT: return "GT";
		case TOK_GE: return "GE";

		case TOK_AND: return "AND";
		case TOK_OR: return "OR";
		case TOK_NOT: return "NOT";

		case TOK_PLUS: return "PLUS";
		case TOK_MINUS: return "MINUS";
		case TOK_MUL: return "MUL";
		case TOK_DIV: return "DIV";
		case TOK_MOD: return "MOD";

		case TOK_LPAREN: return "LPAREN";
		case TOK_RPAREN: return "RPAREN";
		case TOK_LBRACE: return "LBRACE";
		case TOK_RBRACE: return "RBRACE";
		case TOK_LBRACKET: return "LBRACKET";
		case TOK_RBRACKET: return "RBRACKET";
		case TOK_COMMA: return "COMMA";
		case TOK_SEMICOLON: return "SEMICOLON";
		case TOK_COLON: return "COLON";
		case TOK_ERROR_UNCLOSED_COMMENT: return "FIN DE ARCHIVO, COMENTARIO ABIERTO";
		default: return "UNKNOWN";
	}
}