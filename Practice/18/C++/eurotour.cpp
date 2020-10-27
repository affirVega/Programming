#include <iostream>
#include <vector>
#include <string_view>

/*
 * I'm definately gonna forget EVERYTHING about how this code works lol
 * */

typedef std::vector<std::string> strvec_t;

const int NUM_OF_CHARS = (int)'z'-'a';
const strvec_t KNOWN_WORDS = {"hallo", "klempner", "das", "ist", "fantastisch", "fluggegecheimen"};

double chances[NUM_OF_CHARS];

void calculate_chances(strvec_t words) {
	int count[NUM_OF_CHARS];
	for (int i = 0; i < NUM_OF_CHARS; ++i)
	    count[i] = 0;

	int overall_length = 0;
	for (int j = 0; j < words.size(); ++j) {
	    std::string word = words[j];
        overall_length += word.length();
        for (int i = 0; i < word.length(); ++i) {
            int index = word[i] - 'a';
            if (index < NUM_OF_CHARS)
                count[index] += 1;
        }
	}

	for (int i = 0; i < NUM_OF_CHARS; ++i) {
	    chances[i] = count[i] / double(overall_length);
	}
}

int main() {
    calculate_chances(KNOWN_WORDS);
	

	std::string input; std::cin >> input;

	std::string_view word = input;
	double pronounce_chance = chances[word[0] - 'a'];
	if (pronounce_chance == 0) {
		std::cout << "First character is unknown." << std::endl;
		return -1;
	}

	double prev_chance = pronounce_chance;

	for (int i = 1; i < word.length(); ++i) {

		if (chances[word[i]-'a'] == 0.0) {

			if (prev_chance == 0.0) {
				std::cout << "Error: character at index " << i << " is not known!" 
						  << std::endl;
				return -1;
			} else {
				pronounce_chance *= prev_chance;
			}
		} else {
			pronounce_chance *= chances[word[i]-'a'];
			prev_chance = pronounce_chance;
		}
	}
	
	std::cout << pronounce_chance << std::endl;

	for (int i = 0; i < NUM_OF_CHARS; i++) {
		std::cout << "\t" << char('a' + i) << " " << chances[i] << std::endl;
	}
}
