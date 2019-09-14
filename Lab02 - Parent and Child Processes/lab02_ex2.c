/*
    Alex Benasutti
    CSC345-01
    Lab 02 Exercise 2
*/

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

#define SIZE 5

int nums[SIZE] = {0,1,2,3,4};
int main()
{
    int i;
    pid_t pid;
    pid = fork();                               // establish fork
    if (pid == 0) // CHILD PROCESS
    {
        for (i=0;i<SIZE;i++)
        {
            nums[i] *= -i;                      // declare child nums
            printf("CHILD: %d\n", nums[i]);     // output child nums
        }
    }
    else if (pid > 0) // PARENT PROCESS
    {
        wait(NULL);
        for (i=0;i<SIZE;i++)
            printf("PARENT: %d\n", nums[i]);    // output parent nums
    }
    return 0;
}