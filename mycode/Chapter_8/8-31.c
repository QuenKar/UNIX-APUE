#include <apue.h>
#include <sys/times.h>

static void pr_times(clock_t, struct tms *, struct tms *);
static void do_cmd(char *);

int main(int argc, char *argv[])
{
    int i;
    setbuf(stdout, NULL);

    for (i = 1; i < argc; i++)
        do_cmd(argv[i]);
    exit(0);
}

static void do_cmd(char *cmd)
{
    struct tms tmsstart, tmsend;
    clock_t start, end;
    int status;

    printf("\ncommand: %s\n", cmd);

    if ((start = times(&tmsstart)) == -1)
        err_sys("times error");

    if (status = system(cmd) < 0)
        err_sys("system error");

    if ((end = times(&tmsend)) == -1)
        err_sys("times error");

    pr_times(end - start, &tmsstart, &tmsend);
    pr_exit(status);
}

static void pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend)
{
    static long clktck = 0;
    if (clktck == 0)
        if ((clktck = sysconf(_SC_CLK_TCK)) < 0)
            err_sys("sysconf error");
    printf("    real: %7.2f\n", real / (double)clktck);
    printf("    user: %7.2f\n",
           (tmsend->tms_utime - tmsstart->tms_utime) / (double)clktck);
    printf("    sys: %7.2f\n",
           (tmsend->tms_stime - tmsstart->tms_stime / (double)clktck));
    printf("    child user: %7.2f\n",
           (tmsend->tms_cutime - tmsstart->tms_cutime / (double)clktck));
    printf("    child sys: %7.2f\n",
           (tmsend->tms_cstime - tmsstart->tms_cstime / (double)clktck));
}

/*
command: sleep 5
    real:    5.01
    user:    0.00
    sys:    0.00
    child user:    0.00
    child sys:    0.00
normal termination, exit status = 0

command: date
2020年 07月 04日 星期六 13:27:06 CST
    real:    0.00
    user:    0.00
    sys:    0.00
    child user:    0.00
    child sys:    0.00
normal termination, exit status = 0

command: man bash > /dev/null
    real:    0.71
    user:    0.00
    sys:    0.00
    child user:   14.00
    child sys:    7.00
normal termination, exit status = 0
 */
