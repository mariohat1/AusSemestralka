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
	
	void skipLines(int count);
	commune* containsCode(unsigned int code, std::vector<commune*> data);
	void cumulateHierarchy();
	


public:
	using CommuneBlock = ds::amt::MultiWayExplicitHierarchyBlock<commune*>;
	ds::amt::MultiWayExplicitHierarchy<commune*>& loadHierarchy(std::vector<commune*>& data);

	std::vector<commune*> readFile();
	~fileReader();


};


