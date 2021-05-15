#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>

int main(int argsCount,char* args[]){
    void *psm;
    char buf[30];

    int shmid=shmget((key_t)1122, 1024, 0666 | IPC_CREAT);

    psm=shmat(shmid,NULL,0666);

	int a = 0, b = 1, c, n = atoi(args[1]);
	int arr[n];

	arr[0] = a;
	arr[1] = b;

	for (int i = 2; i < n; i++)
	{
		c = a + b;
		arr[i] = c;
		a = b;
		b = c;
	}

	for (int i = 0; i < n;i++){
		sprintf(psm, "%d ", arr[i]);
		psm += strlen(psm);
	}

    shmdt(psm);

    return 0;
}