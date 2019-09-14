# Lab 03 - Multithreaded Programming

Multithreaded programming tasks for integer array analysis and Monte Carlo pi calculations.

#### Task

**Part 1**

• Write a multithreaded program that calculates various statistical values for a list of numbers. This program will be passed a series of numbers on the command line and will then create five separate worker threads. These threads will determine the average, minimum, maximum, median, and standard deviation of the numbers.

**Part 2**

• An interesting way of calculating pi is to use a technique known as Monte Carlo, which involves randomization.

• Write a multi-threaded version of this algorithm that creates a separate thread to generate a number of random points. The thread will count the number of points that occur within the circle and store that result in a global variable. When this thread has exited, the parent thread will calculate and output the estimated value of pi.
