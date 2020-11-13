#include <fstream>
#include <iostream>
#include <iomanip>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

json* find_by_user_id(json &container, int userId) {
	json temp;
	json *user = &temp;

	std::string field = "userId";

	for (auto& element : container) {
		if (element[field] == userId) {
			user = &element;
			break;
		}
	}

	return user;
}

json* create_if_empty(json &container, json *object, int userId) {
	if (object->empty()) {
		container.push_back({
			{"userId", userId},
			{"task_completed", 0}
		});
		
		// make `object` point to created object in container
		object = &*--container.end();
	}

	return object;
}

int main() {
	std::ifstream input("in.json");
	std::ofstream output("out.json");
	
	json jinput;
	input >> jinput;

	json joutput;
	for (auto& element : jinput) {
		int  userId    = element["userId"];
		bool completed = element["completed"];

		json &user = *create_if_empty(joutput,
									  find_by_user_id(joutput, userId),
									  userId);

		if (completed) {
			user["task_completed"] = static_cast<int>(user["task_completed"]) + 1;
		}
	}

	output << std::setw(2) << joutput << std::endl;
}
