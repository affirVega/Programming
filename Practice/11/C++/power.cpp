#include <iostream>

int main() {
    std::cout << "Введите возводимое в степень число и целое число -- степень" << std::endl;
    
    double a;
    int n;
    std::cin >> a >> n;

    double result = 1;
    for (int i = 0; i < n; i++)
        result *= a;

    if (n < 0) {
        result = 1 / result;
    }

    std::cout << result << std::endl;
}
