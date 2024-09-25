#include <iostream>
#include <iomanip>
#include "Time.h"
#include <sstream>

Time::Time(): hour(0), minute(0) {
}

void Time::normalizeTime() {
    if (minute >= 60) {
        hour += minute / 60;
        minute %= 60;
    }
    if (hour >= 24) {
        hour %= 24;
    }
    if (minute < 0) {
        hour--;
        minute += 60;
    }
    if (hour < 0) {
        hour += 24;
    }
}

void Time::read(const char *s) {
    std::cout << s << " (in hh:mm format): ";
    char separator;
    std::cin >> hour >> separator >> minute;
    while (separator != ':' || hour > 24 || minute > 60) {
        std::cout << "Invalid time format" << std::endl;
        std::cout << s << " (in hh:mm format): ";
        std::cin >> hour >> separator >> minute;
    }
}

bool Time::lessThan(const Time &t) const {
    return (hour < t.hour) || (hour == t.hour && minute < t.minute);
}

Time Time::subtract(const Time &t) const {
    Time result;
    const int total_mins_t1 = hour * 60 + minute;
    const int total_mins_t2 = t.hour * 60 + t.minute;

    const int difference = total_mins_t1 - total_mins_t2;

    result.hour = difference / 60;
    result.minute = difference % 60;

    return result;
}

void Time::display() const {
    std::cout << std::setiosflags(std::ios::right);
    std::cout << std::setfill('0') << std::setw(2) << hour << ":" << std::setfill('0') << std::setw(2) << minute <<
            std::endl;
}

std::ostream &operator<<(std::ostream &out, const Time &s) {
    out << std::setfill('0') << std::setw(2) << s.hour << ":" << std::setfill('0') << std::setw(2) << s.minute <<
            std::endl;
    return out;
}
std::istream &operator>>(std::istream &in, Time &s) {
    char separator;
    in >> s.hour >> separator >> s.minute;

    // Validate the separator and time components
    if (separator != ':' || s.minute < 0 || s.minute >= 60 || s.hour < 0 || s.hour >= 24) {
        std::cerr << "Invalid time format! Please enter time as hh:mm." << std::endl;
        in.setstate(std::ios::failbit);
    }
    return in;
}
bool Time::operator<(const Time &t) const {
    return (hour < t.hour) || (hour == t.hour && minute < t.minute);
}

Time Time::operator+(const Time &t) {
    Time result;
    result.hour = hour + t.hour;
    result.minute = minute + t.minute;
    normalizeTime();
    return result;
}

class Time Time::operator-(const Time &t) const {
    Time result;
    const int total_mins_1 = hour * 60 + minute;
    const int total_mins_2 = t.hour * 60 + t.minute;
    const int diff = total_mins_1 - total_mins_2;
    result.hour = diff / 60;
    result.minute = diff % 60;

    return result;
}

Time &Time::operator++() {
    ++minute;
    normalizeTime();
    return *this;
}

Time Time::operator++(int) {
    const Time temp = *this;
    ++minute;
    normalizeTime();
    return temp;
}

bool Time::from_str(const std::string &timeStr) {
    char colon;
    std::stringstream ss(timeStr);
    ss >> hour >> colon >> minute;
    return !ss.fail() && colon == ':' && hour >= 0 && hour < 24 && minute >= 0 && minute < 60;
}

std::string Time::to_str() const {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << hour << ":" << std::setfill('0') << std::setw(2) << minute ;
    return ss.str();
}

void Time::dst(const int offset) {
    hour = (hour + offset) % 24;
    if (hour < 0) {
        hour += 24;
    }
}