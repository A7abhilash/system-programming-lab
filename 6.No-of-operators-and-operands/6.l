%{
        int operandCount=0, operatorCount=0;
%}

chars [a-zA-Z]
digit [0-9]

us _

id {chars}({chars}|{digit}|{us})*
number {digit}+

operand ({id}|{number})
operator ("+"|"-"|"/"|"*"|"^")

%%
{operand}       operandCount++;

{operator}      operatorCount++;

(.|\n) ;

%%

int main(){
        printf("Enter an arithmetic expresiion: ");
        yylex();

        printf("Operands count: %d\nOPerators count: %d\n",operandCount,operatorCount);
}