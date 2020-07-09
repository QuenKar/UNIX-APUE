#include <apue.h>

volatile sig_atomic_t quitflag;

static void sig_int(int signo)
{
    if (signo == SIGINT)
        printf("\ninterrrupt\n");
    else if (signo == SIGQUIT)
        quitflag = 1;
}

int main(void)
{
    sigset_t newmask, oldmask, zeromask;
    //书上将这段代码放在这里，我移到了while里面;
    // if (signal(SIGINT, sig_int) == SIG_ERR)
    //         err_sys("signal error");
    if (signal(SIGQUIT, sig_int) == SIG_ERR)
        err_sys("signal error");

    sigemptyset(&zeromask);
    sigemptyset(&newmask);

    sigaddset(&newmask, SIGQUIT);

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        err_sys("SIG_BLOCK error");

    while (quitflag == 0)
    {
        if (signal(SIGINT, sig_int) == SIG_ERR)
            err_sys("signal error");
        sigsuspend(&zeromask);
    }

    quitflag = 0;

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        err_sys("SIG_SETMASK error");
    exit(0);
}

/*
wrong ans:把signal放在while外面，连续按两次^C程序就直接退出了...
$ ./10-23
^C
interrrupt
^C      



right ans:
$ ./10-23
^C
interrrupt
^C
interrrupt
^C
interrrupt
^C
interrrupt
^\%          
 */