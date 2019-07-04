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

/* mmap 文件映射到内存 */

#define FILENAME "/tmp/test.txt"


int main(void)
{
    int fd;
    char *str;

    struct stat statres;

    fd = open(FILENAME, O_RDONLY);
    printf("fd:%d\n", fd);
    
    int fsize;
    fsize = fstat(fd, &statres); // 获取文件大小
    printf("fsize:%d\n", fsize);

    str = mmap(NULL, statres.st_size, PROT_READ, MAP_SHARED, fd, 0); // 将文件内容映射到内存

    close(fd); // 关闭文件，对映射到内存的字符串进行操作


    for (int i=0; i<statres.st_size; i++)
    {
        printf("%c\n", str[i]);
    }

    printf("%s", str);
    munmap(str, statres.st_size); // 解除映射

	return 0;
}
