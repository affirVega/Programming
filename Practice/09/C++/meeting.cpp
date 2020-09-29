#include <iostream>
#include <sstream>

const int MINUTES_IN_HOUR = 60;

int main() {
    std::cout << "Введите 2 момента времени в формате \"ЧЧ:ММ\", каждое с новой строки." << std::endl;
    int h1, m1, h2, m2;
    char temp;
    std::cin >> h1 >> temp >> m1 >> h2 >> temp >> m2;
    m1 += h1 * MINUTES_IN_HOUR;
    m2 += h2 * MINUTES_IN_HOUR;

    if (std::abs(m1 - m2) <= 15) {
        std::cout << "Встреча состоится!" << std::endl;
    }  else {
        std::cout << "Встреча не состоится!" << std::endl;
    }
}
