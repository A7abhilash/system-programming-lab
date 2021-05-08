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
    int shmid=shmget((key_t)1122, 1024, 0666);
    printf("Key of the shared memory: %d\n",shmid);

    //To attach shared memory segment to and address space
    psm=shmat(shmid,NULL,0666);
    printf("Shared memory for consumer is attached at: %p\n",psm);

    printf("Data in shared memory:\n");
    printf("%s\n",(char*)psm);

    //shmctl performs the control operation specified by the command.
    //IPC_RMID marks the segment to be destroyed
    shmctl(shmid,IPC_RMID,NULL);

    return 0;
}

/*
    Key of the shared memory: 0
    Shared memory for consumer is attached at: 0x7fc7e1b57000
    Data in shared memory:
    Some other new data for shm
*/