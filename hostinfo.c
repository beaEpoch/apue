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

#include "./csapp.h"

/* getaddrinfo getnameinfo */

/* #define MAXLINE 1024 */

int main(int argc, char **argv)
{

    struct addrinfo *p, *listp, hints;
    char buf[MAXLINE];
    int rc, flags;

    if (argc !=2)
        exit(0);

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    rc = getaddrinfo(argv[1], NULL, &hints, &listp);
    if (rc != 0)
        exit(0);

    flags = NI_NUMERICHOST;
    for (p=listp; p; p=p->ai_next)
    {
        getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, NULL, 0, flags);
        printf("%s\n", buf);
    }

    freeaddrinfo(listp);


	return 0;
}
