/*
Improve class you wrote in exercise 4&5 by adding overloaded operators and by splitting it to header and source
files.
The operators to add are:
1. Input operator ( >> ) that extracts time from a stream. The format of the time in the stream is assumed to be
same as output (two numbers separated by a colon).
2. Comparison operator greater than ( > ) that compares two times
3. Comparison operator equal to ( == ) that compares two times
4. Implement a constructor that takes hours and minutes as parameter
Header should only contain class definition and possibly some includes required by the definition. In the example
below #pragma once is MSVC specific pragma that works the same way as header guards after the pragma. The header
guards are used to prevent including same header multiple times. Note that header should not contain any code that
can be executed i.e. no function implementations.

#pragma once
#ifndef TIME_H
#define TIME_H
class Time {
    friend std::ostream &operator<<(std::ostream &out, const Time &s);
    friend std::istream &operator>>(std::istream &in, Time &s);
public:
    Time();
    void read(const char *s);
    [[nodiscard]] bool lessThan(const Time &t) const;
    [[nodiscard]] Time subtract(const Time &t) const;
    void display() const;
    bool operator<(const Time &t) const;
    Time operator-(const Time &t) const;
    Time operator+(const Time &t) const;
    Time &operator++();
    Time operator++(int);

private:
    int hour;
    int min;
    void normalizeTime();
};

#endif

The source file includes library headers that are needed for the implementation of functions and also includes the
header of the class it is implementing. A common practice is to name the files by the class they are implementing.
For example, class Time is defined and implemented in Time.h and Time.cpp.

#include <iostream>
#include <iomanip>
#include "Time.h"
using namespace std;

// Default constructor
Time::Time() : hour(0), min(0) {}

// Output operator (<<) overloaded to display time in the format hh:mm
ostream &operator<<(std::ostream &out, const Time &s) {
    out << std::setfill('0') << std::setw(2) << s.hour << ":"
        << std::setfill('0') << std::setw(2) << s.min;
    return out;
}

// Input operator (>>) overloaded to read time from a stream
istream &operator>>(std::istream &in, Time &t) {
    char separator;
    in >> t.hour >> separator >> t.min;
    if (separator != ':' || t.min < 0 || t.min >= 60 || t.hour < 0 || t.hour >= 24) {
        std::cerr << "Invalid time format! Please enter time as hh:mm." << std::endl;
        in.setstate(std::ios::failbit);
    }
    return in;
}

void Time::read(const char* s) {
    cout << s <<" (in hh:mm format): ";
    char separator; // to store the colon (':') between hours and minutes
    cin >> hour >> separator >> min;
    // Validate the separator to ensure it's a ':'
    if (separator != ':') {
        cout << "Invalid format! Please enter time as hh:mm." << endl;
    }
    normalizeTime();
}

// Function to check if one time is less than another time
bool Time::lessThan(const Time &t) const {
    return hour < t.hour || (hour == t.hour && min < t.min);
}

// Function to subtract two times
Time Time::subtract(const Time &t) const {
    const int totalMinutes1 = hour * 60 + min;
    const int totalMinutes2 = t.hour * 60 + t.min;
    int diffMinutes = totalMinutes1 - totalMinutes2;

    if (diffMinutes < 0) {
        diffMinutes += 24 * 60;  // Handle subtraction across midnight
    }

    // Create a new Time object
    Time result{};
    result.hour = diffMinutes / 60;  // Set the hours manually
    result.min = diffMinutes % 60;   // Set the minutes manually

    return result;
}
// Function to display the time
void Time::display() const {
    cout << *this;  // Use the overloaded output operator
}

// Operator less than overloaded to compare two times
bool Time::operator<(const Time &t) const {
    return (hour < t.hour) || (hour == t.hour && min < t.min);
}

// Operator to subtract two times using '-'
Time Time::operator-(const Time &t) const {
    return this->subtract(t);
}
// Operator to add two times using '+'
Time Time::operator+(const Time &t) const {
    return this->subtract(t.subtract(*this));
}

// Pre-increment operator (++time)
Time &Time::operator++() {
    ++min;
    normalizeTime();
    return *this;
}

// Post-increment operator (time++)
Time Time::operator++(int) {
    const Time temp = *this;
    ++min;
    normalizeTime();
    return temp;
}

// Normalize the time (handle overflow and underflow in hours and minutes)
void Time::normalizeTime() {
    // Handle overflow of minutes
    if (min >= 60) {
        hour += min / 60;
        min %= 60;
    }

    // Handle negative minutes
    if (min < 0) {
        hour--;
        min += 60;
    }

    // Handle overflow of hours (wrap around 24-hour clock)
    if (hour >= 24) {
        hour %= 24;
    }

    // Handle negative hours (roll back to the previous day)
    if (hour < 0) {
        hour += 24;
    }
}
 */

#include <iostream>
#include "Time.h"
using namespace std;

// Function to read time from user and validate it
void print(const vector<Time> &v) {
    for (auto &t: v) {
        cout << t << endl;
    }
}

int main() {
    cout << "Program 1" << endl;
    Time time1, time2, duration;

    time1.read("Enter time 1: ");
    time2.read("Enter time 2: ");

    if (time1.lessThan(time2)) {
        duration = time2.subtract(time1);
        cout << "Starting time was ";
        time1.display();
    } else {
        duration = time1.subtract(time2);
        cout << "Starting time was ";
        time2.display();
    }

    cout << "\nDuration was ";
    duration.display();

    cout << "\nProgram 2" << endl;
    Time time3, time4, duration2;

    time3.read("Enter time 1: ");
    time4.read("Enter time 2: ");

    if (time3 < time4) {
         duration2 = time4 - time3;
        cout << "Starting time was " << time3 << endl;
    } else {
        duration = time3 - time4;
        cout << "Starting time was " << time4 << endl;
    }
    cout << "Duration was " << duration2 << endl;

    vector<Time> tv(5);
    for (auto &t: tv) {
        t.read("Enter time:");
    }

    cout << "Times: " << endl;
    print(tv);

    Time sum;
    for (auto t: tv) {
        sum = sum + t;
    }

    cout << "Sum of times: " << sum << endl;

    cout << "Post-increment: " << endl;
    print(tv);

    for (auto &t: tv) {
        cout << t++ << endl;
    }

    print(tv);

    cout << "Pre-increment: " << endl;
    for (auto &t: tv) {
        cout << ++t << endl;
    }

    sort(tv.begin(), tv.end());

    cout << "Sorted times: " << endl;
    print(tv);

    return 0;
}