#define pure 0
#include <cmath>

struct point 
{ 
    double x; double y; 
    
    // Explicit constructor. 
    explicit point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
};

struct vector : point
{
    double gen_len();
    
    vector(double x, double y)
        : point(x, y)
    {
    }
    
    vector(point p)
        : point(p.x, p.y)
    {
    }
};

double vector::gen_len()
{
    return std::sqrt(this->x*this->x + this->y*this->y);
}

// ------------------------------
// Base Shape. Has anchor point (center)
// and 2 pure functions => base_shape is abstract class
// ------------------------------
struct base_shape
{
    point center;
    
    base_shape(point p)
        : center(p)
    {
    }
    
    virtual double get_area()       = pure;
    virtual double get_perimeter()  = pure;
};


// ------------------------------
// Circle. Has center point and radius.
// Implements pure functions, so this is usual class.
// ------------------------------
struct circle : base_shape
{
    double radius;
    double get_area();
    double get_perimeter();
    
    circle(point p, double radius);
};

circle::circle(point p, double radius)
    : base_shape(p)
{
    this->radius = radius;
}

double circle::get_area()
{
    return 3.1415926 * this->radius * this->radius;
}

double circle::get_perimeter()
{
    return 2.0 * 3.1415926 * this->radius;
}

// ------------------------------
// Rectangle. Has anchor (top left), length on x (positive = right).
// length on y (positive = down).
// ------------------------------
struct rectangle : base_shape
{
    double xlen;
    double ylen;
    double get_area();
    double get_perimeter();
    
    rectangle(point p, double xlen, double ylen);
};

rectangle::rectangle(point p, double xlen, double ylen)
    : base_shape(p)
{
    this->xlen = xlen;
    this->ylen = ylen;
}

double rectangle::get_area()
{
    return std::abs(xlen * ylen);
}

double rectangle::get_perimeter()
{
    return std::abs(2 * (xlen + ylen));
}
