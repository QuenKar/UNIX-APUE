#include "apue.h"
#include <fcntl.h>

char buf1[] = "fdsjafjdks";
char buf2[] = "jjdksfjakd";

int main()
{
    int fd;
    if ((fd = creat("file.hole", FILE_MODE)) < 0)
        ;
    if (write(fd, buf1, 10) != 10)
        ;
    if (lseek(fd, 16384, SEEK_SET) == -1)
        ;
    if (write(fd, buf2, 10) != 10)
        ;
    return 0;
}