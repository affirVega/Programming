#include <iostream>
#include "point.hpp"
#include <cmath>
using namespace std;

double sqr(double a);
bool equal(double a, double b, double e = 1E-10);

class Vector {
    Point head;

public:
    Vector();
    Vector(const Point& end);
    Vector(const Point& begin, const Point& end);

    bool operator==(const Vector& other) const;
    Vector operator-() const;
    Vector operator-(const Vector& other) const;
    Vector operator+(const Vector& other) const;
    Vector operator*(double mul) const;
    double operator*(const Vector& other) const;

    double length() const;
};

Vector::Vector()
    : head(1, 0) {
}
Vector::Vector(const Point& end)
    : head(end.get_x(), end.get_y()) {
}
Vector::Vector(const Point& begin, const Point& end)
    : head(end.get_x() - begin.get_x(), end.get_y() - begin.get_y()) {
}

bool Vector::operator==(const Vector& other) const{
    return head == other.head;
}
Vector Vector::operator-() const{
    Point p = head;
    p.set_x(-p.get_x());
    p.set_y(-p.get_y());
    return Vector(p);
}
Vector Vector::operator-(const Vector& other) const{
    Point p;
    p.set_x( head.get_x() - other.head.get_x() );
    p.set_y( head.get_y() - other.head.get_y() );
    return Vector(p);
}
Vector Vector::operator+(const Vector& other) const{
    Point p;
    p.set_x( head.get_x() + other.head.get_x() );
    p.set_y( head.get_y() + other.head.get_y() );
    return Vector(p);
}
Vector Vector::operator*(double mul) const{
    Point p = head;
    p.set_x(p.get_x() * mul);
    p.set_y(p.get_y() * mul);
    return Vector(p);
}
double Vector::operator*(const Vector& other) const{
    return length() * other.length() * cos( head.get_phi() - other.head.get_phi() );
}

double Vector::length() const{
    return head.get_r();
}

int main()
{
    Vector a(Point(1, 2)), b(Point(-2, 0), Point(-1, 2));
    if (a == b && b == a) cout << "Equality test passed\n";
    else cout << "Equality test failed\n";

    Vector na(Point(-1, -2)), ox(Point(1, 0)), nox(Point(-1, 0)), oy(Point(0, 1)), noy(Point(0, -1));
    if (a == -na && na == -a && -ox == nox && -oy == noy) cout << "Invert test passed\n";
    else cout << "Invert test failed\n";

    if (ox + oy + oy == a && -ox == -a + oy + oy) cout << "Summation test passed\n";
    else cout << "Summation test failed\n";

    if (-ox + oy == oy - ox && -oy + ox == ox - oy) cout << "Subtraction test passed\n";
    else cout << "Subtraction test failed\n";

    if (ox * 3 == ox + ox + ox &&
        oy * 3 == oy + oy + oy &&
        ox * (-3) == -ox - ox - ox &&
        oy * (-3) == -oy - oy - oy) cout << "Multiplication by number test passed\n";
    else cout << "Multiplication by number test failed\n";

    if (equal(ox.length(), 1) &&
        equal(oy.length(), 1) &&
        equal((ox * 3 + oy * 4).length(), 5)) cout << "Length test passed\n";
    else cout << "Length test failed\n";

    if (equal(ox*ox, sqr(ox.length())) &&
        equal(oy*oy, sqr(oy.length())) &&
        equal((ox*3 + oy*4)*(ox*3 + oy*4), sqr((ox*3 + oy*4).length()))) cout << "Multiplication by Vector test passed\n";
    else cout << "Multiplication by Vector test failed\n";
}

bool equal(double a, double b, double e) {
    if (-e < a - b && a - b < e) return true;
    else return false;
}

double sqr(double a) {
    return a * a;
}
