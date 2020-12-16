#include "raii_file.hpp"

std::fstream& raii_file::get()
{
	return _file;
}

raii_file::operator bool() const
{
	return _file.is_open();
}

raii_file::raii_file(const std::string filename,
		std::ios_base::openmode mode)
	  : _file(filename, mode)
{
}

raii_file::~raii_file()
{
	if (_file.is_open())
	{
		_file.close();
	}
}
