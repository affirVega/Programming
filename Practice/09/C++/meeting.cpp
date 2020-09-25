#include <iostream>
#include <sstream>
#include <vector>

// Без понятия особо, как эта штука работает
// От Arafat Hasan из StackOverflow в ответ на вопрос TheCrazyProgrammer
//std::vector<std::string> split(std::string s, std::string delimiter) {
//    size_t pos_start{0},
//           pos_end,
//           delim_len{delimiter.length()};
//    std::string token;
//    std::vector<std::string> res;
//
//    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
//        token = s.substr(pos_start, pos_end - pos_start);
//        pos_start = pos_end + delim_len;
//        res.push_back(token);
//    }
//
//    return res;
//}

int main() {
    std::string input;
    std::cout << "" << std::endl;
    getline(std::cin, input);
}
