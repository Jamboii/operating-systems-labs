/*
    Alex Benasutti
    CSC345-01
    Lab 02 Exercise 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main()
{
    pid_t pid;
    pid = fork(); // establish fork

    if (pid == 0) // child
    {
        // child process terminates
    }
    else if (pid > 0) // parent
    {
        sleep(300); // parent process continues to run and creates zombie process
        
        /*
            to kill zombie process, we use "ps -l" to find the process id
            and use "kill -9 <pid>" to kill the process (labeled S)
            which as a result will kill the zombie process (labeled Z)
        */
    }
    
    return 0;
}