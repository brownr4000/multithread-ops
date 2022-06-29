// AUTHOR:      Robert Brown brownr4000
// PROGRAM:     ThreadStats.cpp
// DATE:        Created 05/17/2021
// PURPOSE:     The purpose of ThreadStats.cpp is to design a multithreaded
//              program that calculates various statistical values for a list
//              of numbers. This program will take a series of numbers on the
//              command line and creates three separate worker threads.
//              One thread will determine the average of the numbers,
//              the second will determine the maximum value, and the third will
//              determine the minimum value.
// INPUT:       None.
// PROCESS:     The program asks for user input to populate a vector, and
//              creates three threads to find the average, minimum and maximum
//              values utilizing the appropriate function.
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

string getUserInput();
// Asks the user to enter elements to populate the vector.
// IN: None
// MODIFY: None
// OUT: A string containing the user input

void displayVector(vector<int> numList);
// Display contents of vector to the screen.
// IN: The integer vector to display.
// MODIFY: None
// OUT: None

vector<int> populateVector();
// Populate a vector with integer values.
// IN: None
// MODIFY: None
// OUT: The populated integer vector

void averageValue(vector<int> numList);
// Calculates the average value of the elements of a vector.
// IN: The integer vector used to calculate its average
// MODIFY: The value of the integer average variable
// OUT: None

void minValue(vector<int> numList);
// Finds the minimum value of the elements of a vector.
// IN: The integer vector used to find its minimum element
// MODIFY: The value of the integer minimum variable
// OUT: None

void maxValue(vector<int> numList);
// Finds the maximum value of the elements of a vector.
// IN: The integer vector used to find its maximum element
// MODIFY: The value of the integer maximum variable
// OUT: None

// Integer variables to store average value, and minimum and maximum elements
int average, minimum, maximum;

int main()
{
    // Call welcome function
    welcome();

    // Create vector object by calling populateVector function
    vector<int> user = populateVector();

    // Call displayVector function to display contents of vector to screen
    displayVector(user);

    // Create threads to call the averageValue, minValue, and maxValue
    // functions for the populated vector
    thread th1(averageValue, user);
    thread th2(minValue, user);
    thread th3(maxValue, user);

    // Join the threads to continue the program
    th1.join();
    th2.join();
    th3.join();

    // Display contents of the integer variables to the screen
    cout << "The average value is " << average << endl;
    cout << "The minimum value is " << minimum << endl;
    cout << "The maximum value is " << maximum << endl;

    // Call goodbye function
    goodbye();

    return 0;
}

void welcome()
{
    cout << "This is a multithreaded program that calculates various "
            "\nstatistical values for a list of numbers.\n" << endl;
}

void goodbye()
{
    cout << "\nGoodbye, and thank you for using this program."
         << endl;
}

string getUserInput()
{
    string input;   // String to hold user input

    // Prompt user to enter a string of numbers, and store the whole line
    cout << "Please enter integer numbers (enter/return to continue): ";
    getline(cin, input);

    return input;
}

void displayVector(vector<int> numList)
{
    // Display message to user
    cout << "\nThe list of numbers is: " << endl;

    for (int i = 0; i < numList.size(); i++)
        cout << numList.at(i) << "\t";
    cout << "\n" << endl;
}

vector<int> populateVector()
{
    vector<int> temp;   // Temporary vector
    int num;            // Integer to hold element values from stringstream

    // Create stringstream object by calling getUserInput function
    stringstream ss(getUserInput());

    // while loop to traverse stringstream and populate vector
    // with integer values
    while (ss >> num)
    {
        temp.push_back(num);
    }

    return temp;
}

void averageValue(vector<int> numList)
{
    double sum = 0; // Double to hold sum of vector elements

    // for loop to traverse vector
    for (int i = 0; i < numList.size(); i++)
    {
        // Add current element to sum variable
        sum += numList.at(i);
    }

    // Calculate the average by dividing sum by the size of the vector
    // and transforming the value into an integer
    average = (int)(sum/numList.size());

}

void minValue(vector<int> numList)
{
    // Set the value of minimum to the first element in the vector
    minimum = numList.at(0);

    // for loop to traverse vector
    for (int i = 1; i < numList.size(); i++)
    {
        // Compare vector element to current minimum value
        // and update minimum if vector element is smaller
        if (numList.at(i) < minimum)
            minimum = numList.at(i);
    }

}

void maxValue(vector<int> numList)
{
    // Set the value of maximum to the first element in the vector
    maximum = numList.at(0);

    // for loop to traverse vector
    for (int i = 1; i < numList.size(); i++)
    {
        // Compare vector element to current maximum value
        // and update maximum if vector element is larger
        if (numList.at(i) > maximum)
            maximum = numList.at(i);
    }
}
