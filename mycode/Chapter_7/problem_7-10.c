#include<stdio.h>

int f1(int val)
{
    int num=0;
    int *ptr=&num;
    if(val==0)
    {
        int p;
        p=5;
        ptr=&p;
    }
    return (*ptr+1);
}

int main(void)
{
    printf("val==0 res=%d\n",f1(0));
    printf("val==2 res=%d\n",f1(2));
    return 0;
}