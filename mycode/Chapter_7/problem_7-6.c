#include <stdio.h>
#include <stdlib.h>
int main()
{
    long *arr = calloc(10, sizeof(long));

    for (int i = 0; i < 10; i++)
        printf("%d ", arr[i]);
    printf("\n");

    char**string=calloc(10,sizeof(char*));
    for(int i=0;i<10;i++)
    {
        if(string[i]==NULL)
            printf("NULL ");
    }
    printf("\n");

    return 0;
}