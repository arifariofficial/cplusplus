#include "Time.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

// Overload the << operator for the Time class to handle output
ostream& operator<<(ostream& os, const Time& s) {
    os << setfill('0') << setw(2) << s.hour << ":" << setfill('0') << setw(2) << s.minute;
    return os;
}

// Overload the >> operator for the Time class to handle input
istream& operator>>(istream& in, Time& s) {
    char colon;
    in >> s.hour >> colon >> s.minute;
    return in;
}

// Default constructor
Time::Time() : hour(0), minute(0) {}

// Parse time from a string in the format "hh:mm"
bool Time::from_str(const string &timeStr) {
    char colon;
    stringstream ss(timeStr);
    ss >> hour >> colon >> minute;
    return !ss.fail() && colon == ':' && hour >= 0 && hour < 24 && minute >= 0 && minute < 60;
}

// Convert time to string in the format "hh:mm"
string Time::to_str() const {
    stringstream ss;
    ss << setfill('0') << setw(2) << hour << ":" << setfill('0') << setw(2) << minute;
    return ss.str();
}

// Adjust time by adding an offset in hours, handling wrap-around past 24 hours
void Time::dst(int offset) {
    hour = (hour + offset) % 24;
    if (hour < 0) hour += 24;  // Handle negative hour wrap-around
}

// Comparison operator to compare two times
bool Time::operator<(const Time &other) const {
    return (hour < other.hour) || (hour == other.hour && minute < other.minute);
}


// Function to read time from input with a prompt
void Time::read(const char* s) {
    cout << s << " (in hh:mm format): ";
    char separator;
    cin >> hour >> separator >> minute;
    if (separator != ':') {
        cout << "Invalid format! Please enter time as hh:mm." << endl;
    }
    normalizeTime();
}

// Function to check if one time is less than another time
bool Time::lessThan(const Time &t) const {
    return hour < t.hour || (hour == t.hour && minute < t.minute);
}

// Function to subtract two times
Time Time::subtract(const Time &t) const {
    const int totalMinutes1 = hour * 60 + minute;
    const int totalMinutes2 = t.hour * 60 + t.minute;
    int diffMinutes = totalMinutes1 - totalMinutes2;

    if (diffMinutes < 0) {
        diffMinutes += 24 * 60;  // Handle subtraction across midnight
    }

    Time result;
    result.hour = diffMinutes / 60;
    result.minute = diffMinutes % 60;

    return result;
}

// Function to display the time using the overloaded output operator
void Time::display() const {
    cout << *this;
}

// Operator to subtract two times using '-'
Time Time::operator-(const Time &t) const {
    return this->subtract(t);
}

// Pre-increment operator (++time)
Time &Time::operator++() {
    ++minute;
    normalizeTime();
    return *this;
}

// Post-increment operator (time++)
Time Time::operator++(int) {
    Time temp = *this;
    ++minute;
    normalizeTime();
    return temp;
}

// Normalize the time (handle overflow and underflow in hours and minutes)
void Time::normalizeTime() {
    if (minute >= 60) {
        hour += minute / 60;
        minute %= 60;
    }
    if (minute < 0) {
        hour--;
        minute += 60;
    }
    if (hour >= 24) {
        hour %= 24;
    }
    if (hour < 0) {
        hour += 24;
    }
}
