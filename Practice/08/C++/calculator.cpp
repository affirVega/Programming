#include <iostream>

using namespace std;

int main() {
    double f, s, result;      // первое, второе, результат
    char op;                  // оператор +, -, *, или /
    bool result_exists{true};

    cout << "Введите вещественное число, символ оператора и вещественное число, разделённые пробелами. "
            "Пример: \"8 * 3\"." << endl;

    cin >> f >> op >> s;

    switch (op) {
        case '*':
            result = f * s;
            break;
        case '+':
            result = f + s;
            break;
        case '-':
            result = f - s;
            break;
        case '/':
            if (s == 0) {
                cout << "Ошибка: Деление на 0.";
                result_exists = false;
                break;
            }
            result = f / s;
            break;
        default:
            cout << "Ошибка: неизвестный оператор.";
            result_exists = false;
            break;
    }
    if (result_exists) {
        cout << result << endl;
    }
}

