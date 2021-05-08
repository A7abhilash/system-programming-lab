#include<stdio.h>
#include<sys/types.h>                            
#include<unistd.h>
#include<fcntl.h>

int main(){
    char buf[30];
    int n,fd;

    fd=open("create.txt",O_CREAT | O_RDWR);
    printf("File Descriptor: %d\n",fd);

    if(fd==-1){
        printf("Error\n");
    }else{
        printf("Enter some text to write onto file:\n");
        n=read(0,buf,30);
        printf("n=%d\n",n);
        write(fd,buf,n);
    }

    return 0;
}