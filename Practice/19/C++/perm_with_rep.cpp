#include <iostream>
#include <map>
#include <iterator>

void print_permutations(std::map<char, int> *usages, 
						std::string str, 
                        char result[], 
						int last, 
						int index, 
						int repetition_left)
{
        int length = str.length();
        
        std::map<char, int>::iterator itr;
        
        // Cycle through every key-value
        for (itr = usages->begin(); itr != usages->end(); ++itr)
        {
//				std::cout << "index=" << index << "\nrepetition_left=" << repetition_left
//						<< "\nresult=" << result << "\nworking with char: " << itr->first
//						<< "\tusages: " << itr->second << "\n\n";
                
				// if amount of usages of character is more than allowed, then
                // choose next character
                if (itr->second > repetition_left)
				{
//						std::cout << "Usages are more than allowed repetitions!\n\n";
                        
                        continue;
                        
                }
                
                result[index] = itr->first;
                itr->second++;
                
                if (last == index)
                {
//						std::cout << "This is the last index filled. Permutation is: ";
                        
                        std::cout << result << " ";
                        
                } else
                {
                        
                        int is_repeated = itr->second > 1;

//						if (is_repeated)
//						{
//								std::cout << "Character " << itr->first << " was used at least 2 times in perm.\n\n";
//						} else
//						{
//								std::cout << "Character " << itr->first << " was used first time in perm.\n\n";
//						}
                        
                        print_permutations(usages, str, result, last, 
								index + 1, repetition_left - is_repeated);
                        
                }
                
                itr->second--;
                
        }
        
        return;
}


void start(int n, std::string str)
{
        if (n < 1 || n > 9)
        {
                
                std::cerr << "Invalid 'n'! Expected 'n' in bounds [1, 9], got " << n 
                    << "." << std::endl;
                return;
                
        }

        char result[n];
        
        std::map<char, int> usages;
        for (char ch : str)
        {
                
                usages.insert(
                    std::pair<char, int>(ch, 0)
                );
                
        }
        
        print_permutations(&usages, str, result, n-1, 0, n - str.length());
		std::cout << std::endl;
}

int main()
{
        std::cout << "Enter number and then characters in password." << std::endl;

		int n;
		std::string str;
		std::cin >> n >> str;

        start(n, str);
}
