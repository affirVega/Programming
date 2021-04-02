#include "point.hpp"

#include <cmath>
#include <iostream>

Point::Point(double a1, double a2, CoordSystem coord_system) {
    if (coord_system == CoordSystem::Cartesian) {
        x = a1;
        y = a2;
    } else {
        // значит, a1 это радиус, а а2 это угол в радианах
        x = cos(a2) * a1;
        y = sin(a2) * a1;
    }
}

bool Point::operator==(const Point& other) const {
    return fabs(x - other.x) < g_percision
            && fabs(y - other.y) < g_percision;
}

bool Point::operator!=(const Point& other) const {
    return !this->operator==(other);
}

double Point::get_x() const { return x; }

double Point::get_y() const { return y; }

double Point::get_r() const { return hypot(x, y); }

double Point::get_phi() const { return atan2(y, x); }

void Point::set_x(double x) { this->x = x; }

void Point::set_y(double y) { this->y = y; }

void Point::set_r(double r) {
    double phi = get_phi(); // угол остаётся тем же
    x = cos(phi) * r;
    y = sin(phi) * r;
}

void Point::set_phi(double phi) {
    double r = get_r(); // радиус остаётся тем же
    x = cos(phi) * r;
    y = sin(phi) * r;
}

std::ostream& operator<<(std::ostream& out, const Point& p) {
    out << '(' << p.get_x() << ',' << p.get_y() << ')';
    return out;
}

std::istream& operator>>(std::istream& in, Point& p) {
    double buf;
    in.ignore(g_maxCharToSkip, '(');
    in >> buf;
    p.set_x(buf);
    in.ignore(g_maxCharToSkip, ',');
    in >> buf;
    p.set_y(buf);
    in.ignore(g_maxCharToSkip, ')');
    return in;
}
