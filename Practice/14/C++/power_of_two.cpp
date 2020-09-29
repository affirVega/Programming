#include <iostream>

int main() {
	std::cout << "Введите целое число." << std::endl;

	long long n;
	std::cin >> n;

	int x = 0;
	if (n >= 1) {
		x++;
	}
	
	while (n > 1) {
		n /= 2;
		x++;
	}

	std::cout << x <<std::endl;
}

