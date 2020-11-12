#include <iostream>
#include <iomanip>  //std::setprecision

#include "sin.hpp"
#include "factorial.hpp"
#include "combinations.hpp"

double const PI = 3.1415926;

int main() {
    std::cout << "n\tn!" << std::endl;
    for (int64_t i = 1; i <= 10; ++i) {
        std::cout << i << "\t" << factorial(i) << std::endl;
    }   std::cout << std::endl;

    std::cout << "x\tsin(x)" << std::endl;
    std::cout << std::setprecision(4);
    for (double x = 0; x <= PI/4; x += PI/180) {
        std::cout << x << "\t" << sin(x, 5) << std::endl;
    }   std::cout << std::endl;

    std::cout << "k\tC(k, 10)" << std::endl;
    for (int64_t k = 1; k <= 10; ++k) {
        std::cout << k << "\t" << combinations(k, 10) << std::endl;
    }
}
