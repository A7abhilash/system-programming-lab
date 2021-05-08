#include<stdio.h>
#include<sys/types.h>                            
#include<unistd.h>
#include<fcntl.h>

int main(){
    char buf[30];
    int n,fd;

    fd=open("input.txt",O_RDONLY);
    printf("File Descriptor: %d\n",fd);

    if(fd==-1){
        printf("Error\n");
    }else{
        n=read(fd,buf,30);
        printf("n=%d\n",n);
        write(1,buf,n);
    }

    return 0;
}

/*
    File Descriptor: 3
    n=22
    This is an input text.
*/