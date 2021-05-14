#include<stdio.h>

int main(int argsCount,char *args[]){
	if(argsCount==1){
		printf("No args provided\n");
		return 0;
	}

	char ch;
	FILE *fp = fopen(args[1], "r");

	if(fp==NULL){
		printf("File doesn't exist\n");
		return 0;
	}

	while((ch=fgetc(fp))!=EOF){
		printf("%c", ch);
	}
	printf("\n");

	fclose(fp);

	return 0;
}

/*	./a.out input.txt
	This is an input text.
*/