#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* result:
    fd1:3
    fd2:4
    c:1
    c:1 */


int main(void)
{
    int fd1, fd2;

    fd1 = open("/tmp/test.txt", O_RDONLY);
    printf("fd1:%d\n", fd1);
    /* close(fd1); */

    fd2 = open("/tmp/test.txt", O_RDONLY);
    printf("fd2:%d\n", fd2);


    char c;
    read(fd1, &c, 1);
    printf("c:%c\n", c);
    
    read(fd2, &c, 1);
    printf("c:%c\n", c);

	return 0;
}
