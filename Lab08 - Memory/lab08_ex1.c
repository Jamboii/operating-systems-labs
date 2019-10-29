/*
* Alex Benasutti
* CSC345-01
* October 17 2019
* Lab 8 Exercise 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#define PAGE_SIZE 4096

int main(int argc, char** argv)
{
    uint32_t addr = (uint32_t)atol(argv[1]);
    uint32_t page = addr / PAGE_SIZE;
    uint32_t offset = addr % PAGE_SIZE;

    printf("The address %u contains\n", addr);
    printf(" page number = %u\n", page);
    printf(" offset = %u\n", offset);

    return 0;
}