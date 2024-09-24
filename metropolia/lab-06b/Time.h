#pragma once
#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <string>
using namespace std;

class Time {
    friend std::ostream &operator<<(std::ostream &out, const Time &s);
    friend std::istream &operator>>(std::istream &in, Time &s);
public:
    Time();
    bool from_str(const string &timeStr);
    [[nodiscard]] string to_str() const;
    void dst(int offset);
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
    int minute;
    void normalizeTime();
};

#endif //TIME_H