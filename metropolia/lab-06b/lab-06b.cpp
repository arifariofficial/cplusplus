/*
Implement class Day to hold calendar events of one day. The class should have at least the following members:

class Day {
public:
    Day();
    bool from_str(const string &s);
    string to_str();
    void dst(int offset);
private:
    int day;
    string month;
    vector<Time> list;
};

Member list is used to store times of event on a day. Note that we don’t store event names only starting time of
each event.
Member function from_str reads events from a string. All existing data (date and event times) are erased by
from_str before it makes an attempt to read data. The function returns true if date and at least one event time
was successfully read otherwise the function returns false. Function sorts the event times in ascending order
before returning.
The string from which to read contains day and month separated by spaces and a list of events start times
separated by spaces.

For example:
13 January 12:00 14:45
14 January 09:00 11:30 13:15 16:00 12:00
1 February 19:00 21:30
2 February 12:00 14:45
1 April 10:00 11: Broken
1 May 8:00 17:55
2 May 00:01 22:00 13:05
7 May Broken
28 May 10:00 17:45

In the example above there is one completely incorrect line (May 7th) that should be completely ignored and one
partially incorrect line (April 1st) where the last time is invalid and should be ignored.
Member function to_str returns a string of event times. The format of the string is the same as from_str input
string format: day and month separated by spaces followed by a list of event times separated by spaces.
Member function dst adds an offset to times. The offset is number of hours to add. Note that the function needs
to roll time properly over 24:00, but it does not need to change the date on roll over.
Test your class with the following code and with different data files.

int main() {
    ifstream inputFile("calendar.txt");

    if (!inputFile.is_open()) {
        cout << "Unable to open file" << endl;
        return 1;
    }

    string line;
    vector<Day> cal;
    Day day;

    while (getline(inputFile, line)) {
        if (day.from_str(line)) {
            cal.push_back(day);
        }
    }
    cout << "Calendar" << endl;

    for (auto &e: cal) {
        cout << e.to_str() << endl;
    }

    // DST shift
    for (auto &e: cal) {
        e.dst(1);
    }
    cout << "DST" << endl;

    for (auto &e: cal) {
        cout << e.to_str() << endl;
    }

    cout << "End" << endl;

    return 0;
}

Example test output:
Calendar
13 January 12:00 14:45
14 January 09:00 11:30 12:00 13:15 16:00
1 February 19:00 21:30
2 February 12:00 14:45
1 April 10:00
1 May 08:00 17:55
2 May 00:01 13:05 22:00
28 May 10:00 17:45
DST
13 January 13:00 15:45
14 January 10:00 12:30 13:00 14:15 17:00
1 February 20:00 22:30
2 February 13:00 15:45
1 April 11:00
1 May 09:00 18:55
2 May 01:01 14:05 23:00
28 May 11:00 18:45
End
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include "Time.h"

using namespace std;

class Day {
public:
    Day();
    bool from_str(const string &s);
    [[nodiscard]] string to_str() const;
    void dst(int offset);
private:
    int day{};
    string month;
    vector<Time> list;
};

int main() {
    ifstream inputFile("/Users/ari/Desktop/cplusplus/metropolia/lab-06b/lab6_calendar.txt");

    if (!inputFile.is_open()) {
        cout << "Unable to open file" << endl;
        return 1;
    }

    string line;
    vector<Day> cal;
    Day day;

    while (getline(inputFile, line)) {
        if (day.from_str(line)) {
            cal.push_back(day);
        }
    }
    cout << "Calendar" << endl;

    for (auto &e: cal) {
        cout << e.to_str() << endl;
    }

    // DST shift
    for (auto &e: cal) {
        e.dst(1);
    }
    cout << "DST" << endl;

    for (auto &e: cal) {
        cout << e.to_str() << endl;
    }

    cout << "End" << endl;

    return 0;
}

Day::Day() = default;

// Parse a string to extract the day, month, and times
bool Day::from_str(const string &s) {
    stringstream ss(s);
    string token;

    // Clear existing data
    list.clear();
    day = 0;
    month = "";

    // Extract the day and month
    ss >> day >> month;
    if (ss.fail()) return false;  // Check if day or month is invalid

    // Parse and add times to the list
    while (ss >> token) {
        if (Time time; time.from_str(token)) {  // Check if the time is valid
            list.push_back(time);
        }
    }

    // If no valid times were added, return false
    if (list.empty()) {
        return false;
    }

    // Sort times in ascending order
    sort(list.begin(), list.end());

    return true;
}

// Convert the Day object back to a string
string Day::to_str() const {
    stringstream ss;
    ss << day << " " << month;
    for (const auto &time : list) {
        ss << " " << time.to_str();  // Use time.to_str() to convert time to a string
    }
    return ss.str();
}

// Adjust times for DST (Daylight Saving Time) by adding the offset in hours
void Day::dst(int offset) {
    for (auto &time : list) {
        time.dst(offset);  // Apply DST adjustment to each time
    }

    // Sort the list of times again after adjustment
    sort(list.begin(), list.end());
}