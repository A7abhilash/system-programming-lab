%{
#include<stdio.h>
%}

%token A CO ZA ER ERR

%%
start:CO {printf("Valid declaration");}
%%

void yyerror(const char *str){printf("error");}

int yywrap(){return 0;}

main(){
    yyparse();
}