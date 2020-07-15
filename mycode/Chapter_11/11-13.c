#include <apue.h>
#include <pthread.h>

int main(void)
{
    int err;
    struct timespec tout;

    struct tm *tmp;
    char buf[64];
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&lock);
    printf("mutex is locked\n");
    clock_gettime(CLOCK_REALTIME, &tout);
    tmp = localtime(&tout.tv_sec);
    strftime(buf, sizeof(buf), "%r", tmp);
    printf("current time is %s\n", buf);
    tout.tv_sec += 10;

    err = pthread_mutex_timedlock(&lock, &tout); //这会导致死锁;
    clock_gettime(CLOCK_REALTIME, &tout);
    tmp = localtime(&tout.tv_sec);
    strftime(buf, sizeof(buf), "%r", tmp);
    printf("the time is now %s\n", buf);
    if (err = 0)
        printf("mutex locked again!\n");
    else
        printf("can't lock mutex again:%s\n", strerror(err));
    exit(0);
}

/*
$ ./11-13 
mutex is locked
current time is 11:01:20 AM
the time is now 11:01:30 AM
can't lock mutex again:Success
 */