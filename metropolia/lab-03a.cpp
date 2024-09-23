/*
Write a program that defines a vector of double. The program asks user to enter numbers and stores the numbers
in the vector. The program stops asking numbers when user enter a negative number. The negative number is not
stored the vector.
When program has finished asking numbers it sorts the numbers. After sorting the program prints the numbers on
separate lines with 3 decimal precision.
Iomanipulators can be used to change formatting of output (and input) streams.
See http://www.cplusplus.com/reference/iomanip/setprecision/ for an example.
 */


#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
 vector<double> numbers;
 double number;

 cout << "Enter numbers (negative number to stop): ";
 while (cin >> number && number >= 0) {
  numbers.push_back(number);
  cout << "Enter numbers (negative number to stop): ";
 }
 cout << "Entered numbers:" << endl;
 for (const auto &num : numbers) {
  cout << fixed << setprecision(3) << num << endl;
 }
 ranges::sort(numbers);
 cout << "Sorted numbers:" << endl;
 for (const auto &num : numbers) {
  cout << fixed << setprecision(3) << num << endl;
 }

 return 0;
}