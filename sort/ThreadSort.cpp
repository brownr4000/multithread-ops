// AUTHOR:      Robert Brown brownr4000
// PROGRAM:     ThreadSort.cpp
// DATE:        Created 05/17/2021
// PURPOSE:     The purpose of ThreadSort.cpp is to design a multithreaded
//              program that utilizes a mergesort algorithm to sort a list of
//              integers stored in an array. It uses two separate threads to
//              sort a sublist of the main list, and a third thread to merge
//              into a single list.
// INPUT:       The user inputs the number of elements in the list, then the
//              integer numbers to populate the list.
// PROCESS:     The program utilizes a mergesort algorithm to sort the array,
//              after getting input from the user.
// OUTPUT:      Displays the results to the screen.
//

#include <iostream>
#include <vector>
#include <thread>
#include <sstream>

using namespace std;

void welcome();
// Prints welcome message.

void goodbye();
// Prints goodbye message.

int getArrSize();
// Asks the user to input the size of the array.
// IN: None
// MODIFY: None
// OUT: The integer size of the array

string getArrElements();
// Asks the user to enter elements to populate the array.
// IN: None
// MODIFY: None
// OUT: A string containing the user input

int * populateArray(int size);
// Populate an array with input from user based on the given size
// IN: The integer value for the size of the array
// MODIFY: None
// OUT: The populated integer array of the given size

void displayArray(int * arr, int size);
// Display contents of array to the screen.
// IN: The integer array to display, and its size.
// MODIFY: None
// OUT: None

void merge(int * arr, int left, int mid, int right);
// Merges two subarrays from the passed in array
// IN: The integer value of the thread trying to be ran
// MODIFY: The allowedID variable
// OUT: None

void mergeSort(int * arr, int left, int right);
// Calculates the middle of the passed in array, creates threads to sort
// the two subarray, and then creates a thread to merge the subarrays into one
// sorted array.
// IN: The integer array to be sorted, and the integer value of its left and
//     right index.
// MODIFY: The integer array
// OUT: None

void threadSort(int * arr, int size);
// Recursively calls the mergeSort using the passed in integer array.
// IN: The integer array to be sorted, and the integer value of its size.
// MODIFY: The integer array
// OUT: None


int main()
{
    // Call welcome function
    welcome();

    // Integer to hold the size of the array
    int size = getArrSize();

    // Integer array to hold user input
    int * numberArray = populateArray(size);

    // Display message to the user, and call displayArray function
    // to display initial array
    cout << "\nThe unsorted array is: " << endl;
    displayArray(numberArray, size);

    // Display information about the array size to user
    cout << "\nThe size of the array is: " << size << endl;
    cout << "The size of the subarray is: " << size/2 << endl;

    // Call threadSort function to sort array
    threadSort(numberArray, size);

    // Display message to the user, and call displayArray function
    // to verify sorted array
    cout << "\nThe sorted array is: " << endl;
    displayArray(numberArray, size);

    // Call goodbye function
    goodbye();

    return 0;
}

void welcome()
{
    cout << "This is a multithreaded program that sorts the elements "
            "\nof a user generated list of numbers.\n" << endl;
}

void goodbye()
{
    cout << "\nGoodbye, and thank you for using this program."
         << endl;
}

int getArrSize()
{
    int num;    // Integer to hold user input

    // Prompt user for integer input
    cout << "Please enter the number of elements to be sorted: ";
    cin >> num;

    cin.ignore();   // Clear cin after integer input

    return num;
}

string getArrElements()
{
    string input;   // String to hold user input

    // Prompt user to enter a string of numbers, and store the whole line
    cout << "Please enter integer numbers (enter/return to continue): ";
    getline(cin, input);

    return input;
}

int * populateArray(int size)
{
    int * temp; // Temporary array to hold elements
    int num;    // Integer to hold element values from stringstream

    // Create stringstream object by calling getArrElements function
    stringstream ss(getArrElements());

    // for loop to traverse stringstream and populate array with integer values
    for (int i = 0; i < size; i++)
    {
        ss >> num;

        temp[i] = num;
    }

    return temp;
}

void displayArray(int * arr, int size)
{
    // for loop to traverse and display array contents
    for (int i = 0; i < size; i++)
        cout << arr[i] << "\t";
    cout << endl;
}

void threadSort(int * arr, int size)
{
    // Call mergeSort function by passing array indices base on its size
    mergeSort(arr, 0, size - 1);
}

void mergeSort(int * arr, int left, int right)
{
    // Check to ensure that left index is greater than right index
    if (left < right)
    {
        // Compute middle index
        int mid = (left + right) / 2;

        // Create two threads for recursive mergeSort function call by passing
        // middle index value
        thread th1(mergeSort, arr, left, mid);
        thread th2(mergeSort, arr, mid + 1, right);
        th1.join();
        th2.join();

        // Create third thread for call to merge function for the array
        thread th3(merge, arr, left, mid, right);
        th3.join();
    }
}

void merge(int * arr, int left, int mid, int right)
{
    // Create variables to calculate size of left and right subarrays
    int sizeLeft = mid - left + 1;
    int sizeRight = right - mid;

    // Create temporary arrays
    int * leftArr = new int[sizeLeft];
    int * rightArr = new int [sizeRight];

    // for loop to populate left subarray with copied data from original array
    for (int i = 0; i < sizeLeft; i++)
    {
        leftArr[i] = arr[i + left];
    }

    // for loop to populate right subarray with copied data from original array
    for (int i = 0; i < sizeRight; i++)
    {
        rightArr[i] = arr[i + mid + 1];
    }

    // Integers to store initial indices
    int i = 0;      // for left subarray
    int j = 0;      // for right subarray
    int k = left;   // for merged array

    // while loop to combine left and right subarray into merged array
    while (i < sizeLeft && j < sizeRight)
    {
        if (leftArr[i] <= rightArr[j])
            arr[k++] = leftArr[i++];
        else
            arr[k++] = rightArr[j++];
    }

    // while loop to merge remaining elements of left subarray
    while (i < sizeLeft)
    {
        arr[k++] = leftArr[i++];
    }

    // while loop to merge remaining elements of right subarray
    while (j < sizeRight)
    {
        arr[k++] = rightArr[j++];
    }
}
