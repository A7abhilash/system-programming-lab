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
cs4a1@ubuntu02:~/A7/system_lab/cd3$ cd ..
cs4a1@ubuntu02:~/A7/system_lab$ cd cd4
cs4a1@ubuntu02:~/A7/system_lab/cd4$ cat 4.l

%{
        int valid = 1;
%}

digit [0-9]
alpha [a-zA-Z]
newline \n
ws \n|" "|\t
wss {ws}*

define "define "({alpha}|{digit}|\.)+" "({alpha}|{digit}|\.)+
include "include <"({alpha}|{digit}|\.)+">"
directive {include}|{define}
preprocessor "#"{directive}{newline}

literal ({digit})+
operator [\+\-\/\*\>\<]=?
term ({id}|{literal})

type ("int"|"char"|"float"|"double")\*?
id {alpha}({alpha}|{digit})*
id_list {id}|({id}({ws}*)","({ws}*))+{id}

vardecl {type}" "{id_list};

exprn ({term}{wss}{operator}{wss})*{term}
stmt {id}{wss}\={wss}{exprn};|{vardecl}

main {type}{ws}+"main()"{wss}\{({stmt}|{ws})*\}{wss}

%%

({preprocessor}|{ws})*({vardecl}|{ws})*{main} {}
. valid=0;

%%

int main(int argc, char* argv[]) {
        if (argc != 2) {
                printf("Usage: %s filename\n", argv[0]);
                exit(0);
        }

        yyin = fopen(argv[1], "r");

        yylex();

        if (valid) {
                printf("Valid C Program!\n");
        } else {
                printf("Invalid C Program!\n");
        }
}