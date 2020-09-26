#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
	srand(time(NULL));
	int guess;
	int n;
	bool want_to_play;
	bool win;

	std::cout << "Это программа, где вам надо угадать число, загаданное компьютером от 0 до 100 включительно.\nВам даётся 5 попыток." << std::endl;
	std::cout << "Введите целое число." << std::endl;
	do{
		want_to_play = false;
		win = false;

		n = rand() % 101;
		for (int tries = 5; tries > 0; tries--) {
			std::cin >> guess;

			if (guess < n) {
				std::cout << "Загаданное число больше" << std::endl;
			} else if (guess > n) {
				std::cout << "Загаданное число меньше" << std::endl;
			} else {
				std::cout << "Поздравляю! Вы угадали" << std::endl;
				win = true;
				break;
			}
		}
		if (!win) {
			std::cout << "Вы проиграли. Было загадано: " << n << std::endl;
		}

		std::cout << "Хотите начать сначала? (1 - да)" << std::endl;
		std::cin >> guess;
		if (guess == 1) {
			want_to_play = true;
		}
	} while (want_to_play);
}

