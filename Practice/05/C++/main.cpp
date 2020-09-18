#include <iostream>

using namespace std;

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

    cout << "Введите x₀, v₀ и t, разделённые пробелом" << endl;
    cin >> x0 >> v0 >> t;

    double d = x0 - x(x0, v0, g, t); // дистанция
	d = d >= 0 ? d : -d; // модуль d
    cout << d << endl;
}
