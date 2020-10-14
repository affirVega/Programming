#include <iostream>
#include <string_view>

int main() {
    std::string_view str;
    std::string input;

    long long count;
    std::cin >> count;

    bool banknote_was_found = false;
    for (long long i = 0; i < count; ++i) {
        std::cin >> input;
        str = input;
        if (str.starts_with('a') && str.ends_with("55661")) {
            banknote_was_found = true;
            std::cout << str << " ";
        }
    }
    if (!banknote_was_found) {
        std::cout << -1 << std::endl;
    }
}
