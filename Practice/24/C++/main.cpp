#include <fstream>
#include <iostream>
#include <iomanip>

#include "nlohmann/json.hpp"

// for convenience
using json = nlohmann::json;

int main() {
	std::ifstream input("in.json");
	std::ofstream output("out.json");
	
	json jinput;
	input >> jinput;

	json joutput;
	for (auto& element : jinput) {
		int userId = element["userId"];
		bool completed = element["completed"];

		json temp;
		json *user = &temp;

		// search for user with userId of `element`
		for (auto& out_element : joutput) {
			if (out_element["userId"] == userId) {
				user = &out_element;
				break;
			}
		}

		// if user wasn't found
		if (user->empty()) {
			joutput.push_back({
				{"userId", userId},
				{"current_tasks", 0}
			});
			
			// make `user` point to created object in joutput
			user = &(*(--joutput.end()));
		}

		if (completed) {
			(*user)["current_tasks"] = static_cast<int>((*user)["current_tasks"]) + 1;
		}
	}

	output << std::setw(2) << joutput << std::endl;
}
