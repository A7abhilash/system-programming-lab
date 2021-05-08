#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

int main(){
    char buf[30];
    int n, fd;

    fd=open("input.text",O_RDWR);
    printf("File descriptor is %d\n",fd);

    if(fd==-1){
        printf("Error\n");
    }else{
        n=read(fd,buf,30);
        write(1,buf,30);
        printf("\n");

        lseek(fd,5,SEEK_CUR);
        n=read(fd,buf,30);
        write(1,buf,30);
        printf("\n");

        lseek(fd,10,SEEK_SET);
        n=read(fd,buf,30);
        write(1,buf,30);
        printf("\n");

        lseek(fd,-5,SEEK_CUR);
        n=read(fd,buf,30);
        write(1,buf,30);
        printf("\n");

        lseek(fd,-10,SEEK_END);
        n=read(fd,buf,30);
        write(1,buf,30);
        printf("\n");
    }

    return 0;
}