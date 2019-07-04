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

/* epoll */

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
    int epfd;
    int ret;
    fd = open(DEBUGFILE, O_WRONLY);
    printf("fd:%d\n", fd);
    
    struct epoll_event ev;

    epfd = epoll_create(10);
    printf("epfd:%d\n", epfd);

    ev.events = EPOLLIN | EPOLLOUT;
    ev.data.fd = 0;
    epoll_ctl(epfd, EPOLL_CTL_ADD, 0, &ev);
    
    ev.events = EPOLLIN;
    ev.data.fd = fd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);

    ret = epoll_wait(epfd, &ev, 1, -1);

    printf("ret:%d\n", ret);

    /* for (int i=0; i<5; i++)
    {
        printf("%d\n", i);
        printf("datafd:%d\n", ev.data.fd);
        if (ev.data.fd == i)
        {
            printf("events[%d] read:%d\n", i, ev.events & EPOLLIN); // 输出可读的描述符
            printf("events[%d] write:%d\n", i, ev.events & EPOLLOUT); // 输出可写的描述符
        }
    } */
    printf("datafd:%d\n", ev.data.fd);
    if (ev.data.fd == 0)
    {
        printf("events[%d] read:%d\n", 0, ev.events & EPOLLIN); // 输出可读的描述符
        printf("events[%d] write:%d\n", 0, ev.events & EPOLLOUT); // 输出可写的描述符
    }
    if (ev.data.fd == fd)
    {
        printf("events[%d] read:%d\n", 3, ev.events & EPOLLIN); // 输出可读的描述符
        printf("events[%d] write:%d\n", 3, ev.events & EPOLLOUT); // 输出可写的描述符
    }

	return 0;
}
