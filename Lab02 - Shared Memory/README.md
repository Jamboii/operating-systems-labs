# Lab 02 - Shared Memory

Print a series of numbers generated from the Collatz conjecture using a shared-memory object.

#### Task

The Collatz conjecture concerns what happens when we take any positive integer _n_ and apply the following algorithm:

if _n_ is even: _n_ = _n_/2
if _n_ is odd:  _n_ = 3 * n + 1

This conjecture states that when this algorithm is continually applied, all positive integers will eventually reach 1.

ex. n = 35 ---> 35,106,53,160,80,40,20,10,5,16,8,4,2,1

Using the fork() system call to generate this sequence in the child process, write the contents of the sequence to a shared-memory object and output the sequence from the parent process.


