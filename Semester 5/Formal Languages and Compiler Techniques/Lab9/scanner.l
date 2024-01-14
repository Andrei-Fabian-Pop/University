%{
#include <stdio.h>
#include <string.h>
int lines = 0;
%}

%option noyywrap
%option caseless

DIGIT [0-9]
NON_ZERO_DIGIT [1-9]
INT_CONSTANT [-]?{NON_ZERO_DIGIT}{DIGIT}*|0
LETTER [a-zA-Z_]
STRING_CONSTANT \"({LETTER}|{DIGIT})*\"
IDENTIFIER {LETTER}({LETTER}|{DIGIT})*
BAD_IDENTIFIER ({DIGIT})+({LETTER})+({LETTER}|{DIGIT})*
INCLUDE #include[ ]+\".*\"

%%

"int" 				{ printf("%s - Reserved word.\n", yytext); return INT; }
"char" 				{ printf("%s - Reserved word.\n", yytext); return CHAR; }
"return" 			{ printf("%s - Reserved word.\n", yytext); return RETURN; }
"for" 				{ printf("%s - Reserved word.\n", yytext); return FOR; }
"while" 			{ printf("%s - Reserved word.\n", yytext); return WHILE; }
"if" 				{ printf("%s - Reserved word.\n", yytext); return IF; }
"else" 				{ printf("%s - Reserved word.\n", yytext); return ELSE; }
"print" 			{ printf("%s - Reserved word.\n", yytext); return PRINT; }
"read" 				{ printf("%s - Reserved word.\n", yytext); return READ; }

{INCLUDE}			{ printf("%s - Include directive.\n", yytext); return INCLIB; }
{IDENTIFIER}		{ printf("%s - Identifier.\n", yytext); return IDENTIFIER; }
{STRING_CONSTANT}	{ printf("%s - String Constant.\n", yytext); return STRCONST; }
{INT_CONSTANT}		{ printf("%s - Int Constant.\n", yytext); return INTCONST; }
{BAD_IDENTIFIER}	{ printf("%s - Bad Identifier.\n", yytext); return -1; }

"+" 				{ printf("%s - operator\n", yytext); return PLUS; }
"-" 				{ printf("%s - operator\n", yytext); return MINUS; }
"*" 				{ printf("%s - operator\n", yytext); return MUL; }
"/" 				{ printf("%s - operator\n", yytext); return DIV; }
"%" 				{ printf("%s - operator\n", yytext); return MOD; }
"=" 				{ printf("%s - operator\n", yytext); return EQ; }
">" 				{ printf("%s - operator\n", yytext); return GT; }
">=" 				{ printf("%s - operator\n", yytext); return GTE; }
"<" 				{ printf("%s - operator\n", yytext); return LT; }
"<=" 				{ printf("%s - operator\n", yytext); return LTE; }
"==" 				{ printf("%s - operator\n", yytext); return EQEQ; }
"!=" 				{ printf("%s - operator\n", yytext); return NEQ; }
"&&" 				{ printf("%s - operator\n", yytext); return AND; }
"||" 				{ printf("%s - operator\n", yytext); return OR; }

"," 				{ printf("%s - separator\n", yytext); return COMMA; }
";" 				{ printf("%s - separator\n", yytext); return SEMICOLON; }
"(" 				{ printf("%s - separator\n", yytext); return OPENPAR; }
")" 				{ printf("%s - separator\n", yytext); return CLOSEPAR; }
"{" 				{ printf("%s - separator\n", yytext); return OPENCB; }
"}" 				{ printf("%s - separator\n", yytext); return CLOSECB; }
"[" 				{ printf("%s - separator\n", yytext); return OPENSB; }
"]" 				{ printf("%s - separator\n", yytext); return CLOSESB; }

[ \t]+ 				{}
[\n]+ 				{ ++lines; }
. 					{ printf("Error at token %s at line %d\n", yytext, lines); return -1; }

%%

