#include <stdio.h>
#include<stdlib.h>
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

	int shm_fd = shm_open("OS", O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, SIZE);
	void *ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

	int a = 0, b = 1, c, n = atoi(args[1]);

	sprintf(ptr, "%d ", a);
	ptr += strlen(ptr);
	sprintf(ptr, "%d ", b);
	ptr += strlen(ptr);

	for (int i = 2; i < n; i++)
	{
		c = a + b;
		sprintf(ptr, "%d ", c);
		a = b;
		b = c;
		ptr += strlen(ptr);
	}

	printf("Fib program executed...\n");

	return 0;
}
