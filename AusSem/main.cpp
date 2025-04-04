#include <Windows.h>
#include <iostream>
#include "algoritmus.h"
#include "fileReader.h"
#include "libds/heap_monitor.h"
#include "libds/amt/explicit_hierarchy.h"
#include "memory"
#include "communeIterator.h"
#include <conio.h>




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
	using iterator = ds::amt::MultiWayExplicitHierarchy<commune*>::PreOrderHierarchyIterator;
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

	/*--------------------------------------------------------------------------------------------------------
	--------------UROVEN 2------------------------------------------------------------------------------------
	 */


	std::string userInput;



	CommuneBlock* currentIterator = bingo.accessRoot();
	iterator currentIteratorPre(&bingo, currentIterator);
	iterator currentIteratorEnd(&bingo, nullptr);



	while (true) {
		std::cout << "s ---- select son at index -- next argument [index]" << std::endl;
		std::cout << "p ---- select predicate -- next argument [index] of predicate" << std::endl;
		std::cout << "u ---- back to parent -- no next arguments" << std::endl;
		std::cout << "q ---- quit" << std::endl;


		unsigned int count = 0;
		if (!currentIterator->sons_->isEmpty())
		{
			for (auto it = currentIterator->sons_->begin(); it != currentIterator->sons_->end(); ++it)
			{
				CommuneBlock* comm = *it;
				std::cout << count << " " << comm->data_->getName() << std::endl;
				count++;
			}


		}
		else {
			std::cout << currentIterator->data_->getName() << std::endl;
		}
		//--------------------------------------------------------------------------//


		;
		std::cin >> userInput;
		if (userInput == "s")
		{
			unsigned int sonOrder;
			std::string sonOrderInput;
			std::cin >> sonOrderInput;
			sonOrder = stoi(sonOrderInput);

			if (sonOrder <= count)
			{
				currentIterator = bingo.accessSon(*currentIterator, sonOrder);
			}
		} else if (userInput == "p") {
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
				
				iterator currentIteratorPreCopy = iterator(&bingo, currentIterator);


				if (predicateInput == "0") {
					dataFilter = algoritmus.filter(currentIteratorPreCopy, currentIteratorEnd, count, year, hasMinResidents);

				}
				if (predicateInput == "1") {
					dataFilter = algoritmus.filter(currentIteratorPreCopy, currentIteratorEnd, count, year, hasMaxResidents);

				}
			

			}
			if (predicateInput == "2") {
				iterator currentIteratorPreCopy = iterator(&bingo, currentIterator);
				std::string strInput;
				std::cout << "str:  ";
				std::cin >> strInput;

				dataFilter = algoritmus.filter(currentIteratorPreCopy, currentIteratorEnd, strInput.c_str(), containsStr);
				
			}
			system("CLS");
			for (auto& comm : dataFilter)
			{
				comm.print(2020);
			}
		}


		
	}













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






}


