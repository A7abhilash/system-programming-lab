#include<stdio.h>
#include<sys/types.h>                            
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
        currentPid=getpid();
        parentPid=getppid();
        printf("\tCurrent pid: %d & Parent pid: %d\n",currentPid,parentPid);
    }else{
        printf("Parent process.\n");
        currentPid=getpid();
        parentPid=getppid();
        printf("\tCurrent pid: %d & Parent pid: %d\n",currentPid,parentPid);
        printf("\tNewly created process pid: %d\n",pid);
    }

    return 0;
}

/*
    Before fork: Proccess id: 78
    Parent process.
        Current pid: 78 & Parent pid: 22
        Newly created process pid: 79
    Child process.
        Current pid: 79 & Parent pid: 78
*/