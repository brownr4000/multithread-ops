# Multithreaded Sort
This is a program designed to sort an array using a multithreaded solution,
with a specification as follows:

A list of integers is divided into two smaller lists of equal size. Two
separate threads (which we will term sorting threads) sort each sublist using
a sorting algorithm of your choice. The two sublists are then merged by a
third thread —a merging thread — which merges the two sublists into a single
sorted list. Because global data are shared across all threads, perhaps the
easiest way to set up the data is to create a global array. Each sorting
thread will work on half of this array. A second global array of the same size
as the unsorted integer array will also be established. The merging thread will
then merge the two sublists into this second array.

This programming project will require passing parameters to each of the sorting
threads. In particular, it will be necessary to identify the starting index
from which each thread is to begin sorting. The parent thread will output the
sorted array once all sorting threads have exited.

## About this program

This program was written in C++, and utilizes the [thread](https://www.cplusplus.com/reference/thread/thread/)
library.

The sorting algorithm is based on a modified [Merge Sort](https://www.geeksforgeeks.org/merge-sort-using-multi-threading/), where each half of the array is passed into a separate thread.
