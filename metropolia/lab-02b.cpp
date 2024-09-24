/*
Write a program that reads strings from the keyboard. There is no upper limit for the number of strings. All
strings are stored in a vector of strings. The data entry phase terminates when the user enters the “stop” string.
This termination string is not stored in the vector.
When all strings have been entered the program displays all strings from the vector and the number of strings
entered. Then the program finds out the longest string from the array and prints the longest string and its length.
The last thing the program does is that it displays the values returned by the member functions size and capacity
of the vector.
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    vector<string> strings;
    cout << "Enter strings (or 'stop' to end): ";
    string input;
    while (cin >> input && input != "stop") {
        strings.push_back(input);
    }

    cout << "Entered strings:" << endl;
    for (const auto &s: strings) {
        cout << s << endl;
    }

    cout << "Number of strings entered: " << strings.size() << endl;

    int longestLength = 0;
    string longestString;
    for (const auto &s: strings) {
        if (s.length() > longestLength) {
            longestLength = s.length();
            longestString = s;
        }
    }
    cout << "Longest string: " << longestString << ", length: " << longestLength << endl;

    cout << "Vector size: " << strings.size() << ", capacity: " << strings.capacity() << endl;

    return 0;
}