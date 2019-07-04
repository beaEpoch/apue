#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../csapp.c"

int main(void)
{
    int i;
    for (i=0; i<5; i++)
    {
        printf("heloo");
        char *c;
        fgets(c, 2, stdin);
        fputs(c, stdout);
        printf("over");
    }

	return 0;
}
