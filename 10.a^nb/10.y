%{
#include<stdio.h>
%}

%token A CO ZA ER ERR

%%
start:CO {printf("VAlid declaration");}
%%

void yyerror(const char *str){printf("error");}

int yywrap(){return 0;}

main(){
    yyparse();
}