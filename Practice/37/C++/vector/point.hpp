#ifndef POINT_HPP
#define POINT_HPP

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




#endif // POINT_HPP
