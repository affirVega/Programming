#pragma once
#include <fstream>

class raii_file
{
	std::fstream _file;

public:
	std::fstream& get();
	operator bool() const;
	raii_file(const std::string filename,
			std::ios_base::openmode mode = std::ios_base::in|std::ios_base::out);
	~raii_file();
};
