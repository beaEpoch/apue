#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


/* result:
    fd:3
    c:1
    c:2 */

int main(void)
{
    int fd;
    char c;

    fd = open("/tmp/test.txt", O_RDONLY);
    printf("fd:%d\n", fd);

    if (fork() == 0)
    {
        read(fd, &c, 1);
        printf("c:%c\n", c);
        exit(0);
    }


    wait(NULL);

    read(fd, &c, 1);
    printf("c:%c\n", c);
    

	return 0;
}
