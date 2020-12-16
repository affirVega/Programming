#include <iostream>
#include <vector>
#include "geometry.hpp"

int main()
{
    circle      a(point(0, 0), 10);
    rectangle   b(point(0, 0), 10, 20);
    
    std::vector<base_shape*> shapes = {&a, &b};
    
    for (auto shape : shapes)
    {
        std::cout << shape->get_area() << " " << shape->get_perimeter() << std::endl;
    }
    
    return 0;
}
