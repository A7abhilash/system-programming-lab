#include<stdio.h>
#include<sys/types.h>                            
#include<unistd.h>

int main(){
    char buf[30];
    printf("Enter some text to display:\n");
    int n=read(0,buf,30);
    printf("n=%d\n",n);
    write(1,buf,n);

    return 0;
}

/*
    hello world
    n=12
    hello world
*/