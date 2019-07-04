#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <syslog.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/select.h>

#include "csapp.c"

/* client */


int main(int argc, char **argv)
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    char client_hostname[MAXLINE], client_port[MAXLINE];
    char *port;
    char buf[MAXLINE];
    rio_t rio;

    if (argc !=2)
        exit(0);

    /* host = argv[1]; */
    port = argv[1];

    listenfd = Open_listenfd(port);
    printf("listenfd:%d\n", listenfd);

    fd_set rset;
    FD_ZERO(&rset);
    FD_SET(listenfd, &rset);
    FD_SET(0, &rset);

    while (1)
    {

        int ret;
        ret = select(listenfd+1, &rset, NULL, NULL, NULL);
        printf("ret:%d\n", ret);
        if (FD_ISSET(0, &rset))
        {
            char buf[MAXLINE];
            printf("stdin ready\n");

            if(fgets(buf, MAXLINE, stdin) < 0)
            {
                exit(0);
            }
            printf("%s", buf);
        }

        if (FD_ISSET(listenfd, &rset))
        {
            printf("listenfd ready\n");


            clientlen = sizeof(struct sockaddr_storage);
            connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);
            printf("connfd:%d\n", connfd);

            Getnameinfo((SA *)&clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
            printf("connected to (%s, %s)\n", client_hostname, client_port);

            Rio_readinitb(&rio, connfd);
            while (Rio_readlineb(&rio, buf, MAXLINE) != 0)
            {
                printf("server received data.\n");
                fputs(buf, stdout);
                /* Rio_writen(connfd, buf, strlen(buf)); */
                Rio_writen(connfd, "server get it!\n", strlen("server get it!\n")); // 开始并没有加\n，输出不会实时，因为终端是行缓冲的
            }
            printf("over");
            close(connfd);
        }
            

    }
	
    printf("exit");
    return 0;
}
