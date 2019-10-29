/*
* Alex Benasutti
* CSC345-01
* October 3 2019
* Lab 6 Example 1
*/

/* starvation free alternates between north and south farmers */
// peterson's algorithm
// before you enter even if youre the first guy in your group, if someone is wating on the other side try to yield
// whoever is waiting on the other side of the bridge you have to let them pass

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

/* farmer */
#define MAX_WAIT 3

typedef struct _FARMER 
{
    pthread_t t;
    int isNorth;
    int idx;
    int waitfor;
} FARMER;

/* bridge */ /* use pthread condition variable in starvation free version */
sem_t sem;

void enter_bridge()
{
    sem_wait(&sem);
}

void exit_bridge()
{
    sem_post(&sem);
}

void* pass_bridge(void* param)
{
    /* 
    each farmer aka thread will check if bridge is available or not. 
    If available, enter bridge. 
    wait for some time, 
    then exit bridge,
    done 
    */

    FARMER* f = (FARMER*)param;

    if (f->isNorth)
        printf("North farmer %d arrived at the bridge\n",f->idx);
    else
        printf("South farmer %d arrived at the bridge\n",f->idx);
    enter_bridge();

    if (f->isNorth)
    {
        printf("\tNorth Farmer %d will spend %d seconds\n", f->idx, f->waitfor);
    }
    else
    {
        printf("\tSouth Farmer %d will spend %d seconds\n", f->idx, f->waitfor);
    }
    sleep(f->waitfor);

    if (f->isNorth)
    {
        printf("\tNorth Farmer %d has just finished passing\n", f->idx);
    }
    else
    {
        printf("\tSouth Farmer %d has just finished passing\n", f->idx);
    }
    exit_bridge();

    if (f->isNorth)
        printf("North farmer %d passed the bridge\n",f->idx);
    else
        printf("South farmer %d passed the bridge\n",f->idx);

    pthread_exit(0);
}

int main(int argc, char** argv)
{
    /* Hold number of farmers from each direction */
    int nNorth = atoi(argv[1]);
    int nSouth = atoi(argv[2]);

    /* list of farmers */
    FARMER* nFarmers = (FARMER*)malloc(sizeof(FARMER) * nNorth);
    FARMER* sFarmers = (FARMER*)malloc(sizeof(FARMER) * nSouth);

    sem_init(&sem, 0, 1);

    for (int i=0;i<nNorth;++i)
    {
        // nFarmers[i].t // initialize the thread
        nFarmers[i].isNorth = 1;
        nFarmers[i].idx     = i;
        nFarmers[i].waitfor = rand() % MAX_WAIT;
    }
    for (int i=0;i<nSouth;++i)
    {
        // sFarmers[i].t // initialize the thread
        sFarmers[i].isNorth = 0;
        sFarmers[i].idx     = i;
        sFarmers[i].waitfor = rand() % MAX_WAIT;
    }

    for (int i=0;i<nNorth;++i)
    {
        pthread_create(&(nFarmers[i].t), 0, pass_bridge, &(nFarmers[i]));
    }
    for (int i=0;i<nSouth;++i)
    {
        pthread_create(&(sFarmers[i].t), 0, pass_bridge, &(sFarmers[i]));
    }

    for (int i=0;i<nNorth;++i)
    {
        pthread_join(nFarmers[i].t, NULL);
    }
    for (int i=0;i<nSouth;++i)
    {
        pthread_join(sFarmers[i].t, NULL);
    }

    sem_destroy(&sem);

    free(nFarmers);
    free(sFarmers);

    return 0;
}