#include <Windows.h>
#include <iostream>
#include "algorithm.h"
#include "fileReader.h"

int main()
{
	SetConsoleOutputCP(1250);
	SetConsoleCP(1250);
	algorithm<commune> algoritmus;
	fileReader reader;
	std::vector<commune> data = reader.readFile(2020);

	std::vector<commune> dataFilter;
	//algoritmus.hasResidentsFilter(data.begin(), data.end(), 1200);
	auto hasMaxResidents = [](commune& comm, unsigned int max) -> bool {
		return comm.getPopulation() <= max; 
		};
	//algoritmus.hasResidentsFilter(data.begin(), data.end(), 1200, hasMaxResidents);
	dataFilter = algoritmus.filter(data.begin(), data.end(), 100, hasMaxResidents);
	for  (auto& comm : dataFilter)
	{
		comm.print();
	}
	dataFilter = algoritmus.filter(data.begin(), data.end(), "Gro");
	for (auto& comm : dataFilter)
	{
		comm.print();
	}
	
}

