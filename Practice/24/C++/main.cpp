#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

int main() {
    std::ifstream input("in.json");
    json jinput; input >> jinput; input.close();

	std::map<int, int> users;
    for (auto& task : jinput) {
        int  userId    = task["userId"];
        bool completed = task["completed"];

		users.try_emplace(userId, 0);
		if (completed) {
			++users[userId];
		}
    }

    json joutput;
	for (auto& pair : users) {
		joutput.push_back(
			{
				{"userId", pair.first},
				{"task_completed", pair.second}
			}
		);
	}

    std::ofstream output("out.json");
    output << std::setw(2) << joutput << std::endl;
	output.close();
}
