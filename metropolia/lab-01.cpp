/* Exercise 1 (Basic input and output, arrays and pointers 4p)
*
* Write a program that first asks from the user how many numbers he needs. After that the program allocates
* memory space to store those numbers (integer array). Next the program fills the array with random numbers
* between 0 - 99, and the program displays all numbers from the array. After that the program calculates the
* mean of the generated number calling a separate function, int mean(int *array, int n). Finally, the program
* must free the memory space it allocated. There is rand() function for generating random numbers. Limiting
* the range to [0,99] is done with rand() % 100. In order to use rand() function you must include cstdlib header.
*/

#include <iostream>
#include <cstdlib>
using namespace std;

int mean(const int *array, int n);

int main() {
    cout << "How many numbers would you like to enter? : ";
    int size;
    cin >> size;

    int *arr = new int[size]; // Dynamically allocate memory for the array

    srand((time(nullptr))); // Seed the random number generator

    // Fill the array with random numbers between 0 and 99
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }

    // output the array
    cout << "Array elements: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }

    cout << "\nMean: " << mean(arr, size); // Calculate and output the mean

    delete[] arr; // Deallocate the dynamically allocated memory

    return 0;
}

// Function to calculate the mean of an array
int mean(const int *array, const int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += array[i];
    }
    return sum / n;
}