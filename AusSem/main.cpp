#include <iostream>
#include "algoritmus.h"
#include "fileReader.h"
#include "libds/heap_monitor.h"
#include "libds/amt/explicit_hierarchy.h"
#include "memory"
#include <windows.h>
#include "locale"
#include "string"
#include "hierarchyIterator.h"
#include "levelThree.h"
#include "heapSort.h"
#include "FirstLevel.h"


int main()
{
	initHeapMonitor();
	using CommuneData = TableData<TerritorialUnit*>;
	using Table = ds::adt::Treap<std::string, CommuneData>;
	SetConsoleOutputCP(1250);
	SetConsoleCP(1250);
	FileReader* reader = new FileReader;
	std::vector<TerritorialUnit> dataFilter;
	std::vector<TerritorialUnit*> data = reader->readFile();
	FirstLevel levelOne(data);
	ds::amt::MultiWayExplicitHierarchy<TerritorialUnit*>& hierar = reader->loadHierarchy(data);
	HierarchyIterator* hierarIterator = new HierarchyIterator(&hierar);
	Table& geoDivisionTable = reader->getGeoDivisionTable();
	Table& communeTable = reader->getCommuneTable();
	Table& federalTable = reader->getFederalTable();
	Table& regionTable = reader->getRegionTable();
	LevelThree* three = new LevelThree(geoDivisionTable, federalTable, regionTable, communeTable);
	std::string input;
	while (true) {
		system("CLS");
		std::cout << "0 ---- uroven 1" << std::endl;
		std::cout << "1 ---- uroven 2" << std::endl;
		std::cout << "2 ---- uroven 3" << std::endl;
		std::cout << "q ---- quit" << std::endl;
		std::cin >> input;
		if (input == "0")
		{
			int number = levelOne.run();
			while (true)
			{
				if (number == -1)
				{
					break;
				}
			}
		}
		else if (input == "1") {
			while (true) {
				bool yearEntered = false;
				unsigned int year;
				int number = hierarIterator->run();
				if (number == -1)
				{
					break;
				}
			}
		}
		else if (input == "2") {
			while (true) {

				int number = three->run();
				if (number == -1)
				{
					break;
				}
			}
		}
		else if (input == "q") {
			break;
		}
	}
	delete reader;
	delete hierarIterator;
	delete three;
	
}























