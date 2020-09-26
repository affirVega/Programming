#include <iostream>

int main() {
	
	long long n;
	int       x{0};
	std::cout << "Введите целое число." << std::endl;
	std::cin >> n;

	if (n >= 1) {
		x++;
	}
	while (n > 1) {
		n /= 2;
		x++;
	}

	std::cout << x <<std::endl;
}

