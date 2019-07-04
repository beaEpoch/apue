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

/* daemon 进程 */

#define DEBUGFILE "/tmp/logout"

static FILE *fp;

static int daemonize(void)
{
    pid_t pid;
    int fd;

    pid = fork();
    syslog(LOG_INFO, "daemon ppid is %d.", getppid());
    syslog(LOG_INFO, "daemon pid is %d.", getpid());
    syslog(LOG_INFO, "daemon pid is %d.", pid);
    if (pid < 0)
        return -1;

    if (pid > 0)
        exit(0);


    fd = open("/dev/null", O_RDWR);
    if (fd < 0)
        return -1;

    dup2(fd, 0);
    dup2(fd, 1);
    dup2(fd, 2);

    if (fd > 2)
        close(fd);

    setsid();
    chdir("/");
    umask(0);

    return 0;
}

static void daemon_exit(int sig)
{
    fclose(fp);
    closelog();
    syslog(LOG_INFO, "daemon exited.");
    exit(0);
}

static void handler(int sig)
{
    sleep(1);
    write(1, "!", 1);
    syslog(LOG_INFO, "signal SIGINT is trigged.");
}


int main(void)
{
    /* sigset_t set, oset, sset; */
    int i;
    
    signal(SIGINT, handler);
    signal(SIGTERM, daemon_exit);

    /* sigemptyset(&set);
    sigaddset(&set, SIGINT);
    
    sigprocmask(SIG_UNBLOCK, &set, &sset);
    sigprocmask(SIG_BLOCK, &set, &oset); */

    openlog("mydaemon", LOG_PID, LOG_DAEMON);

    if (daemonize())
    {
        syslog(LOG_INFO, "daemon failure.");
        exit(1);
    }
    else
    {
        syslog(LOG_INFO, "daemon success.");
    }

    fp = fopen(DEBUGFILE, "w");

    for (i=0;;i++)
    {
        /* fwrite(i, sizeof(i), 1, fp); */
        fprintf(fp, "%d", i);
        fprintf(fp, "----");
        fflush(fp);
        syslog(LOG_DEBUG, "%d was printed.", i);
        sleep(1);
    }

	return 0;
}
