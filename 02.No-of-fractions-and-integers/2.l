%{
        int nint=0,pint=0,nfrac=0,pfrac=0;
%}

%%
([0-9]+)        pint++;
-([0-9]+)       nint++;
([0-9]*\.[0-9]+)        pfrac++;
-([0-9]*\.[0-9]+)       nfrac++;
%%

int main(){
        yylex();
        printf("No. of positive integers: %d\n",pint);
        printf("No. of negative integers: %d\n",nint);
        printf("No. of positive fractions: %d\n",pfrac);
        printf("No. of negative fractions: %d\n",nfrac);
        return 0;
}