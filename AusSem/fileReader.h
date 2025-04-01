#pragma once

#include "libds/amt/explicit_hierarchy.h"
#include <fstream>
#include <vector>
#include "commune.h"
#include <sstream>
#include <string>






class fileReader
{
	
private:
	

	ds::amt::MultiWayExplicitHierarchy<commune*> hierarchy;

	std::ifstream inputReader;
	std::vector<commune> data;
	void skipLines(int count);
	commune* containsCode(unsigned int code);
	
	


public:
	using CommuneBlock = ds::amt::MultiWayExplicitHierarchyBlock<commune*>;
	ds::amt::MultiWayExplicitHierarchy<commune*> loadHierarchy();
	std::vector<commune> readFile();
	~fileReader();


};


