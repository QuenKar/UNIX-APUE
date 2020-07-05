#include <apue.h>

#define PSCMD "ps -o pid,ppid,state,tty,command"

int main(void)
{
    pid_t pid;
    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
    {
        exit(0);
    }

    sleep(4);
    system(PSCMD);

    exit(0);
}

/*

$ ./problem-8-6 
   PID   PPID S TT       COMMAND
  5960   5932 S pts/0    /bin/zsh
  6016   5960 S pts/0    ./problem-8-6
  6017   6016 Z pts/0    [problem-8-6] <defunct>
  6018   6016 S pts/0    sh -c ps -o pid,ppid,state,tty,command
  6019   6018 R pts/0    ps -o pid,ppid,state,tty,command

 */