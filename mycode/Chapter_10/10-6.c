#include <apue.h>
#include <sys/wait.h>

static void sig_cld(int);

int main(void)
{
    pid_t pid;

    if ((signal(SIGCLD, sig_cld)) == SIG_ERR)
        perror("signal error");

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
    {
        sleep(2);
        _exit(0);
    }
    pause();
    exit(0);
}

static void sig_cld(int signo)
{
    pid_t pid;

    int status;

    printf("SIGCLD received!\n");

    if (signal(SIGCLD, sig_cld) == SIG_ERR)
        perror("signal error");

    if ((pid = wait(&status)) < 0)
        perror("wait error");
    printf("pid=%d\n", pid);
}

/*
This program can't run as Apue said in deepin.

The result:

$ ./10-6
SIGCLD received!
pid=7515

 */