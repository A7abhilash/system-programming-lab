#include<stdio.h>
#include<sys/types.h>                            
#include<sys/wait.h>                            
#include<unistd.h>

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
        printf("Child process.\n");
        sleep(5);
        currentPid=getpid();
        parentPid=getppid();
        printf("Current pid: %d & Parent pid: %d\n",currentPid,parentPid);
    }else{
        wait(NULL);
        printf("Parent process.\n");
        currentPid=getpid();
        parentPid=getppid();
        printf("Current pid: %d & Parent pid: %d\n",currentPid,parentPid);
        printf("Newly created process pid: %d\n",pid);
    }

    return 0;
}

/*
    Before fork: Proccess id: 121
    Child process.
        Current pid: 122 & Parent pid: 121
    Parent process.
        Current pid: 121 & Parent pid: 22
        Newly created process pid: 122
*/