#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/stat.h>

int main(){
    void *psm;
    char buf[30];

    int shmid=shm_open("OS", O_RDONLY, 0666);
    ftruncate(shmid,1024);
    psm=mmap(0,1024,PROT_READ,MAP_SHARED,shmid,0);

    printf("Key/ID/fs of the shared memory: %d\n",shmid);
    printf("Shared memory for consumer is attached at: %p\n",psm);

    printf("Data in shared memory:\n");
    printf("%s\n",(char*)psm);
    shm_unlink("OS");

    return 0;
}

/*
    Key/ID/fs of the shared memory: 3
    Shared memory for consumer is attached at: 0x7f57261c3000
    Data in shared memory:
    Data for shared memory
*/