#include <Windows.h>
#include <iostream>
#include "algoritmus.h"
#include "fileReader.h"
#include "libds/heap_monitor.h"
#include "libds/amt/explicit_hierarchy.h"
#include "memory"

#include <conio.h>




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
		using CommuneBlock = ds::amt::MultiWayExplicitHierarchyBlock<commune*>;
		using iterator = ds::amt::MultiWayExplicitHierarchy<commune*>::PreOrderHierarchyIterator;
		ds::amt::MultiWayExplicitHierarchy<commune*>& bingo = reader.loadHierarchy(data);

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
			destroy(name);
			return found;
			};

		/*--------------------------------------------------------------------------------------------------------
		--------------UROVEN 2------------------------------------------------------------------------------------
		 */


		std::string userInput;



		CommuneBlock* currentPosition = bingo.accessRoot();
		iterator currentIteratorPre(&bingo, currentPosition);
		iterator currentIteratorEnd(&bingo, nullptr);



		while (true) {

			std::cout << "s ---- select son at index -- next argument [index]" << std::endl;
			std::cout << "p ---- select predicate -- next argument [index] of predicate" << std::endl;
			std::cout << "u ---- back to parent --no next arguments" << std::endl;
			std::cout << "q ---- quit" << std::endl;
			std::cout << "current Parent: " << currentPosition->data_->getName() << std::endl;

			unsigned int count = 0;
			if (!currentPosition->sons_->isEmpty())
			{
				for (auto it = currentPosition->sons_->begin(); it != currentPosition->sons_->end(); ++it)
				{
					CommuneBlock* comm = *it;
					std::cout << count << " " << comm->data_->getName() << std::endl;
					count++;
				}


			}


			//--------------------------------------------------------------------------//


			;
			std::cin >> userInput;
			if (userInput == "s" && !currentPosition->sons_->isEmpty())
			{

				unsigned int sonOrder;
				std::string sonOrderInput;
				std::cin >> sonOrderInput;
				sonOrder = stoi(sonOrderInput);

				if (sonOrder <= count)
				{
					currentPosition = bingo.accessSon(*currentPosition, sonOrder);
				}
				system("CLS");
			}
			else if (userInput == "p") {
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
					std::cin >> strInput;
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
			else if (userInput == "u") {
				system("CLS");
				if (currentPosition->parent_ != nullptr)
				{
					currentPosition = bingo.accessParent(*currentPosition);
				}
				else {
					std::cout << "Parent does not exist" << std::endl;
				}
				std::cout << std::endl;


			}
			else if (userInput == "q") {

				bingo.processPostOrder(bingo.accessRoot(), [](CommuneBlock* node) {
					std::cout << node->data_ << std::endl;
					delete node->data_;
					node->data_ = nullptr;
					});

				data.clear();
				bingo.clear();

				break;
			}




		}

	}
	_CrtDumpMemoryLeaks();











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


