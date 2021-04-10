%{
        int flag=0;
%}

%%
[_a-zA-Z_][a-zA-Z0-9_]* flag=1;
. flag=0;
%%

int main(){
        yylex();
        if(flag) printf("Valid\n");
        else printf("Invalid\n");
        return 0;
}