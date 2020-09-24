#include <iostream>

int main() {
    long s, l1, r1, l2, r2;

    // Ввод: сумма, начало и конец первого диапазона, начало и конец второго диапазона
    // Все числа между -2^15 и 2^15, в диапазоне как минимум одно число
    std::cin >> s >> l1 >> r1 >> l2 >> r2;

    long long i{l1};
    long long j{r2};

    i = !(i + j >= s) * fmin(-j + 0 + s, r1) + (i + j >= s) * i;
    j = (i + j >= s) * fmax(-i + 0 + s, l2) + !(i + j >= s) * j;
    i = !(i + j >= s) * fmin(-j + 0 + s, r1) + (i + j >= s) * i;
    j = (i + j >= s) * fmax(-i + 0 + s, l2) + !(i + j >= s) * j;

    std::string out{(i + j == s)
        ? "x1 = " + std::to_string(std::min(i, j)) + "\nx2 = " + std::to_string(std::max(i, j))
        : "Нет таких x."};

    std::cout << out << std::endl;
}
