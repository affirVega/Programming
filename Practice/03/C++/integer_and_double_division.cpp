#include <iostream>

int main() {
    int    a, b;
	double c, d;
	
    std::cout << "Введите два целых числа, разделённых пробелом или "
            "новой строкой." << std::endl;
    std::cin >> a >> b;
    std::cout << "Введите два дробных числа, разделённых пробелом или "
            "новой строкой, где дробная часть числа отделяется точкой." << std::endl;
    std::cin >> c >> d;

	std::cout << "Справка: a и b -- целочисленные\n c и d -- дробные" << std::endl;

    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a - b = " << a - b << std::endl;
    std::cout << "a * b = " << a * b << std::endl;
    std::cout << "a / b = " << a / b << std::endl;

	std::cout << std::endl;
    std::cout << "c + d = " << c + d << std::endl;
    std::cout << "c - d = " << c - d << std::endl;
    std::cout << "c * d = " << c * d << std::endl;
    std::cout << "c / d = " << c / d << std::endl;

	std::cout << std::endl;
    std::cout << "c + b = " << c + b << std::endl;
    std::cout << "c - b = " << c - b << std::endl;
    std::cout << "c * b = " << c * b << std::endl;
    std::cout << "c / b = " << c / b << std::endl;

	std::cout << std::endl;
    std::cout << "a + d = " << a + d << std::endl;
    std::cout << "a - d = " << a - d << std::endl;
    std::cout << "a * d = " << a * d << std::endl;
    std::cout << "a / d = " << a / d << std::endl;

	// С++ испольует целочисленное деление, если по обе стороны от 
	// оператора деления целые числа.
	// Если по одну из сторон есть хотя-бы есть один double или float,
	// оператор возвращает дробное число.
}
