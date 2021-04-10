%{
        int valid=1, top=-1, i=0, j=0;
        int operandCount=0, operatorCount=0;
        char operands[10][10], operators[10][10], stk[50];
%}

chars [a-zA-Z]
digit [0-9]

us _

id {chars}({chars}|{digit}|{us})*
number {digit}+

operand ({id}|{number})
operator ("+"|"-"|"/"|"*"|"^")

%%

"(" {stk[++top]='(';}
")" {
                if(stk[top]!='(' | operandCount-operatorCount!=1)
                        valid=0;
                else{
                        top--;
                        operandCount=1, operatorCount=0;
                }
        }
{operand}       {
                                operandCount++;
                                strcpy(operands[i++],yytext);
                        }
{operator}      {
                                operatorCount++;
                                strcpy(operators[j++],yytext);
                        }
(.|\n) ;

%%

int yywrap(){return 1;}

int main(){
        printf("Enter an arithmetic expresiion: ");
        yylex();

        printf("Operands count: %d\nOPerators count: %d\n",i,j);

        printf("Operands: ");
        for(int k=0;k<=i;k++)
                printf("%s ",operands[k]);

        printf("\nOperators: ");
        for(int k=0;k<=j;k++)
                printf("%s ",operators[k]);

        printf("\n");

        if(valid==1 && top==-1 && i-j==1) printf("Valid Expression\n");
        else printf("Invalid Expression\n");
}