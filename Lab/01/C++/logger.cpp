#include <fstream>
#include <ctime>
#include <iomanip>

void log_append_line(std::string line) {
	std::ofstream log("server.log", std::ofstream::app);
	log << line << std::endl;
	log.close();
}

void log_overwrite_line(std::string line) {
	std::ofstream log("server.log");
	log << line << std::endl;
	log.close();
}