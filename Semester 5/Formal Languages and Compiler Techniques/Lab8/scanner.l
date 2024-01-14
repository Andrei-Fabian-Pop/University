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

%%

"#include"			{ printf("%s - Include directive.\n", yytext); }
"<".*">"			{ printf("%s - Angle bracket file name.\n", yytext); }

"int" 				{ printf("%s - Reserved word.\n", yytext); }
"char" 				{ printf("%s - Reserved word.\n", yytext); }
"return" 			{ printf("%s - Reserved word.\n", yytext); }
"for" 				{ printf("%s - Reserved word.\n", yytext); }
"while" 			{ printf("%s - Reserved word.\n", yytext); }
"if" 				{ printf("%s - Reserved word.\n", yytext); }
"else" 				{ printf("%s - Reserved word.\n", yytext); }
"print" 			{ printf("%s - Reserved word.\n", yytext); }
"read" 				{ printf("%s - Reserved word.\n", yytext); }

{IDENTIFIER}		{ printf("%s - Identifier.\n", yytext); }
{STRING_CONSTANT}	{ printf("%s - String Constant.\n", yytext); }
{INT_CONSTANT}		{ printf("%s - Int Constant.\n", yytext); }
{BAD_IDENTIFIER}	{ printf("%s - Bad Identifier.\n", yytext); return -1; }

"+" 				{ printf("%s - operator\n", yytext); }
"-" 				{ printf("%s - operator\n", yytext); }
"*" 				{ printf("%s - operator\n", yytext); }
"/" 				{ printf("%s - operator\n", yytext); }
"%" 				{ printf("%s - operator\n", yytext); }
"=" 				{ printf("%s - operator\n", yytext); }
">" 				{ printf("%s - operator\n", yytext); }
">=" 				{ printf("%s - operator\n", yytext); }
"<" 				{ printf("%s - operator\n", yytext); }
"<=" 				{ printf("%s - operator\n", yytext); }
"==" 				{ printf("%s - operator\n", yytext); }
"!=" 				{ printf("%s - operator\n", yytext); }
"&&" 				{ printf("%s - operator\n", yytext); }
"||" 				{ printf("%s - operator\n", yytext); }

"," 				{ printf("%s - separator\n", yytext); }
";" 				{ printf("%s - separator\n", yytext); }
"(" 				{ printf("%s - separator\n", yytext); }
")" 				{ printf("%s - separator\n", yytext); }
"{" 				{ printf("%s - separator\n", yytext); }
"}" 				{ printf("%s - separator\n", yytext); }
"[" 				{ printf("%s - separator\n", yytext); }
"]" 				{ printf("%s - separator\n", yytext); }

[ \t]+ 				{}
[\n]+ 				{ ++lines; }
. 					{ printf("Error at token %s at line %d\n", yytext, lines); return -1; }

%%


int main(int argc, char** argv) {
	if (argc == 1) {
		yyin = stdin;
	} else if (argc == 2) {
		yyin = fopen(argv[1], "r");
	} else {
		printf("Error, invalid arguments.\n");
		return -1;
	}

	yylex();
	printf("Program finished gracefully.\n");
	return 0;
}

