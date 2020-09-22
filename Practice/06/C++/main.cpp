#include <iostream>
#include <cmath>

using namespace std;

int main() {
    cout << "Введите 3 вещественных числа, разделённых пробелами." << endl;
    double a, b, c;
    cin >> a >> b >> c;

    bool is_successful{true};
    if(a == 0) {
        if (b == 0) {
            cout << "Корней нет." << endl;
        } else {
            cout << "x = " << -c / b << endl;
        }
    } else {
        double d = b*b - 4*a*c;
        if (d < 0)
            cout << "Не найдено действительных корней." << endl;
        else if (d == 0) {
            cout << "x = " << -b / (2*a) << endl;
        } else {
            double d_sqrt {sqrt(d)};
            double x_one {
                (-b + d_sqrt) / (2*a)
            };
            double x_two {
                (-b - d_sqrt) / (2*a)
            };
            cout << "x1 = " << x_one << endl;
            cout << "x2 = " << x_two << endl;
        }
    }
}