/*
Improve class you wrote in exercise 4 by adding overloaded operators. The operators to add are:
1. Output operator ( << ) that outputs the time in two character fields with leading zeros and separates the
fields with a colon.
2. Comparison operator less than ( < ) that compares two times
3. Addition operator ( + ) that adds two times
4. Subtract operator ( - ) that subtracts two times.
5. Pre- and post-increment operators ( ++ ). Both operators increment the time by one minute
Your class should work with the test program below. Note that your class must have a default constructor that
initializes time to 0:00.
Addition must make times to roll over to “next day” but doesn’t have to keep track of days. For example,
adding 14:30 and 13:45 should result in 4:15 or adding 18:30 and 5:37 should yield 0:07.
 */

#include <iostream>
#include <iomanip>

using namespace std;

class Time {
    int hours, minutes;
    // Helper function to normalize time when hours or minutes go beyond valid ranges
    void normalizeTime() {
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        }
        if (hours >= 24) {
            hours %= 24; // Roll over hours beyond 24 to the next day
        }
        if (minutes < 0) {
            hours--;
            minutes += 60;
        }
        if (hours < 0) {
            hours += 24; // Handle negative hours by rolling back the day
        }
    }
public:
    // Constructors
    Time() : hours(0), minutes(0) {
    }
    Time(const int h, const int m) : hours(h), minutes(m) { normalizeTime(); }

    // Output operator (<<) to display the time
    friend ostream &operator<<(ostream &out, const Time &t) {
        out << setfill('0') << setw(2) << t.hours << ":" << setfill('0') << setw(2) << t.minutes;
        return out;
    }

    // Input operator to read time in hh:mm format
    void read(const string &prompt) {
        cout << prompt << " (in hh:mm format): ";
        char separator; // to store the colon (':') between hours and minutes
        cin >> hours >> separator >> minutes;
        // Validate the separator to ensure it's a ':'
        if (separator != ':') {
            cout << "Invalid format! Please enter time as hh:mm." << endl;
        }
        normalizeTime();
    }

    // Comparison operator (less than)
    [[nodiscard]] bool operator<(const Time other) const {
        return (hours < other.hours) || (hours == other.hours && minutes < other.minutes);
    }
    // Addition operator (+) to add two times
    Time operator+(const Time &other) const {
        Time result;
        result.hours = hours + other.hours;
        result.minutes = minutes + other.minutes;
        result.normalizeTime();
        return result;
    }

    // Subtraction operator (-) to subtract two times
    Time operator-(const Time &other) const {
        Time result;
        int totalMinutes1 = hours * 60 + minutes;
        int totalMinutes2 = other.hours * 60 + other.minutes;
        int diffMinutes = totalMinutes1 - totalMinutes2;

        if (diffMinutes < 0) {
            diffMinutes += 24 * 60; // Handle negative difference by rolling back to previous day
        }

        result.hours = diffMinutes / 60;
        result.minutes = diffMinutes % 60;
        return result;
    }

    // Pre-increment operator (++time)
    Time &operator++() {
        ++minutes;
        normalizeTime();
        return *this;
    }

    // Post-increment operator (time++)
    Time operator++(int) {
        const Time temp = *this;
        ++minutes;
        normalizeTime();
        return temp;
    }

    // Function to display time (if needed for manual calls)
    void display() const {
        cout << *this; // Leverage the overloaded output operator (<<)
    }

    // Destructor
    ~Time() = default;
};

void print(const vector<Time> &v) {
    for (auto &t: v) {
        cout << t << endl;
    }
}

int main() {
    Time time1, time2, duration;

    time1.read("Enter time 1");
    time2.read("Enter time 2");

    if (time1 < time2) {
        duration = time2 - time1;
        cout << "Starting time was " << time1 << endl;
    } else {
        duration = time1 - time2;
        cout << "Starting time was " << time2 << endl;
    }
    cout << "Duration was " << duration << endl;

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