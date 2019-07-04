#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

/* execl */

int main(void)
{
	pid_t pid;

	printf("hello------%d\n", getpid());

	fflush(NULL);

	pid = fork();
	if (0 == pid)
	{
		sleep(2);
		printf("Child=============\n");
		printf("self:%d\n", getpid());
		printf("parent:%d\n", getppid());
        execl("/bin/date", "date", "+%s", NULL);
		/* exit(1); */
	}
	else if (0 < pid)
	{
		sleep(10);
		printf("Parent=============\n");
		printf("self--:%d\n", getpid());
		printf("parent--:%d\n", getppid());
	}
    else
    {
        printf("fork error");
        exit(1);
    }
	
	wait(NULL);
	printf("%s\n", "end");

	return 0;
}
