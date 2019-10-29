# Lab 09 - Paging

A program that passes a decimal virtual address and outputs its page number and offset.

### Task

**Part 1**

• Write a program that implements the FIFO, LRU, and optimal page replacement algorithms presented in this chapter. First, you get a random page-reference string where page numbers range from 0 to 9 from an input file. Apply the random page-reference string to each algorithm, and record the number of page faults incurred by each algorithm. Implement the replacement algorithms so that the number of page frames can vary from 1 to 7. Assume that demand paging is used. Your program should read input.txt from the same directory and generate output.txtin the same directory. Formats are like below:

### input.txt
3               <- # of page frames
1 2 3 4 1 3     <- Page reference string (a space separates requests)

### output.txt
FIFO: 5         }
LRU: 5          } # of page faults
Optimal: 4      }

