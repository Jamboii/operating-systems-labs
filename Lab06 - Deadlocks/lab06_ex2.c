/*
* Alex Benasutti
* CSC345-01
* October 3 2019
* Lab 6 Example 2
*/

// starvation free version

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

/* bridge */
pthread_mutex_t c_mutex;
pthread_cond_t c_condv;

int num_waiting_north = 0;
int num_waiting_south = 0;
int prev = 0;
int on_bridge = 0;

const char* direction[2] = {"South", "North"};

void enter_bridge_north(FARMER* f) // some params needed here and for the exits
{
    printf("North farmer %d arrived at the bridge\n",f->idx);

    ++num_waiting_north;

    pthread_mutex_lock(&c_mutex);

    // some synch code with peterson solution idea
    while (on_bridge || (prev == 0 && num_waiting_south > 0))
    {
        pthread_cond_wait(&c_condv, &c_mutex);
    }

    --num_waiting_north;
    prev = 0;       // previous is south
    on_bridge = 1;  // bridge is currently occupied
}

void enter_bridge_south(FARMER* f)
{
    printf("South farmer %d arrived at the bridge\n",f->idx);

    ++num_waiting_south;
    pthread_mutex_lock(&c_mutex);

    /* Synchronization using Peterson's Solution */
    while (on_bridge || (prev == 1 && num_waiting_north > 0))
    {
        pthread_cond_wait(&c_condv, &c_mutex);
    }

    --num_waiting_south;
    prev = 1;       // previous is north
    on_bridge = 1;  // bridge is currently occupied
}

void exit_bridge(FARMER* f)
{
    printf("\t%s Farmer %d has just finished passing\n", direction[f->isNorth], f->idx);

    on_bridge = 0;

    /* Notify everyone waiting to pass the bridge regardless of direction */
    pthread_cond_broadcast(&c_condv);
    pthread_mutex_unlock(&c_mutex);
}

void* pass_bridge(void* param)
{
    /* 
    Each farmer aka thread will check if bridge is available or not. 
    If available, enter bridge. 
    Wait for some time, 
    Then exit bridge. 
    */

    FARMER* f = (FARMER*)param;

    /* Attempt to enter bridge */
    if (f->isNorth) enter_bridge_north(f);
    else            enter_bridge_south(f);
    
    /* Wait some time */
    printf("\t%s Farmer %d will spend %d seconds\n", direction[f->isNorth], f->idx, f->waitfor);
    sleep(f->waitfor);

    /* Exit bridge */
    exit_bridge(f);
    printf("%s farmer %d passed the bridge\n", direction[f->isNorth], f->idx);

    /* Exit thread */
    pthread_exit(0);
}

int main(int argc, char** argv)
{
    /* Hold number of farmers from each direction */
    int nNorth = atoi(argv[1]);
    int nSouth = atoi(argv[2]);

    /* List of farmers */
    FARMER* nFarmers = (FARMER*)malloc(sizeof(FARMER) * nNorth);
    FARMER* sFarmers = (FARMER*)malloc(sizeof(FARMER) * nSouth);

    /* Initialize mutex lock and conditional */
    pthread_cond_init(&c_condv, NULL);
    pthread_mutex_init(&c_mutex, NULL);

    for (int i=0;i<nNorth;++i)
    {
        nFarmers[i].isNorth = 1;
        nFarmers[i].idx     = i;
        nFarmers[i].waitfor = rand() % MAX_WAIT;
    }
    for (int i=0;i<nSouth;++i)
    {
        sFarmers[i].isNorth = 0;
        sFarmers[i].idx     = i;
        sFarmers[i].waitfor = rand() % MAX_WAIT;
    }

    for (int i=0;i<nNorth;++i) pthread_create(&(nFarmers[i].t), 0, pass_bridge, &(nFarmers[i]));
    for (int i=0;i<nSouth;++i) pthread_create(&(sFarmers[i].t), 0, pass_bridge, &(sFarmers[i]));

    for (int i=0;i<nNorth;++i) pthread_join(nFarmers[i].t, NULL);
    for (int i=0;i<nSouth;++i) pthread_join(sFarmers[i].t, NULL);

    /* We are done with the mutex lock and conditional */
    pthread_mutex_destroy(&c_mutex);
    pthread_cond_destroy(&c_condv);

    /* Free up allocated memory */
    free(nFarmers);
    free(sFarmers);

    return 0;
}