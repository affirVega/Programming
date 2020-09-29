#include <iostream>

// x(t) = x0 + v0t - (at²)/2
// Лучше всего использовать double для x0, v0 и t, 
// потому что так можно будет указать более точные 
// данные, чем float или int
double x(double x0, double v0, double a, double t) {
    return x0 + v0*t - (a*t*t)/2;
}

int main() {
    double x0, v0, t;
    double g = 9.8;

    std::cout << "Введите x₀, v₀ и t, разделённые пробелом" << std::endl;
    std::cin >> x0 >> v0 >> t;

    double distance = abs(x0 - x(x0, v0, g, t));
    std::cout << distance << std::endl;
}
