#include <apue.h>
#include <pthread.h>

pthread_t ntid;

void printtids(const char *s)
{
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();

    printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid, (unsigned long)tid, (unsigned long)tid);
}

void thread_fn(void *arg)
{
    printtids("new thread: ");
    return ((void *)0);
}

int main(void)
{
    int err;
    err = pthread_create(&ntid, NULL, thread_fn, NULL);
    if (err != 0)
        err_exit(err, "can't create thread");
    printtids("main thread:");
    sleep(1);
    exit(0);
}

/*

$ ./11-2 
main thread: pid 7969 tid 139948780308224 (0x7f485d564700)
new thread:  pid 7969 tid 139948772185856 (0x7f485cda5700)

 */