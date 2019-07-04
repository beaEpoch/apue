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


void signal_handler(int sig)
{
    /* printf("sigchld signal."); */
    write(1, "child exit\n", 100);
    while (waitpid(-1, 0, WNOHANG) > 0)
        ;
    return;
}


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

    signal(SIGCHLD, signal_handler);
    /* signal(SIGTERM, signal_handler); */
    /* signal(SIGINT, signal_handler); */

    listenfd = Open_listenfd(port);
    printf("listenfd:%d\n", listenfd);


    while (1)
    {
        clientlen = sizeof(struct sockaddr_storage);
        connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);
        printf("connfd:%d\n", connfd);

        if (fork() == 0)
        {
            printf("child process:%d\n", getpid());
            close(listenfd);
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
            printf("client over\n");
            close(connfd);
            exit(0);
        }
        close(connfd);


    }
	
    printf("exit");
    return 0;
}
