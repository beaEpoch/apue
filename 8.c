#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

/* 信号mask设置 */

static void handler(int sig)
{
    sleep(1);
    write(1, "!", 1);
}


int main(void)
{
    sigset_t set, oset, sset;
    int i, j;
    printf("---\n");
    /* alarm(5); */
    
    /* signal(SIGALRM, handler); */
    signal(SIGINT, handler);

    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    
    sigprocmask(SIG_UNBLOCK, &set, &sset);
    sigprocmask(SIG_BLOCK, &set, &oset);


    for (i=0; i<10; i++)
    {
        write(1, "+", 1);
        sleep(3);
        for (j=0; j<2; j++)
        {
            write(1, "*", 1);
            sleep(2);
        }
        write(1, "\n", 1);

        sigsuspend(&oset);
    }

    sigprocmask(SIG_SETMASK, &sset, NULL);


	return 0;
}
