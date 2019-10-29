# Lab 06 - Deadlocks

Apply deadlock/starvation avoidance and process/thread condition variables to a real-world example.

### Task

**Part 1**

• A single-lane bridge connects the two Vermont villages of North Tunbridgeand South Tunbridge. Farmers in the two villages use this bridge to deliver their produce to the neighboring town. 

• The bridge can become deadlocked if a northbound and a southbound farmer get on the bridge at the same time. (Vermont farmers are stubborn and are unable to back up.)

• Using semaphoresand/or mutexlocks, design an algorithm in pseudocodethat prevents deadlock. Initially, do not be concerned about starvation (the situation in which northbound farmers prevent southbound farmers from using the bridge, or vice versa).

**Part 2**

• Modify Part 1 such that it is starvation-free.

