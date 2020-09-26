#include <iostream>

int main() {
	uint n;
	std::cout << "Введите целое положительное число" << std::endl;
	std::cin >> n;

	long long f{1};

	for (int i = 2; i <= n; i++) {
		f *= i;
	}

	std::cout << f << std::endl;
}
