#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

/* 流量控制 每秒输入10个字节数据 */

#define BUFSIZE 10

static volatile int loop = 0;

static void handler(int sig)
{
    /* write(1, "!", 1); */
    alarm(1);
    loop = 0;
}


int main(int argc, char **argv)
{
    int fd = -1;
    char buf[BUFSIZE] = "";
    ssize_t readsize = -1;
    ssize_t writesize = -1;
    size_t off = 0;

    if (argc < 2)
    {
        fprintf(stderr, "argc not 2");
        return 1;
    }

    do {
        fd = open(argv[1], O_RDONLY);
        if (fd < 0)
        {
            return 1;
        }
    } while(fd < 0);

    loop = 1;
    signal(SIGALRM, handler);
    alarm(1);

    while (1)
    {
        while (loop)
        {
            pause();
        }
        loop = 1;

        while ((readsize = read(fd, buf, BUFSIZE)) < 0)
        {
            perror("read()");
            close(fd);
        }
        if (!readsize)
        {
            break;
        }

        off = 0;
        do {
            writesize = write(1, buf+off, readsize);
            off += writesize;
            readsize -= writesize;
        } while (readsize > 0);


        printf("__________________\n");

        /* write(1, "*", 1); */
        /* sleep(3); */
    }

    close(fd);


	return 0;
}
