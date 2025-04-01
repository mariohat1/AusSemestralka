#pragma once
#include <fstream>
#include <vector>
#include "commune.h"
#include <sstream>
#include <string>
#include "libds/amt/explicit_hierarchy.h"



class fileReader
{
	
private:
	ds::amt::MultiWayExplicitHierarchy<int> hierarchy;

	std::ifstream inputReader;
	std::vector<commune> data;
	void skipLines(int count);
	commune* containsCode(unsigned int code);
	
	


public:

	std::vector<commune> readFile();
	~fileReader();


};


