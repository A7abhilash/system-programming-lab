#include<stdio.h>
#include<sys/types.h>                            
#include<unistd.h>
#include<fcntl.h>

int main(){
    char buf[30];
    int n,fd1,fd2;

    fd1=open("input.txt",O_RDONLY);
    fd2=open("output.txt",O_WRONLY);
    // printf("File Descriptor: %d\n",fd1);

    if(fd1==-1 || fd2==-1){
        printf("Error\n");
    }else{
        n=read(fd1,buf,30);
        printf("n=%d\n",n);
        write(fd2,buf,n);
    }

    return 0;
}