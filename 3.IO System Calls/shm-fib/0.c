/*	Write a program to generate and print Fibonacci series with the following
requirements:
- Parent program should create a child and distribute the task of generating
Fibonacci nos to its child.
- The code for generating Fibonacci no. should reside in different program.
- Child should write the generated Fibonacci sequence to a shared memory.
- Parent process has to print by retrieving the Fibonacci sequence from the
shared memory.
a) Implement the above using shm_open and mmap
b) Implement the above using shmget and shmat
Note: Shared object should be removed at the end in the program .	*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/mman.h>

int main(int argsCount,char *args[]){
	if(argsCount==1){
		printf("No args provided\n");
		return 0;
	}

	const int SIZE = 4096;
	int i;

	sscanf(args[1], "%d", &i);

	pid_t pid = fork();

	if(pid==0){
		printf("Child process\n");
		execlp("./fib", "fib", args[1], NULL);
	}else if(pid>0){
		wait(NULL);
		printf("Inside parent process\n");

		int shm_fd=shm_open("OS",O_RDONLY,0666);
		void *ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
		printf("Parent printing the fib series: %s\n", (char *)ptr);

		shm_unlink("OS");
	}

	return 0;
}

/*	./a.out 8
	Child process
	Fib program executed...
	Inside parent process
	Parent printing the fib series: 0 1 1 2 3 5 8 13 
*/