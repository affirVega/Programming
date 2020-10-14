#include <iostream>

const int NUMBERS = 37;
const int k = 12;

int main() {
    int blacks = 0, reds = 0;
    
    int count[NUMBERS];            // Сколько раз выпало
    int round_appearance[NUMBERS]; // Последний раунд, когда число выпало
    for (int i = 0; i < NUMBERS; i++)
        count[i] = round_appearance[i] = 0;
    
    int input;
    int round_now = 0;
    while (++round_now) {
        std::cin >> input;
    	if (input < 0)
    	    break;
    	    
    	    
        // Записываем, что выпало какое-то число
        count[input]++;
        round_appearance[input] = round_now;
            
            
        // Номера, которые выпали чаще всего
        // Ищем самое большое число выпадений
        int highest_number = -1;
    	for (int i = 0; i < NUMBERS; i++)
    	    if (count[i] > highest_number)
    	        highest_number = count[i];
    	
    	// Выводим числа, которые выпадали чаще всего
    	for (int i = 0; i < NUMBERS; i++)
            if (count[i] == highest_number)
                std::cout << i << " ";
    	std::cout << std::endl;
    
        // Номера, которые не выпадали последние k раундов
    	for (int i = 0; i < NUMBERS; i++)
    	    if (round_appearance[i] == 0 || (round_now - round_appearance[i] > k))
                std::cout << i << " ";
    	std::cout << std::endl;
            
        
        // Сколько красных и чёрных выпало
    	if (input != 0) {
            if (input <= 10 ||(input > 18 && input <= 28))
                if (input % 2 == 1) ++reds;
                else                ++blacks;
            else
                if (input % 2 == 0) ++reds;
                else                ++blacks;
    	}
    	
        std::cout << reds << " " << blacks << std::endl;
        std::cout << std::endl;
    }
}
