#include <iostream>
#include <sstream>
#include <vector>

const int MINUTES_IN_HOUR = 60;

int main() {
    std::cout << "Введите 2 момента времени в формате \"ЧЧ:ММ\", каждое с новой строки." << std::endl;
    int hour1, minutes1, hour2, minutes2;
    char temp;
    std::cin >> hour1 >> temp >> minutes1 >> hour2 >> temp >> minutes2;
    minutes1 += hour1 * MINUTES_IN_HOUR;
    minutes2 += hour2 * MINUTES_IN_HOUR;

    if (std::abs(minutes1 - minutes2) <= 15) {
        std::cout << "Встреча состоится!" << std::endl;
    }  else {
        std::cout << "Встреча не состоится!" << std::endl;
    }
}
