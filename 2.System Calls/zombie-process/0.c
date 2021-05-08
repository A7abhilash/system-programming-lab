#include<stdio.h>
#include<sys/types.h>                            
#include<unistd.h>
#include<stdlib.h>                            

int main(){
    pid_t pid, childPid, parentPid;
    pid = getpid();
    printf("Before fork: Proccess id: %d\n",pid);
    
    pid=fork();
    
    if(pid<0){
        printf("Forking failed...\n");
        return 1;
    }
    if(pid==0){
        printf("Child process.\n");
        childPid=getpid();
        parentPid=getppid();
        printf("Child pid: %d & Parent pid: %d\n",childPid,parentPid);
        exit(0);
    }else{
        sleep(5);
        printf("Parent process.\n");
        childPid=getpid();
        parentPid=getppid();
        printf("Child pid: %d & Parent pid: %d\n",childPid,parentPid);
        printf("Newly created process pid: %d\n",pid);
    }

    return 0;
}

/*
    Before fork: Proccess id: 136
    Child process.
        Child pid: 137 & Parent pid: 136
    Parent process.
        Child pid: 136 & Parent pid: 22
        Newly created process pid: 137
*/