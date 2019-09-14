/*
 
lab01.c
 
Alex Benasutti
CSC345-01
September 4 2019
 
Has at least one for/while loop                     X
Has at least one defined function excluding main()  X
Calls defined function from main()                  X
Functions declare at least one local variable       X
Calls any standard C library function               X
 
*/

#include <stdio.h>
#include <math.h>

void get_sqrts(int num) // print all integer square roots from 0 to num
{
    while (num > 1)
    {
        int root = sqrt(num);
        printf("Square root of %d is %d\n", num, root);
        num = (root - 1) * (root - 1);
    }
}

int main()
{
    int number = 25;
    get_sqrts(number);
    return 0;
}
