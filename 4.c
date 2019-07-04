#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

/* 僵死进程，孤儿进程，收尸，刷新缓冲区（全缓存、行缓冲） */

int main(void)
{
	pid_t pid;
	//write(1, "123\n", 5);

	printf("hello------%d\n", getpid());

	fflush(NULL);

	pid = fork();
	if (0 == pid)
	{
		sleep(2);
		printf("Child=============\n");
		printf("self:%d\n", getpid());
		printf("parent:%d\n", getppid());
		//exit(1);
	}
	else if (0 < pid)
	{
		sleep(10);
		printf("Parent=============\n");
		printf("self--:%d\n", getpid());
		printf("parent--:%d\n", getppid());
		//exit(1);
	}
	
	wait(NULL);
	//sleep(1);

	printf("%s\n", "end");

	return 0;
}
