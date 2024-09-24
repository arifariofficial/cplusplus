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