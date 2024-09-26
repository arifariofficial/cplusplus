/*
In this exercise we implement a class hierarchy similar to the one used as example in the lectures.
Derive two classes from Point:
1. Circle: add radius
2. Square: add width and height.
All derived classes must implement all virtual functions and define constructors that take 2 – 4 values as
parameter depending on the class. All parameters must have a default value.
See example output at end of this document.

//definition of class Point

class Point {
public:
    Point(double xcoord = 0.0, double ycoord = 0.0); //constructor
    virtual ~Point() = default; // destructor
    virtual void input(const char *prompt); // print coordinates and area(if applicable)
    virtual void output() const;  // return area (Point returns 0.0)
    virtual double area() const;
    void move(double deltax, double deltay);
private:
    double x;
    double y;
};

Write a program that defines a vector of shared pointers to the base class.
Then program puts the following objects into vector:
• Point with coordinates (1.0, 1.0)
• Circle at (2.0, 2.0) with radius 2.0
• Square at (5.0, 5.0) with width and height of 2.0
• Square whose data is asked from user before adding to the vector
• Circle whose data is asked from user before adding to the vector
• Point whose data is asked from user before adding to the vector
When vector has been filled program does the following:
1. Prints the object data
2. Sorts the vector by area
3. Prints the object data
See example output on the following page.

Example output:
Coordinates: (1,1)
Circle's area: 12.5664 Coordinates: (2,2)
Square's area: 4 Coordinates: (5,5)
Sorted:
Coordinates: (1,1)
Square's area: 4 Coordinates: (5,5)
Circle's area: 12.5664 Coordinates: (2,2)
Example output of calls to input():
Point:
Enter x:2.3
Enter y:5.7
Circle:
Enter x:3.4
Enter y:4.5
Enter radius: 6.7
Square:
Enter x:1.2
Enter y:2.3
Enter height: 3.4
Enter width: 4.5
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//definition of class Point
class Point {
public:
    explicit Point(double xcoord = 0.0, double ycoord = 0.0); //constructor
    virtual ~Point() = default; // destructor

    virtual void input(const char *prompt); // print coordinates and area(if applicable)
    virtual void output() const; // return area (Point returns 0.0)
    [[nodiscard]] virtual double area() const;
    void move(double deltax, double deltay);
protected:
    double x;
    double y;
};

//definition of Circle class
class Circle final : public Point {
public:
    explicit Circle(double xcoord = 0.0, double ycoord = 0.0, double radius = 0.0);

    void input(const char *prompt) override;
    void output() const override;
    [[nodiscard]] double area() const override;
private:
    double radius;
};

//definition of Square class
class Square final : public Point {
public:
    explicit Square(double xcoord = 0.0, double ycoord = 0.0, double width = 0.0, double height = 0.0);

    void input(const char *prompt) override;
    void output() const override;
    [[nodiscard]] double area() const override;
private:
    double width;
    double height;
};

int main() {
    std::vector<std::shared_ptr<Point>> shapes;

    // Adding predefined shapes to the vector
    shapes.push_back(std::make_shared<Point>(1.0, 1.0));
    shapes.push_back(std::make_shared<Circle>(2.0, 2.0, 2.0));
    shapes.push_back(std::make_shared<Square>(5.0, 5.0, 2.0, 2.0));

    // Adding user-defined shapes
    // const auto userPoint = std::make_shared<Point>();
    // userPoint->input("Point:");
    // shapes.push_back(userPoint);
    //
    // const auto userCircle = std::make_shared<Circle>();
    // userCircle->input("Circle:");
    // shapes.push_back(userCircle);
    //
    // const auto userSquare = std::make_shared<Square>();
    // userSquare->input("Square:");
    // shapes.push_back(userSquare);



    // Printing initial object data
    std::cout << "\nExample output:\n";
    for (const auto& shape : shapes) {
        shape->output();
    }

    // Sorting the shapes by area
    ranges::sort(shapes, [](const std::shared_ptr<Point>& a, const std::shared_ptr<Point>& b) {
        return a->area() < b->area();
    });

    // Printing sorted object data
    std::cout << "\nSorted:\n";
    for (const auto& shape : shapes) {
        shape->output();
    }

    return 0;
}

// implementation of Point class
Point::Point(const double xcoord, const double ycoord) : x(xcoord), y(ycoord) {
}

void Point::input(const char *prompt) {
    cout << prompt << endl;
    cout << "Enter x: ";
    cin >> x;
    cout << "Enter y: ";
    cin >> y;
}

void Point::output() const {
    cout << "Coordinates: (" << x << "," << y << ")" << endl;
}

double Point::area() const {
    return 0.0;
}

void Point::move(const double deltax, const double deltay) {
    x += deltax;
    y += deltay;
}

// implementation of Circle class
Circle::Circle(const double xcoord, const double ycoord, const double radius) : Point(xcoord, ycoord), radius(radius) {
}

void Circle::input(const char *prompt) {
    Point::input(prompt);
    cout << "Enter radius: ";
    cin >> radius;
}

void Circle::output() const {
    std::cout << "Circle's area: " << area() << " Coordinates: (" << x << "," << y << ")\n";
}


double Circle::area() const {
    return 3.14159 * radius * radius;
}

// implementation of Square class
Square::Square(const double xcoord, const double ycoord, const double width, const double height) : Point(xcoord, ycoord), width(width), height(height) {
}

void Square::input(const char *prompt) {
    Point::input(prompt);
    cout << "Enter height: ";
    cin >> height;
    cout << "Enter width: ";
    cin >> width;
}

void Square::output() const {
    std::cout << "Square's area: " << area() << " Coordinates: (" << x << "," << y << ")\n";
}


double Square::area() const {
    return width * height;
}

