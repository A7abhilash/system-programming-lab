#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>

int main(){
    void *psm;

    int shmid=shmget((key_t)1122, 1024, 0666 | IPC_CREAT);

    psm=shmat(shmid,NULL,0666);

    printf("Fib Series in shared memory: %s\n",(char*)psm);

    shmdt(psm);

    return 0;
}

// Fib Series in shared memory: 0 1 1 2 3 5 8 13 