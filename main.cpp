#include <iostream>

using namespace std;

void first() {
    cout << "Результат выражения 2+2*2 = " << 2+2*2 << endl;
}

void second() {
    int i1 = 3;
    int i2 = 3.14;

    double d1 = 3;
    double d2 = 3.14;

    cout << "Значение i1: " << i1 << endl;
    cout << "Значение i2: " << i2 << endl;
    cout << "Тип int хранит целочисленное значение. При попытке присвоить к int-овой переменной дробное число, "
         << "дробная его часть отбрасывается." << endl << endl;

    cout << "Значение d1: " << d1 << endl;
    cout << "Значение d2: " << d2 << endl;
    cout << "Тип double и float хранят дробные числа. Разница в том, что для double выделяется в два раза больше байтов"
         << " в ОЗУ, поэтому оно может хранить более точное значение." << endl;
}

void third() {
    int a;
    int b;

    cout << "Введите два целых числа, разделённых пробелом или новой строкой." << endl;
    cin >> a >> b;

    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;
    cout << "a / b = " << a / b << endl;
}

void fourth() {
    int a;
    int b;

    cout << "Введите два целых числа, разделённых пробелом или новой строкой." << endl;
    cin >> a >> b;

    a = a - b;
    b = b + a;
    a = b - a;

    cout << "Значение a = " << a << endl;
    cout << "Значение b = " << b << endl;
}

double x(double x0, double v0, double a, double t) {
    return x0 + v0*t - (a*t*t)/2;
}
void fifth() {
    // x(t) = x0 + v0t - (at*t)/2
    double x0, v0, t;
    double g = 9.8;

    cout << "Введите x₀, v₀ и t, разделённые пробелом" << endl;
    cin >> x0 >> v0 >> t;

    double d = x0 - x(x0, v0, g, t);
    d = d >= 0 ? d : -d;
    cout << d << endl;
}


int main() {
    //first();
    //second();
    //third();
    //fourth();
    fifth();
}
