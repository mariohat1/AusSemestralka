#pragma once
#include <fstream>
#include <vector>
#include "commune.h"
#include <sstream>
#include <string>
class file_reader
{
private:
	std::ifstream input_reader;
	std::vector<commune> data;
	void skip_lines(int count);
public:
	
	std::vector<commune>& read_file(int year);
	~file_reader();


};

