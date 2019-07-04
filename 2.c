#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	FILE *fp = NULL;
	int fd;
	int fd1;

	fp = fopen("/tmp/test.txt", "r");
	fd = open("/tmp/test.txt", O_RDONLY);
	
	fd1 = fileno(fp);
	printf("%d\n", fd);
	printf("%d\n", fd1);

	return 0;
}
