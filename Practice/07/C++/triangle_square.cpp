#include <iostream>
#include <cmath>

double length(double x1, double y1, double x2, double y2) {
    return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
}

int main() {
    double a, b, c, p, S, x1, y1, x2, y2, x3, y3;
    int choice;
    bool is_failure;
    std::cout << "Это программа для высчитывания площади треугольника.\n"
                 "Введите цифру, чтобы указать, какой тип данных о треугольнике вы хотите указать.\n"
                 "1. Координаты треугольника.\n"
                 "2. Стороны треугольника." << std::endl;
    do {
        is_failure = false;
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "Введите три пары вещественных чисел, разделённых пробелом. Первое число x, второе y."
                          << std::endl;
                std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

                a = length(x1, y1, x2, y2);
                b = length(x2, y2, x3, y3);
                c = length(x3, y3, x1, y1);
                break;
            case 2:
                std::cout << "Введите стороны треугольника." << std::endl;
                std::cin >> a >> b >> c;
                break;
            default:
                std::cout << "Ошибка во введённых данных. Попробуйте снова." << std::endl;
                is_failure = true;
                break;
        }
        if (a + b < c || a + c < b || c + b < a)
            is_failure = true;

    } while (is_failure);

    p = (a + b + c) / 2;
    S = sqrt(p * (p - a) * (p - b) * (p - c));

    std::cout << "S = " << S << std::endl;
}

