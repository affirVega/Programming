#include <sstream>
#include <vector>
#include <array>
#include <string>
#include <fstream>
#include <algorithm>

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}

struct Passenger {
	std::string name;
	std::string cabin;
	std::string ticket;
	float 		fare;
	int			id;
	bool 		survival;	// false = no
	uint8_t 	age;	   	// 0 - 255
	uint8_t 	pclass;		// '1' = 1st, 2nd, 3rd
	uint8_t 	sex;	   	// m - male, f - female
	uint8_t 	sibsp;	 	// number of sublings/spouses aboard
	uint8_t 	parch;	 	// number of parents/children aboard
	uint8_t 	embarked;
};

struct Passenger_str {
	std::string name;
	std::string cabin;
	std::string ticket;	 	// ticket number
	std::string fare;
	std::string id;
	std::string survival; 	// false = no
	std::string pclass;		// '1' = 1st, 2nd, 3rd
	std::string sex;	   	// m - male, f - female
	std::string age;	   	// 0 - 255
	std::string sibsp;	 	// number of sublings/spouses aboard
	std::string parch;	 	// number of parents/children aboard
	std::string embarked;
};

std::vector<std::vector<std::string>> parse_cvs(
		std::istream& out,
		char end_ch='\r',
		char quote_ch='"',
		char sep_ch=',')
{
	std::string line;
	std::string buffer;

	std::vector<std::string> seperated_string;
	std::vector<std::vector<std::string>> result;

	char quote_depth = 0;
	char pos = 0;

	while (std::getline(out, line, end_ch)) {
		pos = 0;
		quote_depth = 0;

		for (char ch : line) {
			if (ch == sep_ch) {
				switch (quote_depth) {
				case 0:
					seperated_string.push_back(buffer);
					buffer.clear();
					++pos;
					continue;
				case 2:
					seperated_string.push_back(buffer);
					buffer.clear();
					quote_depth = 0;
					++pos;
					continue;
				}
			}
			if (ch == quote_ch) {
				switch (quote_depth) {
				case 0: 
						quote_depth = 1;
						continue;
				case 1:
						quote_depth = 2;
						continue;
				case 2: 
						buffer.push_back(quote_ch);
						quote_depth = 1;
						continue;
				}
			}
			buffer.push_back(ch);
		}
		seperated_string.push_back(buffer);
		buffer.clear();

		result.push_back(seperated_string);
		seperated_string.clear();
	}
	return result;
}
std::istream& operator>> (std::istream& stream, std::vector<Passenger>& vec) {
	auto matrix = parse_cvs(stream);
	matrix.erase(matrix.begin());

	for (auto row : matrix) {
		Passenger p;

		p.id	   	= std::stoi(row[0]);
		p.survival 	= std::stoi(row[1]);
		p.pclass   	= std::stoi(row[2]);
		p.name	 	= row[3];
		p.sex	  	= row[4] == "male" ? 'm' : 'f';
		p.age	  	= row[5] == "" ? 0 : std::stof(row[5]);
		p.sibsp		= std::stoi(row[6]);
		p.parch		= std::stoi(row[7]);
		p.ticket   	= row[8];
		p.fare	 	= std::stof(row[9]);
		p.cabin		= row[10];
		p.embarked 	= row[11][0];
		
		vec.push_back(p);
	}

	return stream;
}
std::ostream& operator<< (std::ostream& stream, std::vector<Passenger>& vec) {
	char sep = ',';
	char end = '\r';
	for (auto& pass : vec) {
		std::string name = pass.name;
		name = ReplaceAll(name, "\"", "\"\"");

		stream << pass.id << sep
			<< pass.survival << sep
			<< int(pass.pclass) << sep
			<< '"' << name << '"' << sep
			<< ((pass.sex == 'm') ? "male" : "female") << sep
			<< int(pass.age) << sep
			<< int(pass.sibsp) << sep
			<< int(pass.parch) << sep
			<< pass.ticket << sep
			<< pass.fare << sep
			<< pass.cabin << sep
			<< pass.embarked
			<< end << std::flush;
	}
	return stream;
}
void sort(std::vector<Passenger*>& vec) {
	for (int i = 0; i < vec.size()-1; ++i) {
		for (int j = vec.size()-1; j > i; --j) {
			if (vec[j]->age < vec[j-1]->age)
				std::swap(*vec[j], *vec[j-1]);
		}
	}
}

int main()
{
	//std::stringstream ss(sample);
	std::ifstream file("train.csv");
	std::ofstream outfile("out.csv");
	std::vector<Passenger> passengers;

	file >> passengers;
	std::vector<Passenger*> passengers_ptr;
	
	for (auto& elem : passengers) 
		if (elem.pclass == 1 and elem.sex == 'f' and elem.survival)
			passengers_ptr.push_back(&elem);
	
	sort(passengers_ptr);
	
	outfile << passengers;

	std::vector<Passenger> newvec;
	for (auto elem : passengers_ptr) newvec.push_back(*elem);
	std::ofstream outfile2("out_woman.csv");
	outfile2 << newvec;
	return 0;
}
