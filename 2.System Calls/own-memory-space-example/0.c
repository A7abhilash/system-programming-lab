#include<stdio.h>
#include<sys/types.h>                            
#include<unistd.h>

int main(){
    pid_t pid, childPid, parentPid;
    pid = getpid();
    printf("Before fork: Proccess id: %d\n",pid);
    
    int i=10;
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
        i+=10;
        printf("i in child: %d\n",i);
    }else{
        printf("Parent process.\n");
        childPid=getpid();
        parentPid=getppid();
        printf("Child pid: %d & Parent pid: %d\n",childPid,parentPid);
        printf("Newly created process pid: %d\n",pid);
        i+=20;
        printf("i in parent: %d\n",i);
    }

    return 0;
}

/*
    Before fork: Proccess id: 166
    Parent process.
        Child pid: 166 & Parent pid: 22
        Newly created process pid: 167
        i in parent: 30
    Child process.
        Child pid: 167 & Parent pid: 1
        i in child: 20
*/