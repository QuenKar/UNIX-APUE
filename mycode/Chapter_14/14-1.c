#include <apue.h>
#include <errno.h>
#include <fcntl.h>

char buf[500000];

int main(void)
{
    int ntowrite, nwrite;
    char *ptr;

    ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
    fprintf(stderr, "read %d bytes\n", ntowrite);

    set_fl(STDOUT_FILENO, O_NONBLOCK);

    ptr = buf;
    while (ntowrite)
    {
        errno = 0;
        nwrite = write(STDOUT_FILENO, ptr, ntowrite);
        fprintf(stderr, "nwrite = %d,errno = %d\n", nwrite, errno);

        if (nwrite > 0)
        {
            ptr += nwrite;
            ntowrite -= nwrite;
        }
    }
    clr_fl(STDOUT_FILENO, O_NONBLOCK);
    exit(0);
}

/*
$ ./14-1 < ./test >temp.file
read 500000 bytes
nwrite = 500000,errno = 0

$ ./14-1 < ./test 2>stderr.out 
结果见stderr.out
 */

// int main(void)
// {
//     int fd;
//     fd = open("test", O_RDWR);

//     char ch[10] = "fjdsalkfjd";
//     for (int i = 0; i < 50001; i++)
//     {
//         write(fd,ch,sizeof(ch));
//     }
//     exit(0);
// }