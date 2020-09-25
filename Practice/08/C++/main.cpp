#include <iostream>

using namespace std;

void input_error() {
    cout << "Ошибка во входных данных. Попробуйте снова.\n";
    cin.clear();
    cin.ignore(32767, '\n'); // игнорировать 32767 символов до следующей строки
}

int main() {
    setlocale(LC_ALL, "Russian");
    double f, s, result;      // первое, второе, результат
    char op;                  // оператор +, -, *, или /
    bool repeat_result;
    bool result_exists{true};

    do {
        repeat_result = false;
        cout << "Введите вещественное число, символ оператора и вещественное число, разделённые пробелами. "
                "Пример: \"8 * 3\"." << endl;

        cin >> f >> op >> s;
        if (cin.fail()) {
            input_error();
            repeat_result = true;
            continue;
        }

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
                input_error();
                repeat_result = true;
                break;
        }
    } while(repeat_result);
    if (result_exists) {
        cout << result << endl;
    }
}

