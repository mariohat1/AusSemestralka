#include <Windows.h>
#include <iostream>
#include "algoritmus.h"
#include "fileReader.h"
#include "libds/heap_monitor.h"
#include "libds/amt/explicit_hierarchy.h"
#include "memory"
#include "communeIterator.h"



int main()
{
	SetConsoleOutputCP(1250);
	SetConsoleCP(1250);
	algoritmus algoritmus;
	fileReader reader;
	std::vector<commune*> data = reader.readFile();
	std::vector<commune> dataFilter;
	communeIterator iteratorComm;
	using CommuneBlock = ds::amt::MultiWayExplicitHierarchyBlock<commune*>;

	ds::amt::MultiWayExplicitHierarchy<commune*>& bingo = reader.loadHierarchy();
	
	

	auto hasMaxResidents = [](commune& comm, unsigned int max, unsigned int year) -> bool {
		return comm.getPopulation(year) <= max;
		};
	auto hasMinResidents = [](commune& comm, unsigned int min, unsigned int year) -> bool {
		return comm.getPopulation(year) >= min;
		};

	auto containsStr = [](commune& comm, const char* retazec) -> bool {
		const char* name = comm.getName();
		size_t nameLen = strlen(name);
		size_t retazecLen = strlen(retazec);
		bool found = true;
		if (retazecLen > nameLen)
		{
			return false;
		}
		for (size_t i = 0; i < nameLen; i++)
		{
			found = true;
			for (size_t j = 0; j < retazecLen; j++)
			{
				if (name[i + j] != retazec[j])
				{
					found = false;
				}
			}
			if (found) {
				break;
			}
		}
		return found;
		};
	char userInput;
	ds::amt::MultiWayExplicitHierarchy<commune*>::PreOrderHierarchyIterator currentIterator = bingo.begin();
	while (true) {
		iteratorComm.hierarchyIterator(currentIterator, bingo.end());

	}
	dataFilter = algoritmus.filter(bingo.begin(), bingo.end(), "öf", containsStr);
	for (auto& comm : dataFilter)
	{

		comm.print();
	}


	unsigned int year = 2022;

	dataFilter = algoritmus.filter(data.begin(), data.end(), 100, year, hasMaxResidents);
	for (auto& comm : dataFilter)
	{
		comm.print(year);
	}
	dataFilter = algoritmus.filter(data.begin(), data.end(), 15000, year, hasMinResidents);
	for (auto& comm : dataFilter)
	{
		comm.print(year);
	}






}


