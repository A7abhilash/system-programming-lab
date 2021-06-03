%{
        int count=0;
%}

underscore _
digit [0-9]
alpha [a-zA-Z]

identifier ({underscore}|{alpha})({underscore}|{alpha}|{digit})*

%%
[^\na-zA-Z_]+[^ \n]*    ;


{identifier}    count++;

.|\n                    ;
%%

int yywrap(){return 1;}

int main(){
        yylex();

        printf("No. of identifiers: %d\n",count);

        return 1 ;
}