#include <iostream>
#include "algoritmus.h"
#include "fileReader.h"
#include "libds/heap_monitor.h"
#include "libds/amt/explicit_hierarchy.h"
#include "memory"
#include <windows.h>

#include "hierarchyIterator.h"
#include "levelThree.h"

auto hasType = [&](commune& comm, size_t level) -> bool {

	return comm.getLevel() == level;
	};


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
using CommuneBlock = ds::amt::MultiWayExplicitHierarchyBlock<commune*>;
using iterator = ds::amt::MultiWayExplicitHierarchy<commune*>::PreOrderHierarchyIterator;
using TableData = CommuneData<commune*>;
using Table = ds::adt::Treap<std::string, TableData>;

/*dataFilter = algoritmus.filter(bingo.begin(), bingo.end(), "öf", containsStr);
for (auto& comm : dataFilter)
{
	comm.print();
}*/


/*unsigned int year = 2022;

dataFilter = algoritmus.filter(data.begin(), data.end(), 100, year, hasMaxResidents);
for (auto& comm : dataFilter)
{
	comm.print(year);
}
dataFilter = algoritmus.filter(data.begin(), data.end(), 15000, year, hasMinResidents);
for (auto& comm : dataFilter)
{
	comm.print(year);
}*/

int main()
{
	initHeapMonitor();
	{


		SetConsoleOutputCP(1250);
		SetConsoleCP(1250);
		algoritmus algoritmus;
		fileReader reader;
		std::vector<commune> dataFilter;
		std::vector<commune*> data = reader.readFile();
		ds::amt::MultiWayExplicitHierarchy<commune*>& bingo = reader.loadHierarchy(data);
		iterator currentIteratorEnd(&bingo, nullptr);
		hierarchyIterator hierarIterator(bingo);

		Table& geoDivisionTable = reader.getGeoDivisionTable();
		Table& communeTable = reader.getCommuneTable();
		Table& federalTable = reader.getFederalTable();

		Table& regionTable = reader.getRegionTable();
		levelThree three(geoDivisionTable, federalTable, regionTable, communeTable);



		std::string input;
		std::cout << "0 ---- uroven 2" << std::endl;
		std::cout << "1 ---- uroven 3" << std::endl;
		std::cin >> input;
		if (input == "0") {




			while (true) {

				CommuneBlock* currentPosition = hierarIterator.run();
				if (currentPosition == nullptr)
				{
					break;
				}
				std::string predicateInput;
				std::cout << "0 ---- hasMinResidents" << std::endl;
				std::cout << "1 ---- hasMaxResidents" << std::endl;
				std::cout << "2 ---- containsStr" << std::endl;
				std::cout << "3 ---- hasType" << std::endl;
				std::cin >> predicateInput;

				if (predicateInput == "0" || predicateInput == "1") {
					std::string yearInput;
					std::string countInput;
					unsigned int year;
					int count;

					std::cout << "year(2020,2021,2022,2023,2024):  ";
					std::cin >> yearInput;
					year = stoi(yearInput);
					while (year != 2020 && year != 2021 && year != 2022 && year != 2023 && year != 2024)
					{
						std::cout << "wrong year input";
						std::cout << "year(2020,2021,2022,2023,2024):  ";
						std::cin >> yearInput;
						year = stoi(yearInput);
					}

					std::cout << "count(>= 0):  ";
					std::cin >> countInput;
					count = stoi(countInput);
					while (count < 0)
					{
						std::cout << "wrong count input";
						std::cout << "count(>= 0):  ";
						std::cin >> countInput;
						count = stoi(countInput);
					}

					iterator currentIteratorPreCopy = iterator(&bingo, currentPosition);
					system("CLS");
					std::cout << "Filtered: " << std::endl;
					if (predicateInput == "0") {
						dataFilter = algoritmus.filter(currentIteratorPreCopy, currentIteratorEnd, count, year, hasMinResidents);

					}
					if (predicateInput == "1") {
						dataFilter = algoritmus.filter(currentIteratorPreCopy, currentIteratorEnd, count, year, hasMaxResidents);

					}
					std::cout << std::endl;
					for (auto& comm : dataFilter)
					{
						comm.print(year);
					}

				}
				if (predicateInput == "2") {
					iterator currentIteratorPreCopy = iterator(&bingo, currentPosition);
					std::string strInput;
					std::cout << "str:  ";
					std::cin.ignore();
					std::getline(std::cin, strInput);
					system("CLS");
					std::cout << "Filtered: " << std::endl;
					dataFilter = algoritmus.filter(currentIteratorPreCopy, currentIteratorEnd, strInput.c_str(), containsStr);
					for (auto& comm : dataFilter)
					{
						comm.print();
					}
					std::cout << std::endl;
				}
				if (predicateInput == "3") {
					std::string typeInput;
					int level;
					std::cout << "0 ---- koren(krajina)" << std::endl;
					std::cout << "1 ---- geogreficke delenie" << std::endl;
					std::cout << "2 ---- spolkova republika" << std::endl;
					std::cout << "3 ---- region" << std::endl;
					std::cout << "4 ---- obec" << std::endl;
					std::cin >> typeInput;
					level = stoi(typeInput);
					while (level < 0 && level < 5)
					{
						std::cin >> typeInput;
						level = stoi(typeInput);
					}
					iterator currentIteratorPreCopy = iterator(&bingo, currentPosition);
					system("CLS");
					dataFilter = algoritmus.filter(currentIteratorPreCopy, currentIteratorEnd, level, hasType);
					for (auto& comm : dataFilter)
					{
						comm.print();
					}

					std::cout << std::endl;

				}
			}
		}
		else if (input == "1") {
			while (true) {

				int number = three.run();
				if (number == -1)
				{
					break;
				}

			}




		}

	}


}























