# Lab 04 - Scheduling

Demonstration of priority-based scheduling and POSIX real-time scheduling. 

### Task

**Part 1**

• A simple program that logs the time that it takes to execute. Run in the background both regularly and with a NICE value of 19 and observe the time each process takes based on their priorities (a greater NICE value means lower priority).

**Part 2**

• Display the usage of the POSIX real-time scheduling API example. The code retrieves the scheduling policy, be it round robin (RR), first-in-first-out (FIFO) or other, and executes a predefined number threads using that policy. The runner() procedure is the beginning of control for each thread, which will execute whatever code is contained within, and exit upon completion.
