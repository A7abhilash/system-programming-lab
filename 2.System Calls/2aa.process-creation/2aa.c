#include<stdio.h>
#include<sys/types.h>                            
#include<unistd.h>

int main(){
    printf("Before forking...\n");
    fork();
    printf("After forking...\n");
    
    return 0;
}

/*
    Before forking...
    After forking...
    After forking...
*/