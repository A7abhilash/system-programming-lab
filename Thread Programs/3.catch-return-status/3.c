#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int sum=0, a[5]={1,2,3,4,5};
void *res;

void * add(void *args){
	printf("Inside add func.\n");

	int i;
	int *arr = args;

	for (i = 0; i < 5;i++){
		sum += arr[i];
	}

	pthread_exit("Sum Calculated");
}

int main(){
	pthread_t T;
	pthread_attr_t attr; //set of thread attributes
	pthread_attr_init(&attr); //get the default attributes

	pthread_create(&T, &attr, add, (void*)a);//to create a new thread
	//(&id,&attr,func,args)

	pthread_join(T, &res);

	printf("Inside main thread.\n");
	printf("Sum: %d\n", sum);
	printf("Child thread returned status: %s\n",(char*)res);

	return 0;
}

/*
	Inside add func.
	Inside main thread.
	Sum: 15
	Child thread returned status: Sum Calculated
*/