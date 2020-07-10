#include <apue.h>
#include <pthread.h>

struct foo
{
    int a, b, c, d;
};

void printfoo(const char *s, const struct foo *fp)
{
    printf("%s", s);
    printf(" structure at 0x%lx\n", (unsigned long)fp);
    printf(" foo.a = %d\n", fp->a);
    printf(" foo.b = %d\n", fp->b);
    printf(" foo.c = %d\n", fp->c);
    printf(" foo.d = %d\n", fp->d);
}
//设为全局变量就不会发生结果一问题
struct foo foo = {1, 2, 3, 4};

void *thr_fn1(void *arg)
{
    //struct foo foo = {1, 2, 3, 4};
    printfoo("thread 1:\n", &foo);
    pthread_exit((void *)&foo);
}

void *thr_fn2(void *arg)
{
    printf("thread 2: ID is %lu\n", (unsigned long)pthread_self());
    pthread_exit((void *)0);
}

int main(void)
{
    int err;
    pthread_t tid1, tid2;
    struct foo *fp;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (err != 0)
        err_exit(err, "can't create thread 1");
    err = pthread_join(tid1, (void *)&fp);
    if (err != 0)
        err_exit(err, "can't join with thread 1");
    sleep(1);

    printf("parent starting second thread\n");
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (err != 0)
        err_exit(err, "can't create thread 2");
    sleep(1);
    printfoo("parent:\n", fp);

    exit(0);
}

/*
线程2的栈覆盖了线程1的栈
The Result one:
$ ./11-4
thread 1:
 structure at 0x7f464cc74f40
 foo.a = 1
 foo.b = 2
 foo.c = 3
 foo.d = 4
parent starting second thread
thread 2: ID is 139939912570624
parent:
 structure at 0x7f464cc74f40
 foo.a = 1288132352
 foo.b = 32582
 foo.c = 1
 foo.d = 0


 The Result two:
$ ./11-4                             
thread 1:
 structure at 0x55bd85ee10b0
 foo.a = 1
 foo.b = 2
 foo.c = 3
 foo.d = 4
parent starting second thread
thread 2: ID is 140298245912320
parent:
 structure at 0x55bd85ee10b0
 foo.a = 1
 foo.b = 2
 foo.c = 3
 foo.d = 4

 */