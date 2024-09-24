/*
We need to write an application, which reads two times (times are represented by two integers: hours and minutes).
Then the program finds out which time is later. After that it calculates the time difference between these times.
Finally, the program displays the smaller (earlier) time and the time difference (duration) in the format
starting time was 11:22
duration was 1:04

The main function that does these things looks as follows:

int main() {
    Time time1, time2, duration;

    time1.read("Enter time 1");
    time2.read("Enter time 2");
    if (time1.lessThan(time2)) {
        duration = time2.subtract(time1);
        cout << "Starting time was ";
        time1.display();
    } else {
        duration = time1.subtract(time2);
        cout << "Starting time was ";
        time2.display();
    }
    cout << "Duration was ";
    duration.display();
    return 0;
}
Now you need to define and implement class Time so that the program starts working. As can be seen from the main
function, class Time has the following member functions:
1. read that is used to read time (minutes and hours) from the keyboard.
2. lessThan that is used to compare two times.
3. subtract that is used to calculate time difference between two times.
4. display that is used to display time in the format hh:mm

If you want to display time values in two character fields with leading ’0’, use the following formatting
commands: cout << setiosflags(ios::right);
cout << setfill('0') << setw(2) << hours;
cout << ":" << setfill('0') << setw(2) << minutes;
Note you also need to include <iomanip>
 */

#include <iostream>
#include <iomanip>

using namespace std;

class Time {
    int hours, minutes;
public:
    void read(const string &prompt) {
        cout << prompt << " (in hh:mm format): ";
        char separator; // to store the colon (':') between hours and minutes
        cin >> hours >> separator >> minutes;
        // Optionally, you can validate the separator to ensure it's a ':'
        if (separator != ':') {
            cout << "Invalid format! Please enter time as hh:mm." << endl;
        }
    }

    [[nodiscard]] bool lessThan(const Time other) const {
        return (hours < other.hours) || (hours == other.hours && minutes < other.minutes);
    }
    [[nodiscard]] Time subtract(const Time other) const {
        Time result;

        // Convert both times to total minutes since midnight
        const int totalMinutes1 = hours * 60 + minutes;
        const int totalMinutes2 = other.hours * 60 + other.minutes;

        int diffMinutes;

        // If the current time is earlier, calculate the time difference across midnight
        if (totalMinutes1 >= totalMinutes2) {
            diffMinutes = totalMinutes1 - totalMinutes2;
        } else {
            diffMinutes = (24 * 60 - totalMinutes2) + totalMinutes1;
        }

        // Convert the difference back to hours and minutes
        result.hours = diffMinutes / 60;
        result.minutes = diffMinutes % 60;

        return result;
    }
    void display() const {
        cout << setiosflags(ios::right);
        cout << setfill('0') << setw(2) << hours << ":" << setfill('0') << setw(2) << minutes;
    }
    Time() {
        hours = minutes = 0;
    }
    Time(const int h, const int m) {
        hours = h;
        minutes = m;
    }
    ~Time() = default;
};

int main() {
    Time time1, time2, duration;

    time1.read("Enter time 1");
    time2.read("Enter time 2");
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
    return 0;
}