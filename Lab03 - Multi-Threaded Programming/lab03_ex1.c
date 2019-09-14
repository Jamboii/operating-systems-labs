#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int len;
int r_min, r_max;
float r_avg, r_median, r_stddev;
int *nums;

void *myMin(void *param)
{
    int i;

    r_min = nums[0];                        // set initial min to first nums position
    for (i=0;i<len;++i)
        if (r_min > nums[i]) r_min = nums[i];   // if current minimum is greater than array value, update

    pthread_exit(0);                        // exit pthread
}

void *myMax(void *param)
{
    int i;

    r_max = nums[0];                        // set initial max to first nums position
    for (i=0;i<len;++i)
        if (r_max < nums[i]) r_max = nums[i];   // if current maximum is less than array value, update
    
    pthread_exit(0);                        // exit pthread
}

void *myAvg(void *param)
{
    int i;

    r_avg = 0;                              // set initial mean to 0
    for (i=0;i<len;++i)
        r_avg += nums[i];                   // get sum of all known nums

    r_avg /= len;                           // sum / len = mean

    pthread_exit(0);                        // exit pthread
}

void *myMedian(void *param)
{
    int i, j, temp;

    for (i=0;i<len;++i)                     // compare every i num to every j num after it
    {
        for (j=i+1;j<len;++j)
        {
            if (nums[i] > nums[j])          // if out of order
            {
                temp = nums[i];             // swap numbers
                nums[i] = nums[j];
                nums[j] = temp;
            }
        }
    }

    if (len % 2 == 1)                       // if odd nums amount
    {
        r_median = nums[(len-1)/2];         // median = middle num
    }
    else                                    // if even nums amount
    {
        float med1 = nums[len/2 - 1];
        float med2 = nums[len/2];

        r_median = (med1 + med2)/2;         // take average of center 2 nums
    }

    pthread_exit(0);                        // exit pthread
}

void *myStddev(void *param)
{
    int i, sum = 0;
    float mean = 0;

    for (i=0;i<len;++i)
        mean += nums[i];                    // generate mean again

    mean /= len;                            // mean = sum / len

    for (i=0;i<len;++i)
        sum += pow(nums[i] - mean, 2);      // sum of differences^2
    
    r_stddev = sqrt(sum / len);             // sqrt(variance) = stddev

    pthread_exit(0);                        // exit pthread
}

int main(int argc, char** argv)
{
    nums = (int*)malloc(sizeof(int) * (argc-1));    // allocate memory for nums

    for (int i=1;i<argc;++i)
        nums[i-1] = atoi(argv[i]);                  // assign nums from argv
    
    len = argc - 1;                                 // length of nums

    pthread_t tid1;                                 // create pthread ids
    pthread_t tid2;
    pthread_t tid3;
    pthread_t tid4;
    pthread_t tid5;

    pthread_create(&tid1, 0, myMin, NULL);          // create threads for each function
    pthread_create(&tid2, 0, myMax, NULL);
    pthread_create(&tid3, 0, myAvg, NULL);
    pthread_create(&tid4, 0, myMedian, NULL);
    pthread_create(&tid5, 0, myStddev, NULL);

    pthread_join(tid1, NULL);                       // wait for threads to exit
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    pthread_join(tid5, NULL);

    printf("The average value is %f\n", r_avg);     // output values
    printf("The minimum value is %d\n", r_min);
    printf("The maximum value is %d\n", r_max);
    printf("The median value is %f\n", r_median);
    printf("The stddev value is %f\n", r_stddev);

    free(nums);                                     // free up allocated memory for nums

    return 0;
}
