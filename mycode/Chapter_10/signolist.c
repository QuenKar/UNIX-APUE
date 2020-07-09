#include <apue.h>
#include <stdio.h>
extern char *sys_siglist[];

int main()
{
    for (int i = 0; i < 32; i++)
    {
        printf("%d :%s\n", i, sys_siglist[i]);
    }
    return 0;
}

/*
deepin Linux 上支持1-31共31种信号，0是空信号;
$ ./signo                    
0 :(null)
1 :Hangup
2 :Interrupt
3 :Quit
4 :Illegal instruction
5 :Trace/breakpoint trap
6 :Aborted
7 :Bus error
8 :Floating point exception
9 :Killed
10 :User defined signal 1
11 :Segmentation fault
12 :User defined signal 2
13 :Broken pipe
14 :Alarm clock
15 :Terminated
16 :Stack fault
17 :Child exited
18 :Continued
19 :Stopped (signal)
20 :Stopped
21 :Stopped (tty input)
22 :Stopped (tty output)
23 :Urgent I/O condition
24 :CPU time limit exceeded
25 :File size limit exceeded
26 :Virtual timer expired
27 :Profiling timer expired
28 :Window changed
29 :I/O possible
30 :Power failure
31 :Bad system call
 */