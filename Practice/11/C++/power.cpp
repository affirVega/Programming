//
// Created by affir on 9/24/20.
//
#include <iostream>
#include <cmath>

int main() {
    double result{1};
    double a;
    int n;
    std::cout << "Введите возводимое в степень число и целое число -- степень" << std::endl;
    std::cin >> a >> n;

    bool negative_power = n < 0;
    n = std::abs(n);

    while (n-- > 0)
        result *= a;

    if (negative_power) {
        result = 1 / result;
    }

    std::cout << result << std::endl;
}
