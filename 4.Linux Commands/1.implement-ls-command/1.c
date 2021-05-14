#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<stdlib.h>

void main(int argsCount,char *args[]){
	if(argsCount==1){
		printf("No args provided\n");
		return;
	}

	DIR *dp;
	struct dirent *dirp;

	if((dp=opendir(args[1]))==NULL){
		printf("Directory doesn't exist!\n");
	}else{
		while((dirp=readdir(dp))!=NULL){
			printf("%s\n", dirp->d_name);
		}
		closedir(dp);
	}
}

/*
	.
	..
	file1
	file2
	childfolder1
*/