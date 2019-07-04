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

/* web server */


void make_response(int fd)
{
    fflush(NULL);
    char buf[MAXLINE];
    sprintf(buf, "HTTP/1.1 200 OK\r\nServer: Tiny Web\r\nConnection: keep-alive\r\nContent-Type: text/html; charset=utf-8\r\nAllow: GET, HEAD, OPTIONS\r\nX-Frame-Options: SAMEORIGIN\r\n\r\nhello world.");
    Rio_writen(fd, buf, strlen(buf));
    fputs(buf, stdout);
    /* Rio_writen(fd, "hello client", strlen("hello client")); */
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

    listenfd = Open_listenfd(port);
    printf("listenfd:%d\n", listenfd);


    while (1)
    {
        clientlen = sizeof(struct sockaddr_storage);
        connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);
        printf("connfd:%d\n", connfd);

        /* Getnameinfo((SA *)&clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0); */
        /* printf("connected to (%s, %s)\n", client_hostname, client_port); */

       fflush(NULL);
       Rio_readinitb(&rio, connfd);
       Rio_readlineb(&rio, buf, MAXLINE);
       printf("%s", buf);
       while (strcmp(buf, "\r\n"))
       {
           Rio_readlineb(&rio, buf, MAXLINE);
           fputs(buf, stdout);
       }
       make_response(connfd);
       printf("over");
       close(connfd);

    }
	
    printf("exit");
    return 0;
}
