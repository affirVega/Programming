#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

const auto PI = 3.141592653589793;

enum class CoordSystem { Cartesian, Polar };

// точность сравнивания двух точек.
const double g_percision = 1e-10;

// максимальное количество символов, которое пропускается при парсинге точки
const double g_maxCharToSkip = 3;

class Point {
public:
    Point(double = 0, double = 0, CoordSystem = CoordSystem::Cartesian);

    bool operator==(const Point&) const;
    bool operator!=(const Point&) const;

    double get_x() const;
    double get_y() const;
    double get_r() const;
    double get_phi() const;
    void set_x(double);
    void set_y(double);
    void set_r(double);
    void set_phi(double);

private:
    double x, y;
};

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

int main() {
    std::vector<Point> original;
    std::ifstream fin("data.txt");
    if (!fin.is_open()) {
        std::cout << "Can't open file" << std::endl;
        return 1;
    } else {
        while (!fin.eof()) {
            Point p;
            fin >> p;
            fin.ignore(2); // Точки разделены двумя символами ", "
            original.push_back(p);
        }
        fin.close();
    }

    std::vector<Point> simulacrum(original);
    for (auto& p : simulacrum) {
        std::cout << p;
        p.set_x(p.get_x() + 10);
        p.set_phi(p.get_phi() + 180*PI/180);
        p.set_y(-p.get_y());
        p.set_x(-p.get_x() - 10);
        std::cout << p << std::endl;
    }

    if (std::equal(original.begin(), original.end(), simulacrum.begin()))
        std::cout << "\nIt works!\n";
    else
        std::cout << "\nIt not works!\n";
}
