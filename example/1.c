#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	/* putchar('a'); */
	/* write(1, "b", 1); */
    int fd1, fd2;

    fd1 = open("/tmp/test.txt", O_RDONLY);
    printf("fd1:%d\n", fd1);

    fd2 = open("/tmp/test.txt", O_RDONLY);
    printf("fd2:%d\n", fd2);
    close(fd2);
    fd2 = open("/tmp/test.txt", O_RDONLY);
    printf("fd2:%d\n", fd2);


    char c;
    while(read(0, &c, 1)>0)
    {
        write(1, "hello\n", 7);
        write(1, &c, 1);
    }

	return 0;
}
