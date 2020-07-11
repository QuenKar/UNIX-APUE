#include <stdlib.h>
#include <pthread.h>

typedef struct foo
{
    int f_count;
    int f_id;
    pthread_mutex_t f_lock;
} foo;

foo *foo_alloc(int id)
{
    foo *fp;
    if ((fp = malloc(sizeof(foo))) != NULL)
    {
        fp->f_count = 1;
        fp->f_id = id;
        if (pthread_mutex_init(&fp->f_lock, NULL) != 0)
        {
            free(fp);
            return NULL;
        }
    }
    return fp;
}

void foo_hold(foo *fp)
{
    pthread_mutex_lock(&fp->f_lock);
    fp->f_count++;
    pthread_mutex_unlock(&fp->f_lock);
}

void foo_rele(foo *fp)
{
    pthread_mutex_lock(&fp->f_lock);
    if (--fp->f_count == 0)
    {
        pthread_mutex_unlock(&fp->f_lock);  
        pthread_mutex_destroy(&fp->f_lock);//为什么要在摧毁之前先解开锁?;
        free(fp);
        fp = NULL;
    }
    else
    {
        pthread_mutex_unlock(&fp->f_lock);
    }
}
