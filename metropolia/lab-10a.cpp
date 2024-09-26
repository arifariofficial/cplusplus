/*
In this exercise you need to derive two classes from an abstract class and write a function that helps in
testing the classes. Your starting point is an abstract class called Counter that defines an interface for
incrementing and decrementing a counter and a conversion operator that can be used to read or print the current
counter value.

Derive a class called LimitedCounter.
• The constructor takes two parameters: initial value and upper limit
• Counter can’t be incremented over the upper limit. If inc() is called when counter has reached the upper limit
nothing happens
• Counter can’t be decremented below zero. If counter is zero then calling dec() will have no effect
Derive a class called OverflowCounter.
• The constructor takes two parameters: initial value and upper limit
• When counter has reached the upper limit incrementing the value will set the counter to zero.
• When counter is zero decrementing the counter sets counter to upper limit.
Implement function called UseCounter.
• void UseCounter(Counter& ctr, int num);
• Function takes two parameters: a reference to Counter and number that tells how many times the counter should
be incremented or decremented. A negative value decrements counter and positive value increments counter.
Test your counters with different values and ways. Pay attention to the limits and make sure that they work
properly.
Use the attached code as starting point.
 */

#include <iostream>

class Counter {
public:
    virtual void inc() = 0;
    virtual void dec() = 0;
    virtual explicit operator int() = 0;
    virtual ~Counter() = default;
};

class LimitedCounter final : public Counter {
public:
    LimitedCounter(const int initial, const int upperLimit) : counter(initial), upperLimit(upperLimit) {
    }
    void inc() override {
        if (counter < upperLimit) counter++;
    }
    void dec() override {
        if (counter > 0) counter--;
    }
    explicit operator int() override { return counter; }
    ~LimitedCounter() override = default;
private:
    int counter;
    int upperLimit;
};

class OverflowCounter final : public Counter {
public:
    OverflowCounter(const int initial, const int upperLimit) : counter(initial), upperLimit(upperLimit) {
    }
    void inc() override {
        if (counter < upperLimit) counter++;
        else counter = 0;
    }
    void dec() override {
        if (counter > 0) counter--;
        else counter = upperLimit;
    }
    explicit operator int() override { return counter; }
    ~OverflowCounter() override = default;
private:
    int counter;
    int upperLimit;
};

void UseCounter(Counter &ctr, int num);

int main(int argc, char **argv) {
    LimitedCounter lc(0, 5);
    OverflowCounter oc(5, 9);

    // Test OverflowCounter
    std::cout << static_cast<int>(oc) << std::endl;
    UseCounter(oc, 5);
    std::cout << static_cast<int>(oc) << std::endl; // should display zero
    UseCounter(oc, -1);
    std::cout << static_cast<int>(oc) << std::endl; // should display 9
    oc.dec();
    std::cout << static_cast<int>(oc) << std::endl; // should display 8

    // Test LimitedCounter
    std::cout << static_cast<int>(lc) << std::endl;
    lc.inc();
    std::cout << static_cast<int>(lc) << std::endl;
    lc.dec();
    std::cout << static_cast<int>(lc) << std::endl;
    for (int i = 0; i < 10; ++i) lc.inc();  // Incrementing beyond the limit
    std::cout << static_cast<int>(lc) << std::endl;
    UseCounter(lc, -9);
    std::cout << static_cast<int>(lc) << std::endl;

    return 0;
}

void UseCounter(Counter &ctr, int num) {
    for (int i = 0; i < std::abs(num); ++i) {
        if (num > 0) ctr.inc();
        else ctr.dec();
    }
    std::cout << static_cast<int>(ctr) << std::endl;
}

