#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

long number_of_points_in_circle;
long total_number_of_points;
double pi;

void* run(void* param)
{
    number_of_points_in_circle = 0;

    for (long i=0;i<total_number_of_points;++i)
    {
        // generate total_number_of_points points in square - numbers between -1 and +1
        double x = 2.0 * ((double)rand() / (double)RAND_MAX) - 1;
        double y = 2.0 * ((double)rand() / (double)RAND_MAX) - 1;

        // count how many of them fall within circle of r = 1
        if (sqrt(x*x + y*y) < 1.0)
        {
            ++number_of_points_in_circle;
        }
    }

    pthread_exit(0);
}

int main(int argc, char** argv)
{

    // get total number of random points to be generated (from command line)
    total_number_of_points = atol(argv[1]);

    // create thread to do the counting job
    pthread_t tid;
    pthread_create(&tid, 0, run, NULL);
    pthread_join(tid, NULL);

    // estimate pi based on the counting result

    pi = 4.0 * (double)number_of_points_in_circle / (double)total_number_of_points;

    printf("Estimated pi = %f\n", pi);

    return 0;
}