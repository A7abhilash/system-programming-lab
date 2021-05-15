#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

int i, j;

void * threadFunction(){
	printf("Inside thread func.\n");
	for (j = 1; j <= 5;j++){
		printf("j = %d\n", j);
		sleep(1);
	}
}

int main(){
	pthread_t T;
	pthread_create(&T, NULL, threadFunction, NULL);//to create a new thread
	//(&id,&attr,func,args)

	//pthread_join(T,NULL); //Main thread waits until child thread finishes
	
	printf("Inside main thread.\n");
	for (i = 11; i <= 15;i++){
		printf("i = %d\n", i);
		sleep(1);
	}

	return 0;
}

/*
	Inside main thread.
	i = 11
	Inside thread func.
	j = 1
	i = 12
	j = 2
	i = 13
	j = 3
	i = 14
	j = 4
	i = 15
	j = 5
*/