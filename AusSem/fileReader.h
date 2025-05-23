#pragma once

#include "libds/amt/explicit_hierarchy.h"
#include <fstream>
#include <vector>
#include "TerritorialUnit.h"
#include "TableData.h"
#include <sstream>
#include <string>
#include "libds/adt/table.h"


class fileReader
{
	
private:
	using CommuneData = TableData<TerritorialUnit*>;
	using Table = ds::adt::Treap<std::string, CommuneData>;
	ds::amt::MultiWayExplicitHierarchy<TerritorialUnit*> hierarchy;
	Table geoDivisionTable;
	Table federalRepublicTable;
	Table regionTable;
	Table communeTable;

	std::ifstream inputReader;

	void skipLines(int count);
	TerritorialUnit* containsCode(unsigned int code, std::vector<TerritorialUnit*> data);
	void cumulateHierarchy();
	


public:
	
	using CommuneBlock = ds::amt::MultiWayExplicitHierarchyBlock<TerritorialUnit*>;
	ds::amt::MultiWayExplicitHierarchy<TerritorialUnit*>& loadHierarchy(std::vector<TerritorialUnit*>& data);

	std::vector<TerritorialUnit*> readFile();
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


