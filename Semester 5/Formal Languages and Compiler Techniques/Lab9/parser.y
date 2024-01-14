%{
#include <stdio.h>
#include <stdlib.h>

#define YYDEBUG 1
%}

%token INT;
%token CHAR;
%token RETURN;
%token FOR;
%token WHILE;
%token IF;
%token ELSE;
%token PRINT;
%token READ;

%token INCLIB;
%token IDENTIFIER;
%token STRCONST;
%token INTCONST;

%token PLUS;
%token MINUS;
%token MUL;
%token DIV;
%token MOD;
%token EQ;
%token GT;
%token GTE;
%token LT;
%token LTE;
%token EQEQ;
%token NEQ;
%token AND;
%token OR;

%token COMMA;
%token SEMICOLON;
%token OPENPAR;
%token CLOSEPAR;
%token OPENCB;
%token CLOSECB;
%token OPENSB;
%token CLOSESB;

%start Program

%%
Program : Statement SEMICOLON Program {printf("Program -> Statement ; Program\n");} 
		| Statement SEMICOLON {printf("Program -> Statement ;\n");} ;
Statement : VarStatement {printf("Statement -> VarStatement\n");} 
		  | AssignStatement {printf("Statement -> AssignStatement\n");} 
		  | IfStatement {printf("Statement -> IfStatement\n");} 
		  | WhileStatement {printf("Statement -> WhileStatement\n");} 
		  | ReturnStatement {printf("Statement -> ReturnStatement\n");} 
		  | FunctionCallStatement {printf("Statement -> FunctionCallStatement\n");} ;
VarStatement : INT IdentifierList {printf("IntStatement -> int IdentifierList\n");} 
			 | CHAR IdentifierList {printf("CharStatement -> char IdentifierList\n");} ;
IdentifierList : DeclExpression {printf("IdentifierList -> DeclExpression \n");} 
			   | DeclExpression COMMA IdentifierList {printf("IdentifierList -> DeclExpression , IdentifierList\n");} ;
DeclExpression : IDENTIFIER {printf("DeclExpression -> IDENTIFIER \n");} 
			   | IDENTIFIER EQ Expression {printf("DeclExpression -> IDENTIFIER = Expression \n");} ;
Expression : IntExpression {printf("Expression -> IntExpression \n");} 
		   | StringExpression {printf("Expression -> StringExpression \n");} ;
MathematicalOperator : PLUS {printf("MathematicalOperator -> + \n");} 
					 | MINUS {printf("MathematicalOperator -> - \n");} 
					 | MUL {printf("MathematicalOperator -> * \n");} 
					 | DIV {printf("MathematicalOperator -> / \n");} 
					 | MOD {printf("MathematicalOperator -> % \n");} ;
IntExpression : INTCONST {printf("IntExpression -> INTCONST \n");} 
			  | IDENTIFIER {printf("IntExpression -> IDENTIFIER \n");} 
			  | FunctionCallStatement {printf("IntExpression -> FunctionCallStatement \n");} 
			  | IntExpression MathematicalOperator IntExpression {printf("IntExpression -> IntExpression MathematicalOperator IntExpression \n");} 
			  | OPENPAR IntExpression MathematicalOperator IntExpression CLOSEPAR {printf("IntExp -> ( IntExp MathOp IntExp ) \n");} ;
StringExpression : STRCONST {printf("StringExpression -> STRING_CONSTANT \n");} ;
ExpressionList : Expression {printf("ExpressionList -> Expression \n");} 
			   | Expression COMMA ExpressionList {printf("ExpressionList -> Expression , ExpressionList \n");} ;
AssignStatement : IDENTIFIER EQ Expression {printf("AssignStatement -> IDENTIFIER = Expression \n");} ;
IfStatement : IF OPENPAR Condition CLOSEPAR OPENCB Program CLOSECB {printf("IfStatement -> if ( Condition ) { Program } \n");} 
			| IF OPENPAR Condition CLOSEPAR OPENCB Program CLOSECB ELSE OPENCB Program CLOSECB {printf("IfElseStatement -> if ( Condition ) { Program } else { Program } \n");} ;
RelationalOperator : EQEQ {printf("RelationalOperator -> ==\n");} 
				   | LT {printf("RelationalOperator -> <\n");} 
				   | LTE {printf("RelationalOperator -> <=\n");} 
				   | GT {printf("RelationalOperator -> >\n");} 
				   | GTE {printf("RelationalOperator -> >=\n");} ;
Condition : Expression RelationalOperator Expression {printf("Condition -> Expression RelationalOperator Expression\n");} 
		  | Expression RelationalOperator Expression AND Expression RelationalOperator Expression {printf("Condition -> Expression RelationalOperator Expression && Expression RelationalOperator Expression\n");}
		  | Expression RelationalOperator Expression OR Expression RelationalOperator Expression {printf("Condition -> Expression RelationalOperator Expression || Expression RelationalOperator Expression\n");} ;
WhileStatement : WHILE OPENPAR Condition CLOSEPAR OPENCB Program CLOSECB {printf("WhileStatement -> while ( Condition ) { Program }\n");} ;
ReturnStatement : RETURN Expression {printf("ReturnStatement -> return Expression\n");} ;
FunctionCallStatement : FunctionName OPENPAR ExpressionList CLOSEPAR {printf("FunctionCallStatement -> FunctionName ( ExpressionList )\n");} 
					  | FunctionName OPENPAR CLOSEPAR {printf("FunctionCallStatement -> FunctionName ( )\n");} ;
FunctionName : PRINT {printf("FunctionName -> print\n");} 
			 | READ {printf("FunctionName -> read\n");} ;
%%

void yyerror(const char* e) {
	fprintf(stderr, "Parse error: %s\n", e);
}

extern FILE* yyin;

int main(int argc, char** argv) {
	if (argc == 1) {
		yyin = stdin;
	} else if (argc == 2) {
		yyin = fopen(argv[1], "r");
	} else {
		printf("Error, invalid arguments.\n");
	}

	yyparse();
	printf("Program finished gracefully.\n");
	return 0;
}

#include "lex.yy.c"
