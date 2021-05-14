#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int sum=0, product=1;

void * add(void *args){
	printf("Inside add func.\n");

	int i, n;
	n = atoi(args);//ascii to integer

	for (i = 1; i <= n;i++){
		sum += i;
	}
	printf("Add func completed\n");
}

void * mul(void *args){
	printf("Inside mul func.\n");
	
	int i, n;
	n = atoi(args);//ascii to integer

	for (i = 2; i <= n;i++){
		product *= i;
	}
	printf("Mul func completed\n");
}

int main(int argsCount,char* args[]){
	if(argsCount==1){
		printf("No args provided\n");
		return 0;
	}

	pthread_t T1,T2;
	pthread_attr_t attr; //set of thread attributes
	pthread_attr_init(&attr); //get the default attributes

	pthread_create(&T1, &attr, add, args[1]);//to create a new thread
	pthread_create(&T2, &attr, mul, args[1]);//to create a new thread
	//(&id,&attr,func,args)

	pthread_join(T1, NULL);
	pthread_join(T2, NULL);

	printf("Inside main thread.\n");
	printf("Sum: %d\n", sum);
	printf("Product: %d\n", product);

	return 0;
}

/*
	Inside add func.
	Add func completed
	Inside mul func.
	Mul func completed
	Inside main thread.
	Sum: 15
	Product: 120
*/