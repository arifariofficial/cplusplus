#include <fstream>
#include <iostream>
#include <sstream>
#include "Time.h"
using namespace std;

class Day {
public:
    Day();
    bool from_str(const string &s);
    string to_str() const;
    void dst(int offset);
private:
    int day;
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

Day::Day(): day(0), month(""), list(0) {
}

bool Day::from_str(const string &s) {
    stringstream ss(s);
    string token;
    list.clear();
    day = 0;
    month = "";

    // Extract the day and month
    ss >> day >> month;
    if (ss.fail()) return false;

    // Parse the rest of the line and extract times
    while (ss >> token) {
        if (Time time; time.from_str(token)) {
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

// Convert the Day object back to string
string Day::to_str() const {
    stringstream ss;
    ss << day << " " << month;
    for (auto &time: list) {
        ss << " " << time.to_str();
    }
    return ss.str();
}

// Adjust time for DST(Daylight Saving Time) by adding the offset in hours
void Day::dst(int offset) {
    for (auto &time: list) {
        time.dst(offset);
    }
    sort(list.begin(), list.end());
}