#pragma once
#include <fstream>
#include <vector>
#include "commune.h"
#include <sstream>
#include <string>
class fileReader
{
private:
	std::ifstream inputReader;
	std::vector<commune> data;
	void skipLines(int count);
public:
	
	std::vector<commune> readFile(int year);
	~fileReader();


};

