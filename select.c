#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <syslog.h>

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
    
    fd_set rset;

    FD_ZERO(&rset);
    /* FD_ZERO(&wset); */

    /* alarm(5); */
    /* signal(SIGALRM, handler); */
    

    FD_SET(fd, &rset);
    /* FD_SET(1, &wset); */
    /* FD_SET(3, &rset); */
    /* FD_SET(3, &wset); */
    
    /* FD_CLR(1, &wset); */

    ret = select(fd+1, &rset, NULL, NULL, NULL);
    printf("ret:%d\n", ret);

    printf("%d\n", FD_ISSET(0, &rset));
    /* printf("%d\n", FD_ISSET(1, &wset)); */
    printf("isset:%d\n", FD_ISSET(fd, &rset));
    /* printf("%d\n", FD_ISSET(3, &wset)); */


	return 0;
}
