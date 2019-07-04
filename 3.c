#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	char buff[25];

	fd = open("/tmp/test.txt", O_RDONLY);
	printf("%d\n", fd);

	read(fd, buff, 20);
	printf("%s\n", buff);

	return 0;
}
