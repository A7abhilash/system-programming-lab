%{
	#include<stdio.h>
	#include<stdlib.h>
	
	int yylex();
	void yyerror(char *msg);
%}

%token A B NL

%%
start: AN B NL {printf("String accepted\n"); exit(0);}
	;
AN: A AN
	|
	;
%%

void yyerror(char *msg) {
	printf("String rejected\n");
	exit(0);
}

int main() {
	printf("Enter string of a's and b's:\n");
	yyparse();
	return 0;
}
