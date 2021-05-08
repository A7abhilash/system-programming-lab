#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>

int main(){
    void *psm;
    char buf[30];

    //To get the id of shared memory
    int shmid=shmget((key_t)1122, 1024, 0666 | IPC_CREAT);
    printf("Key of the shared memory: %d\n",shmid);

    //To attach shared memory segment to and address space
    psm=shmat(shmid,NULL,0666);
    printf("Shared memory for producer is attached at: %p\n",psm);

    printf("Enter some data to write to shared memory:\n");
    read(0,buf,30);
    sprintf(psm,"%s",buf);

    //To detach the shared memory segment from the address space of the calling process
    shmdt(psm);

    return 0;
}

/*
    Key of the shared memory: 0
    Shared memory for producer is attached at: 0x7fb3b6182000
    Enter some data to write to shared memory:
    Some other new data for shm
*/