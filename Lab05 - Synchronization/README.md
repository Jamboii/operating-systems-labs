# Lab 05 - Synchronization

Demonstration of the implementation and application of mutex locks and semaphores. 

### Task

**Part 1**

• Observe a multi-threaded producer/consumer example with and without the addition of mutex locks.

**Part 2**

• Demonstrate the usage of semaphores using wait() and signal() to solve the critical-section problem.

**Part 3**

• An interesting way of calculating pi is to use a technique known as Monte Carlo, which involves randomization.

• Write a multi-threaded version of this algorithm that creates a separate thread to generate a number of random points. The thread will count the number of points that occur within the circle and store that result in a global variable. When this thread has exited, the parent thread will calculate and output the estimated value of pi. (See Lab 03)

• Modify this program so several threads are created, each of which generates random points and determines if the points fall within the circle. Each thread will have to update the global count of all points that fall within the circle. Protect against race conditions on updates to the shared global variable by some synchronization method.
