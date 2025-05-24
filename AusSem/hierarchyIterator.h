#pragma once
#include <iostream>
#include <libds/amt/explicit_hierarchy.h>
#include "TerritorialUnit.h"
#include "heapSort.h"
#include "fileReader.h"
#include "Algoritmus.h"
class HierarchyIterator
{
private:
	using CommuneBlock = ds::amt::MultiWayExplicitHierarchyBlock<TerritorialUnit*>;
	using iterator = ds::amt::MultiWayExplicitHierarchy<TerritorialUnit*>::PreOrderHierarchyIterator;
	CommuneBlock* currentPosition;
	ds::amt::MultiWayExplicitHierarchy<TerritorialUnit*>* hierarchy;
	Algoritmus algorithm;
	iterator currentIteratorEnd;
	std::vector<TerritorialUnit> dataFilter;
	HeapSort sorter;
	int count = 0;

	void selectPredicate() {
		std::string predicateInput;
		std::cout << "0 ---- hasMinResidents" << std::endl;
		std::cout << "1 ---- hasMaxResidents" << std::endl;
		std::cout << "2 ---- containsStr" << std::endl;
		std::cout << "3 ---- hasType" << std::endl;
		std::cin >> predicateInput;
		if (predicateInput == "0" || predicateInput == "1")
		{
			residentsPredicate(predicateInput);
		}
		else if (predicateInput == "2") {
			containsPredicate();
		}
		else if (predicateInput == "3") {
			hasTypePredicate();
		}
		sortData();




	}
	void sortData() {
		std::cout << "Sort?" << std::endl;
		std::cout << "0 ---- yes" << std::endl;
		std::cout << "1 ---- no" << std::endl;
		std::string sortInput;
		std::cin >> sortInput;
		if (sortInput == "0")
		{
			system("CLS");
			std::string compareInput;
			std::cout << "0 ---- compareAlphabetical" << std::endl;
			std::cout << "1 ---- comparePopulation" << std::endl;
			std::cin >> compareInput;
			if (compareInput == "0") {
				auto compareAlphabetical = [](const TerritorialUnit& a, const TerritorialUnit& b) -> bool {
					std::locale locale("German_Germany.1250");
					return locale(std::string(a.getName()), std::string(b.getName()));

					};
				
				sorter.sort<TerritorialUnit>(dataFilter, compareAlphabetical);
				std::cout << "Sorted: " << std::endl;
				for (auto& comm : dataFilter)
				{
					comm.print();
				}
			}
			else if (compareInput == "1") {
				unsigned int compareYear;
				
				std::cout << "year: " << std::endl;
				std::cin >> compareYear;
				while (compareYear != 2020 && compareYear != 2021 && compareYear != 2022 && compareYear != 2023 && compareYear != 2024)
				{
					std::cout << "wrong year input";
					std::cout << "year(2020,2021,2022,2023,2024):  ";
					std::cin >> compareYear;
				}
				unsigned int compareGender;
				std::cout << "0--- male" << std::endl;
				std::cout << "1--- female" << std::endl;
				std::cout << "2 --- total" << std::endl;
				std::cin >> compareGender;
				auto comparePopulation = [&](const TerritorialUnit& a, const TerritorialUnit& b) {
					return a.getPopulation(compareYear, compareGender) < b.getPopulation(compareYear, compareGender);
					};
				sorter.sort<TerritorialUnit>(dataFilter, comparePopulation);
				std::cout << "Sorted: " << std::endl;
				for (auto& comm : dataFilter)
				{
					comm.print(compareYear, compareGender);
				}


			}





		}
	}

	void containsPredicate() {
		system("CLS");
		iterator currentIteratorPreCopy = iterator(hierarchy, currentPosition);
		std::string strInput;
		std::cout << "str:  ";
		std::cin.ignore();
		std::getline(std::cin, strInput);
		system("CLS");
		std::cout << "Filtered: " << std::endl;
		auto containsStr = [&](TerritorialUnit& comm) -> bool {
			const char* name = comm.getName();
			size_t nameLen = strlen(name);
			size_t retazecLen = strlen(strInput.c_str());
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
					if (name[i + j] != strInput[j])
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

		dataFilter = algorithm.filter(currentIteratorPreCopy, currentIteratorEnd, containsStr);
		for (auto& comm : dataFilter)
		{
			comm.print();
		}


	}


	void hasTypePredicate() {
		system("CLS");
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
		iterator currentIteratorPreCopy = iterator(hierarchy, currentPosition);
		system("CLS");
		auto hasType = [&](TerritorialUnit& comm) -> bool {

			return comm.getLevel() == level;
			};
		dataFilter = algorithm.filter(currentIteratorPreCopy, currentIteratorEnd, hasType);



		for (auto& comm : dataFilter)
		{
			comm.print();
		}




	}

	void residentsPredicate(std::string option) {
		system("CLS");
		std::string yearInput;
		std::string countInput;

		int count;

		std::cout << "year(2020,2021,2022,2023,2024):  ";
		std::cin >> yearInput;
		int year = stoi(yearInput);
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

		iterator currentIteratorPreCopy = iterator(hierarchy, currentPosition);
		system("CLS");
		std::cout << "Filtered: " << std::endl;
		if (option == "0") {
			auto hasMinResidents = [&](TerritorialUnit& comm) -> bool {
				return comm.getPopulation(year) >= count;
				};
			dataFilter = algorithm.filter(currentIteratorPreCopy, currentIteratorEnd, hasMinResidents);
		}

		if (option == "1") {
			auto hasMaxResidents = [&](TerritorialUnit& comm) -> bool {
				return comm.getPopulation(year) <= count;
				};
			dataFilter = algorithm.filter(currentIteratorPreCopy, currentIteratorEnd, hasMaxResidents);
		}
		for (auto& comm : dataFilter)
		{
			comm.print(year);
		}





	}




	void selectSon() {

		if (!currentPosition->sons_->isEmpty())
		{

			int sonOrder;
			std::string sonOrderInput;
			std::cin >> sonOrderInput;
			sonOrder = stoi(sonOrderInput);

			if (sonOrder <= this->count)
			{
				currentPosition = hierarchy->accessSon(*currentPosition, sonOrder);
			}
			system("CLS");

		}
	}
	void moveUp() {
		system("CLS");
		if (currentPosition->parent_ != nullptr)
		{
			currentPosition = hierarchy->accessParent(*currentPosition);
		}
		else {
			std::cout << "Parent does not exist" << std::endl;
		}
	}



	void displayMenu() {
		std::cout << "s ---- select son at index -- next argument [index]" << std::endl;
		std::cout << "p ---- select predicate -- next argument [index] of predicate" << std::endl;
		std::cout << "u ---- back to parent --no next arguments" << std::endl;
		std::cout << "q ---- quit" << std::endl;
		std::cout << "current Parent: " << currentPosition->data_->getName() << std::endl;

		this->count = 0;
		if (!currentPosition->sons_->isEmpty())
		{
			for (auto it = currentPosition->sons_->begin(); it != currentPosition->sons_->end(); ++it)
			{
				CommuneBlock* comm = *it;
				std::cout << this->count << " " << comm->data_->getName() << std::endl;
				this->count++;
			}


		}
	}
public:
	HierarchyIterator(ds::amt::MultiWayExplicitHierarchy<TerritorialUnit*>* hierarchy)
		: hierarchy(hierarchy), currentPosition(hierarchy->accessRoot()), currentIteratorEnd(hierarchy, nullptr) {
	}

	int run() {
		this->currentPosition = hierarchy->accessRoot();
		while (true) {
			std::string userInput;

			displayMenu();
			std::cin >> userInput;

			if (userInput == "s") {
				selectSon();
			}
			else if (userInput == "p") {
				this->selectPredicate();
			}
			else if (userInput == "u") {
				moveUp();
			}
			else if (userInput == "q") {
				return -1;

			}
		}

	}

	

};

