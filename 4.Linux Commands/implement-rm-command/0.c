#include<stdio.h>
#include<fcntl.h>

void main(){
	char filename[20];

	printf("Enter the filename to be deleted: ");
	scanf("%s", filename);

	if(remove(filename)==0){
		printf("File deleted\n");
	}else{
		printf("File doesn't exist\n");
	}
}

/*
	Enter the filename to be deleted: a.out
	File deleted
*/