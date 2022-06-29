// AUTHOR:      Robert Brown brownr4000
// PROGRAM:     ThreadSync.cpp
// DATE:        Created 05/26/2021
// PURPOSE:     The purpose of ThreadSort.cpp is to design a multithreaded
//              program that utilizes a shared variable allowed_ID to track the
//              synchronization of three separate threads. Each thread accesses
//              the allowed_ID and displays a message based on whether its
//              passed value is equal to the shared value or not. This process
//              is repeated twice for each of the three threads.
// INPUT:       None.
// PROCESS:     The main program creates three threads and runs them while a
//              set of counter variables are incremented until the end
//              condition is met.
// OUTPUT:      Displays the results to the screen.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

void welcome();
// Prints welcome message.

void goodbye();
// Prints goodbye message.

void threadMessage(int);
// Prints a message about the thread being ran, based on the passed in integer
// and the current allowedID
// IN: The integer value of the thread trying to be ran
// MODIFY: The allowedID variable
// OUT: None

// Global variables
const int MAX_RUN = 2;  // Constant for maximum number of runs
int allowedID = 1;      // Initial value for allowedID

// Counter variables to hold thread run count
int thdCount1 = 0, thdCount2 = 0, thdCount3 = 0;

// Global mutex object
mutex yoke;

// Condition variable to control mutex
condition_variable cond1;
condition_variable cond2;
condition_variable cond3;

int main()
{
    // Call welcome function
    welcome();

    // Create three thread objects
    thread syncOne, syncTwo, syncThree;

    // while loop to run threads until maximum runs occurs
    while (thdCount1 != MAX_RUN && thdCount2 != MAX_RUN && thdCount3 != MAX_RUN)
    {
        // Assign threads to call threadMessage function with a passed in value
        syncOne = thread(threadMessage, 1);
        syncTwo = thread(threadMessage, 2);
        syncThree = thread(threadMessage, 3);

        // Join threads
        syncOne.join();
        syncTwo.join();
        syncThree.join();
    }

    // Call goodbye function
    goodbye();

    return 0;
}

void welcome()
{
    cout << "This is a multithreading program that explores "
            "synchronization challenges.\nThis program runs three" <<
            " threads with each printing a message, two times before\n"
            "the program terminates.\n" << endl;
}

void goodbye()
{
    cout << "\nGoodbye, and thank you for using this program."
         << endl;
}

void threadMessage(int idx)
{
    // Create unique lock object for condition variables
    unique_lock<mutex> pause(yoke);

    // Comparing passed in index to allowedID value
    if (allowedID != idx)
    {
        cout << "Not thread " << idx << "'s turn!" << endl;

        // When values are not equal, create wait lock on condition
        if (idx == 1)
        {
            cond1.wait(pause);
        }
        else if (idx == 2)
        {
            cond2.wait(pause);
        }
        else if (idx == 3)
        {
            cond3.wait(pause);
        }
    }

    // Printing Thread message when allowedID and index are equal
    cout << "Thread " << idx << "'s turn!" << endl;

    // Scheduling next thread according to the value of allowedID
    // Incrementing thread run counter, and resetting allowedID
    if (allowedID == 3)
    {
        thdCount3++;
        allowedID = 1;
        cond1.notify_one();
    }
    else if (allowedID == 1)
    {
        thdCount1++;
        allowedID = 2;
        cond2.notify_one();
    }
    else if (allowedID == 2)
    {
        thdCount2++;
        allowedID = 3;
        cond3.notify_one();
    }

    if ((thdCount1 == MAX_RUN && idx == 1) ||
        (thdCount2 == MAX_RUN && idx == 2) ||
        (thdCount3 == MAX_RUN && idx == 3))
        cout << "Thread " << idx << " complete." << endl;

    // Release unique lock object
    pause.unlock();
}
