#pragma once
#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

class Time {
    friend std::ostream &operator<<(std::ostream &out, const Time &s);
    friend std::istream &operator>>(std::istream &in, Time &s);
public:
    Time();
    void read(const char *s);
    bool lessThan(const Time &t) const;
    Time subtract(const Time &t) const;
    void display() const;
    // Operator overload
    bool operator<(const Time &t) const;
    Time operator+(const Time &t);
    Time operator-(const Time &t) const;
    Time &operator++(); // prefix increment
    Time operator++(int);

    bool from_str(const std::string &timeStr);
    std::string to_str() const;
    void dst(int offset);
private:
    int hour;
    int minute;
    void normalizeTime();
};
#endif //TIME_H_INCLUDED