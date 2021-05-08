#include<stdio.h>
#include<sys/types.h>                            
#include<sys/wait.h>
#include<unistd.h>

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
        execlp("/bin/ls","ls",NULL);
        printf("Won't be executed at all\n");//Executed only if error is there while executing execlp command...
    }else{
        wait(NULL);
        printf("Parent process.\n");
    }
    printf("Executed by parent only...\n");

    return 0;
}

/*
    Before fork: Proccess id: 86
    Child process.
    a.out  main.c  main.sh
    Parent process.
    Executed by parent only...
*/