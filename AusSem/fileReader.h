#pragma once

#include "libds/amt/explicit_hierarchy.h"
#include <fstream>
#include <vector>
#include "commune.h"
#include <sstream>
#include <string>
#include "libds/adt/table.h"


class fileReader
{
	
private:
	using CommuneData = TableData<commune*>;
	using Table = ds::adt::Treap<std::string, CommuneData>;
	ds::amt::MultiWayExplicitHierarchy<commune*> hierarchy;
	Table geoDivisionTable;
	Table federalRepublicTable;
	Table regionTable;
	Table communeTable;

	std::ifstream inputReader;
	std::vector<commune*> communes;
	void skipLines(int count);
	commune* containsCode(unsigned int code, std::vector<commune*> data);
	void cumulateHierarchy();
	


public:
	
	using CommuneBlock = ds::amt::MultiWayExplicitHierarchyBlock<commune*>;
	ds::amt::MultiWayExplicitHierarchy<commune*>& loadHierarchy(std::vector<commune*>& data);

	std::vector<commune*> readFile();
	Table& getGeoDivisionTable() {
		return geoDivisionTable;
	}
	Table& getFederalTable() { 
		return federalRepublicTable;
	}
	Table& getRegionTable() {
		return regionTable;
	}
	Table& getCommuneTable() {
		return communeTable;
	}


	~fileReader();


};


