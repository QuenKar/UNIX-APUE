#include <apue.h>
#include <setjmp.h>
#include <time.h>

static void sig_usr1(int);
static void sig_alrm(int);

static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjmp;

int main(void)
{
    if (signal(SIGUSR1, sig_usr1) == SIG_ERR)
        err_sys("signal(SIGUSR1) error");

    if (signal(SIGALRM, sig_alrm) == SIG_ERR)
        err_sys("signal(SIGALRM) error");

    pr_mask("starting main: ");

    if (sigsetjmp(jmpbuf, 1))
    {
        pr_mask("ending main: ");
        exit(0);
    }

    canjmp = 1; //信号处理程序的longjump，需要保护机制；
    for (;;)
        pause();
}

static void sig_usr1(int signo)
{
    time_t starttime;
    if (canjmp == 0) //未知信号发生，返回;
        return;

    pr_mask("starting sig_usr1");

    alarm(3);
    starttime = time(NULL);

    for (;;)
    {
        if (time(NULL) > starttime + 5)
            break;
    }

    pr_mask("finishing sig_usr1");

    canjmp = 0;
    siglongjmp(jmpbuf, 1);
}

static void sig_alrm(int signo)
{
    pr_mask("in sig_alrm");
}

/*
$ ./10-20&
[1] 8718
starting main:                                                                                                            

$ kill -USR1 8718 
starting sig_usr1                                                                                                         

$ in sig_alrm
finishing sig_usr1
ending main: 

[1]  + 8718 done       ./10-20

 */