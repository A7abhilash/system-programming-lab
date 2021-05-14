#include<stdio.h>
#include<string.h>

void main(){
	char filename[10], pattern[10], temp[200];
	FILE *fp;

	printf("Enter the filname: ");
	scanf("%s", filename);

	printf("Enter the pattern to be searched: ");
	scanf("%s", pattern);

	fp = fopen(filename, "r");

	while(!feof(fp)){
		fgets(temp, 1000, fp);
		if(strstr(temp,pattern)){
			printf("%s ", temp);
		}
	}

	fclose(fp);
}

/* Searched "fp" in same program
	FILE *fp;
	fp = fopen(filename, "r");
	while(!feof(fp)){
		fgets(temp, 1000, fp);
	fclose(fp);
*/