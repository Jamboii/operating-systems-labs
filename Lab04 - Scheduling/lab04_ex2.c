/*
* Alex Benasutti
* CSC345-01
* Lab 4 Exercise 2
*/

#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 5

/* Each thread will begin control in this function */
void *runner(void *param)
{
    /* do some work ... */
    printf("nice\n");

    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    int i, policy;
    pthread_t tid[NUM_THREADS];
    pthread_attr_t attr;

    /* get default attributes */
    pthread_attr_init(&attr);

    /* get the current scheduling policy */
    if (pthread_attr_getschedpolicy(&attr, &policy) != 0)
        fprintf(stderr, "Unable to get policy.\n");
    else
    {
        if (policy == SCHED_OTHER) printf("SCHED_OTHER\n");
        else if (policy == SCHED_RR) printf("SCHED_RR\n");
        else if (policy == SCHED_FIFO) printf("SCHED_FIFO\n");
    }

    /* set the scheduling policy - FIFO, RR, or OTHER */
    if (pthread_attr_setschedpolicy(&attr, SCHED_FIFO) != 0)
        fprintf(stderr, "Unable to set policy.\n");

    /* create the threads */
    for (i=0;i<NUM_THREADS;i++)
        pthread_create(&tid[i],&attr,runner,NULL);

    for (i=0;i<NUM_THREADS;i++)
        pthread_join(tid[i],NULL);

    return 0;
}