#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <syslog.h>
#include <syslog.h>
#include <poll.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/epoll.h>
#include <sys/mman.h>

/* mmap 实现共享内存，注意这种共享内存的方式只适用在具有亲缘关系的进程之间使用 */

#define FILENAME "/tmp/test.txt"
#define MEMSIZE 1024


int main(void)
{
    char *str;
    pid_t pid;


    str = mmap(NULL, MEMSIZE, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0); // 在内存中开辟一个共享空间


    fflush(NULL);
    pid = fork();
    /* printf("self pid:%d\n", getpid()); */
    printf("---parent pid:%d\n", getppid());

    if(pid < 0)
    {
        exit(1);
    }

    /* if (pid == 0)
    {
        strcpy(str, "hello world.");
        munmap(str, MEMSIZE); // 子进程也拷贝了一份，所以使用完后也需要解除映射
        exit(0);
    }
    else
    {
        wait(NULL);
        puts(str);
        munmap(str, MEMSIZE); // 父进程解除映射
        exit(0);
    } */

    if(pid)
    {
        printf("1-parent pid:%d\n", pid);
        fflush(NULL);
        pid = fork();
        if(pid < 0)
        {
            exit(1);
        }
        if(pid)
        {
            printf("2-parent pid:%d\n", pid);
            munmap(str, MEMSIZE);
            exit(0);
        }
        else
        {
            sleep(2);
            printf("2--parent pid:%d\n", getppid());
            printf("2--child pid:%d\n", pid);
            printf("2--self pid:%d\n", getpid());
            strcpy(str, "hello world.");
            munmap(str, MEMSIZE);
            exit(0);
        }
    }
    else
    {
        sleep(5);
        printf("1--parent pid:%d\n", getppid());
        printf("1--child pid:%d\n", pid);
        printf("1--self pid:%d\n", getpid());
        puts(str);
        munmap(str, MEMSIZE);
        exit(0);
    }

    wait(NULL);
    printf("------\n");
    exit(0);

	/* return 0; */
}
