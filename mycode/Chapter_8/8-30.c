#include <apue.h>
#include <errno.h>
#include <sys/time.h>

unsigned long long count;
struct timeval end;

void checktime(char *str)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    if (tv.tv_sec >= end.tv_sec && tv.tv_usec >= end.tv_usec)
    {
        printf("%s count = %lld\n", str, count);
        exit(0);
    }
}

int main(int argc, char *argv[])
{
    pid_t pid;
    char *s;
    int nzero, ret;
    int adj = 0;
    //set "unbuffered"
    setbuf(stdout, NULL);

    //to get NZERO value ,need to use sysconf;
    nzero = sysconf(_SC_NZERO);

    printf("NZERO = %d\n", nzero);
    if (argc == 2)
        adj = strtol(argv[1], NULL, 10);
    gettimeofday(&end, NULL);
    end.tv_sec += 10; //run for 10 seconds;

    if ((pid = fork()) < 0)
        err_sys("fork failed");
    else if (pid == 0)
    {
        s = "child";
        printf("current nice value in child is %d, adjusting by %d\n", nice(0) + nzero, adj);
        errno = 0;
        if ((ret = nice(adj)) == -1 && errno != 0)
            err_sys("child set scheduling priority");
        printf("ret = %d\n", ret);
        printf("NZERO = %d\n", nzero);
        printf("now child nice value is %d\n", ret + nzero);
    }
    else
    {
        s = "parent";
        printf("current nice value in parent is %d\n", nice(0) + nzero);
    }

    for (;;)
    {
        if (++count == 0)
            err_quit("%s counter wrap", s);
        checktime(s);
    }
}

/* result

$ ./8-30                   
NZERO = 20
current nice value in parent is 20
current nice value in child is 20, adjusting by 0
ret = 0
NZERO = 20
now child nice value is 20
parent count = 263416439
child count = 264077903

$ ./8-30 30                
NZERO = 20
current nice value in parent is 20
current nice value in child is 20, adjusting by 30
ret = 19
NZERO = 20
now child nice value is 39
parent count = 519852945
child count = 7595060


 */
