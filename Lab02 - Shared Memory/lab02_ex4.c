/*
    Alex Benasutti
    CSC345-01
    Lab 02 Exercise 4
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char** argv)
{
    const char* name = "COLLATZ";                               // name of shared memory
    const int SIZE = 4096;                                      // byte size of shared memory

    int shm_fd;                                                 // shared memory file descriptor
    void *ptr;                                                  // pointer to shared memory

    int n = atoi(argv[1]);                                      // number integer input for collatz conjecture
    pid_t id = fork();                                          // create fork
    if (id == 0) // CHILD PROCESS aka PRODUCER
    {
        shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);        // create shared memory object
        ftruncate(shm_fd, SIZE);                                // configure size of shared memory

        ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0); // memory map to shared memory
        char buf[256];                                          // create buffer array

        while (n > 1)                                           // collatz conjecture
        {
            sprintf(buf, "%d  ", n);                            // write results to shared memory
            sprintf(ptr, "%d  ", n);
            ptr += strlen(buf + 1);
            if (n % 2 == 0)
            {
                n = n / 2;
            } 
            else 
            {
                n = 3 * n + 1;
            }
        }
        sprintf(buf, "%d\n", n);                                // write n=1 to shared memory
        sprintf(ptr, "%d  ", n);
        ptr += strlen(buf + 1);
    } 
    else if (id > 0) // PARENT PROCESS aka CONSUMER
    { 
        wait(NULL);

        shm_fd = shm_open(name, O_RDONLY, 0666);                // open shared memory object

        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);  // memory map to shared memory
        printf("%s\n", (char *)ptr);                            // read from shared memory

        shm_unlink(name);                                       // remove shared memory
    }
    return 0;
}