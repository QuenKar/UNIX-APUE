#include <apue.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

#define NTHR 8
#define NUMNUM 8000000L
#define TNUM (NUMNUM / NTHR)

long nums[NUMNUM];
long snums[NUMNUM];

pthread_barrier_t b;

void swap(long *a, long *b)
{
    long *tmp = a;
    *a = *b;
    *b = *tmp;
}

int complong(const void *arg1, const void *arg2)
{
    long l1 = *(long *)arg1;
    long l2 = *(long *)arg2;
    if (l1 == l2)
        return 0;
    else if (l1 < l2)
        return -1;
    else if (l1 > l2)
        return 1;
}
//can't extern heapsort,so I write a quicksort instead.

void quicksort(long a[], long left, long right)
{
    long mid = a[(left + right) / 2];
    long i = left, j = right;
    do
    {
        while (a[i] < mid)
            i++;
        while (a[j] > mid)
            j--;
        if (i <= j)
        {
            swap(&a[i], &a[j]);
            i++;
            j--;
        }
    } while (i <= j);
    if (left < j)
        quicksort(a, left, j);
    if (i < right)
        quicksort(a, i, right);
}

void *thr_fn(void *arg)
{
    long idx = (long)arg;
    quicksort(&nums[idx], idx, idx + TNUM);
    pthread_barrier_wait(&b);

    return ((void *)0);
}

void merge()
{
    long idx[NTHR];
    long i, minidx, sidx, num;

    for (i = 0; i < NTHR; i++)
        idx[i] = i * TNUM;
    for (sidx = 0; sidx < NUMNUM; sidx++)
    {
        num = LONG_MAX;
        for (i = 0; i < NTHR; i++)
        {
            if ((idx[i] < (i + 1) * TNUM) && (nums[idx[i]] < num))
            {
                num = nums[idx[i]];
                minidx = i;
            }
        }
        snums[sidx] = nums[idx[minidx]];
        idx[minidx]++;
    }
}

int main(void)
{
    unsigned long i;
    struct timeval start, end;
    long long startusec, endusec;
    double elapsed;
    int err;
    pthread_t tid;

    //sort with concurrency;
    srandom(1);
    for (int i = 0; i < NUMNUM; i++)
        nums[i] = random();

    gettimeofday(&start, NULL);
    pthread_barrier_init(&b, NULL, NTHR + 1);
    for (i = 0; i < NTHR; i++)
    {
        err = pthread_create(&tid, NULL, thr_fn, (void *)(i * TNUM));
        if (err != 0)
            err_exit(err, "can't create thread");
    }

    pthread_barrier_wait(&b);
    merge();
    gettimeofday(&end, NULL);

    startusec = start.tv_sec * 1000000 + start.tv_usec;
    endusec = end.tv_sec * 1000000 + end.tv_usec;
    elapsed = (double)(endusec - startusec) / 1000000.0;
    // for (i = 0; i < NUMNUM; i++)
    //     printf("%ld\n", snums[i]);
    printf("sort with many threads took %.4f seconds\n", elapsed);

    //sort without concurrency;
    srandom(1);
    for (int i = 0; i < NUMNUM; i++)
        nums[i] = random();

    gettimeofday(&start, NULL);
    qsort(nums, NUMNUM, sizeof(long), complong);
    gettimeofday(&end, NULL);

    startusec = start.tv_sec * 1000000 + start.tv_usec;
    endusec = end.tv_sec * 1000000 + end.tv_usec;
    elapsed = (double)(endusec - startusec) / 1000000.0;
    // for (i = 0; i < NUMNUM; i++)
    //     printf("%ld\n", snums[i]);
    printf("sort without thread took %.4f seconds\n", elapsed);

    exit(0);
}

/*
$ ./11-16                              
sort with many threads took 0.9380 seconds
sort without thread took 2.1453 seconds

$ ./11-16
sort with many threads took 0.9646 seconds
sort without thread took 1.6883 seconds

 */