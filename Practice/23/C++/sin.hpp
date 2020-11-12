#ifndef SIN_HPP
#define SIN_HPP
#include "factorial.hpp"

double sin(double x, int64_t k);

double sin(double x) {
    return sin(x, 20);
}

double sin(double x, int64_t k) {
    if (k < 1) 
        return -2;

    double result = 0;
    int    sign   = 1;
    
    for (int64_t i = 0; i < k; ++i) {
        int64_t n = i*2 + 1;

        double next = sign;
        for (int64_t j = 0; j < n; ++j) {
            next *= x;
        }
        next /= factorial(n);
        result += next;
        sign *= -1;
    }

    return result;
}
#endif
