#pragma once
#include "algoritmus.h"
#include "heapSort.h"
class FirstLevel {
private:
	std::vector<TerritorialUnit> dataFilter;
	std::vector<TerritorialUnit*> data;
	Algoritmus algorithm;
	HeapSort sorter;
public:
	FirstLevel(std::vector<TerritorialUnit*>& communes) : data(communes) {}
	int run() {
		while (true)
		{	
		std::string predicateInput;
		std::cout << "Predicates" << std::endl;
		std::cout << "0 ---- hasMinResidents" << std::endl;
		std::cout << "1 ---- hasMaxResidents" << std::endl;
		std::cout << "2 ---- containsStr" << std::endl;
		std::cout << "q --- quit" << std::endl;
		std::cin >> predicateInput;
		if (predicateInput == "0" || predicateInput == "1")
		{
			residentsPredicate(predicateInput);
		}
		else if (predicateInput == "2") {
			containsPredicate();
		}
		else if (predicateInput == "q") {
			return -1;
			
		}
		sortData();
		}
	};

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

		system("CLS");
		std::cout << "Filtered: " << std::endl;
		if (option == "0") {
			auto hasMinResidents = [&](TerritorialUnit& comm) -> bool {
				return comm.getPopulation(year) >= count;
				};
			dataFilter = algorithm.filter(data.begin(), data.end(), hasMinResidents);
		}

		if (option == "1") {
			auto hasMaxResidents = [&](TerritorialUnit& comm) -> bool {
				return comm.getPopulation(year) <= count;
				};
			dataFilter = algorithm.filter(data.begin(), data.end(), hasMaxResidents);
		}
		for (auto& comm : dataFilter)
		{
			comm.print(year);
		}	
	}

	void containsPredicate() {
		system("CLS");
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

		dataFilter = algorithm.filter(data.begin(), data.end(), containsStr);
		for (auto& comm : dataFilter)
		{
			comm.print();
		}	
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
			system("CLS");
			if (compareInput == "0") {
				auto compareAlphabetical = [](const TerritorialUnit& a, const TerritorialUnit& b) -> bool {
					std::locale locale("German_Germany.1250");
					return locale(std::string(a.getName()), std::string(b.getName()));

					};
				std::cout << "Sorted: " << std::endl;
				sorter.sort<TerritorialUnit>(dataFilter, compareAlphabetical);
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
};


