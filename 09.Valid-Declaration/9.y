%{
#include<stdio.h>
%}

%token ID BUILTIN SC NL COMMA

%%
start:BUILTIN varlist SC NL {printf("valid");}
|
varlist:varlist COMMA ID|ID;
%%

void yyerror(const char *str){printf("error");}

int yywrap(){return 0;}

main(){
    yyparse();
}