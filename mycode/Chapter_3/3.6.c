#include <apue.h>
#include <fcntl.h>

#define BUFFERSIZE 100

int main(void)
{
    int fd, result;
    char wbuf[5] = "1234";
    char rbuf[20];
    if ((fd = open("a.txt", O_RDWR | O_APPEND)) < 0)
    {
        perror("open");
        return -1;
    }

    if ((result = lseek(fd, 0, SEEK_SET)) < 0)
    {
        perror("lseek");
        return -1;
    }

    if (result = read(fd, rbuf, 20) < 0)
    {
        perror("read");
        return -1;
    }
    printf("readbuf:%s", rbuf);

    if ((result = write(fd, wbuf, 4)) < 0)
    {
        perror("write");
        return -1;
    }

    close(fd);
    return 0;
}