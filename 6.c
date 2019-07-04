#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

/* 信号 */

static void handler(int sig)
{
    sleep(1);
    write(1, "!", 1);
    /* pause(); */
}


int main(void)
{
    int i = 0;
    printf("---\n");
    sleep(5);
    alarm(5);
    
    signal(SIGALRM, handler);
    signal(SIGINT, handler);

    for (i=0; i<10; i++)
    {
        write(1, "*", 1);
        sleep(3);
    }


	return 0;
}
