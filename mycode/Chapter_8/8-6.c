#include <apue.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;
    int status;

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)
    {
        if ((pid = fork()) < 0)
            err_sys("fork error");
        else if (pid > 0)
            exit(2);

        printf("parent pid = %ld\n", (long)getppid());
        exit(3);
    }

    if (waitpid(pid, &status, 0) != pid)
        err_sys("waitpid error");
    pr_exit(status);

    exit(0);
}