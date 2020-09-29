#include <iostream>

int main() {
    int a, b;

    std::cout << "Введите два целых числа, разделённых пробелом или новой строкой." << std::endl;
    std::cin >> a >> b;

    // Обмен без дополнительной переменной
    a = a - b;
    b = b + a;
    a = b - a;

    std::cout << "Значение a = " << a << std::endl;
    std::cout << "Значение b = " << b << std::endl;

    // Обмен с дополнительной переменной
	int temp;
	temp = a;
	a = b;
	b = temp;

    std::cout << "Значение a = " << a << std::endl;
    std::cout << "Значение b = " << b << std::endl;
}
