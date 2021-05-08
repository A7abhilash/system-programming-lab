#include<stdio.h>
#include<sys/types.h>                            
#include<unistd.h>
#include<stdlib.h>                            

int main(){
    pid_t pid, currentPid, parentPid;
    pid = getpid();
    printf("Before fork: Proccess id: %d\n",pid);
    
    pid=fork();
    
    if(pid<0){
        printf("Forking failed...\n");
        return 1;
    }
    if(pid==0){
        sleep(5);
        printf("Child process.\n");
        currentPid=getpid();
        parentPid=getppid();
        printf("Current pid: %d & Parent pid: %d\n",currentPid,parentPid);
        exit(0);
    }else{
        printf("Parent process.\n");
        currentPid=getpid();
        parentPid=getppid();
        printf("Current pid: %d & Parent pid: %d\n",currentPid,parentPid);
        printf("Newly created process pid: %d\n",pid);
        exit(0);
    }

    return 0;
}

/*
    Before fork: Proccess id: 129
    Parent process.
        Child pid: 129 & Parent pid: 22
        Newly created process pid: 130

    ~/1$ Child process.
        Child pid: 130 & Parent pid: 1
*/