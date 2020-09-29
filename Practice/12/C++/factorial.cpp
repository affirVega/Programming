#include <iostream>

int main() {
	std::cout << "Введите число для расчёта факториала" << std::endl;

	long n;
	std::cin >> n;

	long long f = 1;

	for (int i = 2; i <= n; i++) {
		f *= i;
	}

	std::cout << f << std::endl;
}
