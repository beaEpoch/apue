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

#include "csapp.c"

/* client */


int main(int argc, char **argv)
{
    int clientfd;
    char *host, *port;
    char buf[MAXLINE];
    rio_t rio;

    if (argc !=3)
        exit(0);

    host = argv[1];
    port = argv[2];

    clientfd = Open_clientfd(host, port);

    printf("clientfd:%d\n", clientfd);

    Rio_readinitb(&rio, clientfd);


    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
        Rio_writen(clientfd, buf, strlen(buf));
        Rio_readlineb(&rio, buf, MAXLINE);
        fputs(buf, stdout);
    }

    close(clientfd);
	printf("--over");
    return 0;
}
