%{
	int vowels=0,consonants=0;
%}

%%
[aeiouAEIOU]	vowels++;
[a-z A-Z]	consonants++;
%%

int main(){
	yylex();
	printf("No. of vowels: %d\n",vowels);
	printf("No. of consonants: %d\n",consonants);
	return 0;
}
