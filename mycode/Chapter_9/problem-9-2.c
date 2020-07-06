#include <apue.h>

int main(void)
{
    pid_t pid;
    char *cmd = "ps -o pid,ppid,pgid,sid,tpgid,comm";

    if ((pid = vfork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
    {
        setsid();
        printf("child:\n");
        system(cmd);
    }
    else
    {
        printf("father:\n");
        system(cmd);
    }

    exit(0);
}

/*
child:
…………
其他命令
   PID   PPID   PGID    SID  TPGID COMMAND
  4328   3038   3038   3038     -1 deepin-terminal
  4900   4899   4900   4900     -1 problem-9-2
  4901   4900   4900   4900     -1 sh
  4902   4901   4900   4900     -1 ps
father:
   PID   PPID   PGID    SID  TPGID COMMAND
  4356   4328   4356   4356   4899 zsh
  4899   4356   4899   4356   4899 problem-9-2
  4903   4899   4899   4356   4899 sh
  4904   4903   4899   4356   4899 ps

 */