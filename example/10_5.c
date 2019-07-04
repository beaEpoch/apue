#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* result:
    fd1:3
    fd2:4
    c:1
    c:2 */


int main(void)
{
    int fd1, fd2;
    char c;

    fd1 = open("/tmp/test.txt", O_RDONLY);
    printf("fd1:%d\n", fd1);

    fd2 = open("/tmp/test.txt", O_RDONLY);
    printf("fd2:%d\n", fd2);

    read(fd2, &c, 1);
    printf("c:%c\n", c);
    dup2(fd2, fd1);
    read(fd1, &c, 1);
    printf("c:%c\n", c);

	return 0;
}
