#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/stat.h>

int main(){
    void *psm;
    char buf[30];

    int shmid=shm_open("OS", O_CREAT | O_RDWR, 0666);
    ftruncate(shmid,1024);
    psm=mmap(0,1024,PROT_WRITE,MAP_SHARED,shmid,0);

    printf("Key/ID/fd of the shared memory: %d\n",shmid);
    printf("Shared memory is attached at: %p\n",psm);

    printf("Enter some data to write to shared memory:\n");
    read(0,buf,30);
    sprintf(psm,"%s",buf);

    return 0;
}

/*
    Key/ID/fd of the shared memory: 3
    Shared memory is attached at: 0x7f0c0e239000
    Enter some data to write to shared memory:
    Data for shared memory
*/