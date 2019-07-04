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

/* select */

#define DEBUGFILE "/tmp/logout"

/* static void handler(int sig)
{
    int fd;
    fd = open(DEBUGFILE, O_RDONLY);
    printf("fd:%d\n", fd);
} */

int main(void)
{
    int fd;
    int ret;
    fd = open(DEBUGFILE, O_WRONLY);
    printf("fd:%d\n", fd);
    
    struct pollfd fds[5];

    fds[0].fd = 0;
    fds[1].fd = 1;
    fds[2].fd = 2;
    fds[3].fd = fd;
    fds[4].fd = 4; // 出错的描述符

    for (int i=0; i<5; i++)
        fds[i].events = POLLIN | POLLOUT; // 监听的事件类型（读或写）

    ret = poll(fds, 5, 1000); // 返回数组fds中读准备好、写准备好，以及出错的总数量
    printf("ret:%d\n", ret);

    for (int i=0; i<5; i++)
    {
        printf("revents[%d] read:%d\n", i, fds[i].revents & POLLIN); // 输出可读的描述符
        printf("revents[%d] write:%d\n", i, fds[i].revents & POLLOUT); // 输出可写的描述符
    }

	return 0;
}
