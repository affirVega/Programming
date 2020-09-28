#include <iostream>

int main() {
    long s, l1, r1, l2, r2;

	std::cout << "Введите сумму, границы первого промежутка и границы второго промежутка на одной строке через пробел" << std::endl;
    std::cin >> s >> l1 >> r1 >> l2 >> r2;

    long long i{l1};
    long long j{r2};

	if (i + j < s) i = min(r1, s-j);
	else           j = max(l2, s-i);

	if (i + j < s) i = min(r1, s-j);
	else           j = max(l2, s-i);

    std::string out{(i + j == s)
        ? "x1 = " + std::to_string(std::min(i, j)) +
		  "\nx2 = " + std::to_string(std::max(i, j))
        : "Нет таких x."};

    std::cout << out << std::endl;
}
