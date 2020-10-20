#include <iostream>

struct Drink {
	std::string name;
	long long   price;
	long long   volume;
};

int main()
{
	long long balance, drink_amount;
	std::cin >> balance >> drink_amount;

	Drink best;
	Drink input;
	for (int i = 0; i < drink_amount; ++i) {
		std::cin >> input.name >> input.price >> input.volume;

		long long liters = (balance / input.price) * input.volume;

		if (liters == 0)
		    continue;

		if (best.price == 0) {
			best = input;
			continue;
		}

		long long best_liters = (balance / best.price) * best.volume;

		if (liters > best_liters)
			best = input;
	}

	if (best.price == 0)
		std::cout << -1 << std::endl;
	else {
		long long bottles = balance / best.price;
		std::cout << best.name << " " << bottles << "\n" 
		    << bottles * best.volume << "\n"
		    << balance - best.price * bottles << std::endl;
	}
}
