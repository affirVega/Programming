#include <iostream>

int main() {
    std::cout << "Через пробел введите вещественное число, затем оператор и вещественное число. "
            "Пример: \"8 * 3\"." << std::endl;

    double f, s;
    char op;
    std::cin >> f >> op >> s;

    double result;
    bool result_exists = true;
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
                std::cout << "Ошибка: Деление на 0.";
                result_exists = false;
                break;
            }
            result = f / s;
            break;
        default:
            std::cout << "Ошибка: неизвестный оператор.";
            result_exists = false;
            break;
    }
    if (result_exists) {
        std::cout << result << std::endl;
    }
}

