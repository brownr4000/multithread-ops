# Multithreaded Synchronization

This is a program designed to answer the following question, exploring
synchronization using multithreading:

Assume that we have a shared variable allowed_ID.
This variable is initialized to 1 at the beginning. Now create three threads
in your program and assign ID 1,2,3 to them, respectively. Pass the ID as a
parameter when you create the threads. Each of the threads will try to access
the variable “allowed_ID.” Whenever a thread reads this variable, it checks
whether the allowed_ID is equal to its ID or not. If, for example, thread 2
reads allowed_ID and sees that this variable is not 2, it prints “Not thread
2’s turn” and releases the variable. Otherwise, thread 2 prints “Thread 2’s
turn!” and increases the allowed_ID by 1, and releases the variable. However,
after increasing allowed_ID by 1, if it is 4, the thread will reset the
variable to 1 before releasing the variable. The program should execute until
each thread prints “Thread i’s turn!” two times. Once a thread prints this
message twice, it terminates.

## About this program

This program was written in C++, and utilizes the [thread](https://www.cplusplus.com/reference/thread/thread/)
library.
