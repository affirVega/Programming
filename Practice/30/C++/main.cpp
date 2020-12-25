# include "main.h"
# include <iostream>

int main() {
    using std::cout;
    using std::cin;
    using std::endl;

    std::string input;
    while (true) {
        cout << "Открыть лутбокс? Yes/No" << endl;
        
        cin >> input;

        if (input == "Y" or input == "y" or input == "Yes" or input == "yes") {
            auto box = generateLootBox();
            cout << box << endl;
        }
        else if (input == "N" or input == "n" or input == "No" or input == "no") {
            break; // from while
        }
    }
};
