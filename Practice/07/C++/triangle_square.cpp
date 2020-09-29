#include <iostream>
#include <cmath>

struct Point {
    double x;
    double y;

    double distance_to(Point other) {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }
};

int main() {
    
    
    std::cout << "Это программа для высчитывания площади треугольника.\n"
                 "Введите цифру, чтобы указать, какой тип данных о треугольнике вы хотите указать.\n"
                 "1. Длины стороны треугольника.\n"
                 "2. Координаты треугольника." << std::endl;

    int choice;
    std::cin >> choice;

    double a, b, c;
    switch (choice) {
        case 1:
            std::cout << "Введите длины сторон треугольника, каждое с отдельной строки." << std::endl;
            std::cin >> a >> b >> c;

            break;
        case 2:
            std::cout << "Введите три пары вещественных чисел, каждая пара с новой строки, \n"
                "числа в паре разделены пробелом. Первое число x, второе y." << std::endl;
            double x1, y1, x2, y2, x3, y3;
            std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

            // Почему-то компилятор ругается, если здесь не будет блока
            {
                Point p1 {x1, y1};
                Point p2 {x2, y2};
                Point p3 {x3, y3};

                a = p1.distance_to(p2);
                b = p1.distance_to(p3);
                c = p2.distance_to(p3);
            }

            break;
        default:
            std::cout << "Ошибка: неизвестный способ ввода." << std::endl;
            break;
    }

    if (a + b < c || a + c < b || c + b < a)
        std::cout << "Ошибка: данный треугольник не может существовать на плоскости." << std::endl;
    else {
        double p = (a + b + c) / 2;
        double S = sqrt(p * (p - a) * (p - b) * (p - c));

        std::cout << "S = " << S << std::endl;
    }
}
