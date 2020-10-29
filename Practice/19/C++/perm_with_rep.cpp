#include <iostream>
#include <map>
#include <iterator>

void print_permutations(std::map<char, int>& usages, 
			std::string& str,
			char *result,
			int last,
			int index,
			int repetition_left) {

        for (auto itr = usages.begin();
	     itr != usages.end(); ++itr) {

                if (itr->second - 1 > repetition_left) {
                        continue;
                }

                result[index] = itr->first;
                itr->second++;
                
                if (last == index) {
                        std::cout << result << " ";
		} else {
                        int is_repeated = itr->second > 1;
                        print_permutations(usages, str, result, last, 
					        index + 1, repetition_left - is_repeated);
                }
                itr->second--;
        }
        
        return;
}


void start(int n, std::string str) {

        if (n < 1 || n > 9) {
                std::cerr << "Invalid 'n'! Expected 'n' in"
					"bounds [1, 9], got " << n << "." << std::endl;
                return;
        }

        char *result_heap = new char[n+1];
		result_heap[n] = '\0';
        
        std::map<char, int> usages;
        for (char ch : str)
			usages[ch] = 0;
        
        print_permutations(usages, str, result_heap, n-1, 0,
				n - str.length());

	std::cout << std::endl;
	delete[] result_heap;
}

int main() {

        std::cout << "Enter number and then characters in password." << std::endl;

		int n;
		std::string str;
		std::cin >> n >> str;

        start(n, str);
}
