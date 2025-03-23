#include <Windows.h>
#include <iostream>
#include "algoritmus.h"
#include "fileReader.h"


int main()
{
	SetConsoleOutputCP(1250);
	SetConsoleCP(1250);
	algoritmus algoritmus;
	fileReader reader;
	std::vector<commune> data = reader.readFile();
	std::vector<commune> dataFilter;
	
	auto hasMaxResidents = [](commune& comm, unsigned int max) -> bool {
		return comm.getPopulation() <= max;
		};
	auto hasMinResidents = [](commune& comm, unsigned int min) -> bool {
		return comm.getPopulation() >= min;
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



	
	//dataFilter = algoritmus.filter(data.begin(), data.end(), "aß", containsStr);
	//for (auto& comm : dataFilter)
	//{
	//	
	//	comm.print();
	//}


	
	dataFilter = algoritmus.filter(data.begin(), data.end(), 100, 2024, hasMaxResidents);
	for  (auto& comm : dataFilter)
	{
		comm.print();
	}
	dataFilter = algoritmus.filter(data.begin(), data.end(), 15000, 2020, hasMinResidents);
	for (auto& comm : dataFilter)
	{
		comm.print();
	}






}

