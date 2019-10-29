/*
* Alex Benasutti
* CSC345-01
* September 31 2019
* Lab 5 example 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define NUM_THREADS 4

long points_inCircle = 0;
long points_total;
double pi;

pthread_mutex_t lock;

void* run(void* param)
{
    double x,y;
    int tempCount;

    for (long i=0;i<points_total/NUM_THREADS;++i)
    {
        // generate points_total points in square - numbers between -1 and +1
        x = 2.0 * ((double)rand() / (double)RAND_MAX) - 1;
        y = 2.0 * ((double)rand() / (double)RAND_MAX) - 1;

        // count how many of them fall within circle of r = 1
        if (sqrt(x*x + y*y) < 1.0)
        {
            ++tempCount;
        }
    }

    pthread_mutex_lock(&lock);
        points_inCircle += tempCount;
    pthread_mutex_unlock(&lock);

    pthread_exit(0);
}

int main(int argc, char** argv)
{

    // get total number of random points to be generated (from command line)
    points_total = atol(argv[1]);
    int i;

    // create thread to do the counting job
    pthread_t tid[NUM_THREADS];

    pthread_mutex_init(&lock, NULL);

    for (i=0;i<NUM_THREADS;++i) pthread_create(&tid[i], 0, run, NULL);
    for (i=0;i<NUM_THREADS;++i) pthread_join(tid[i], NULL);

    // estimate pi based on the counting result

    pi = 4.0 * (double)points_inCircle / (double)points_total;

    printf("Estimated pi = %f\n", pi);

    pthread_mutex_destroy(&lock);

    return 0;
}