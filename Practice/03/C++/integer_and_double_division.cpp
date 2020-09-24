#include <iostream>

using namespace std;
int main() {
    int a;
    int b;
	double c;
	double d;
	
    cout << "Введите два целых числа, разделённых пробелом или "
            "новой строкой." << endl;
    cin >> a >> b;
    cout << "Введите два дробных числа, разделённых пробелом или "
            "новой строкой, где дробная часть числа отделяется точкой." << endl;
    cin >> c >> d;

	cout << "Справка: a и b -- целочисленные\n c и d -- дробные" << endl;

    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;
    cout << "a / b = " << a / b << endl;

	cout << endl;
    cout << "c + d = " << c + d << endl;
    cout << "c - d = " << c - d << endl;
    cout << "c * d = " << c * d << endl;
    cout << "c / d = " << c / d << endl;

	cout << endl;
    cout << "c + b = " << c + b << endl;
    cout << "c - b = " << c - b << endl;
    cout << "c * b = " << c * b << endl;
    cout << "c / b = " << c / b << endl;

	cout << endl;
    cout << "a + d = " << a + d << endl;
    cout << "a - d = " << a - d << endl;
    cout << "a * d = " << a * d << endl;
    cout << "a / d = " << a / d << endl;

	// С++ испольует целочисленное деление, если по обе стороны от 
	// оператора деления целые числа.
	// Если по одну из сторон есть хотя-бы есть один double или float,
	// оператор возвращает дробное число.
}
