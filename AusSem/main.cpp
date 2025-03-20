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
	//algoritmus.hasResidentsFilter(data.begin(), data.end(), 1200);
	auto hasMaxResidents = [](commune& comm, unsigned int max) -> bool {
		return comm.getPopulation() <= max; 
		};
	/*algoritmus.hasResidentsFilter(data.begin(), data.end(), 1200, hasMaxResidents);*/
	/*dataFilter = algoritmus.filter(data.begin(), data.end(), 100, hasMaxResidents);
	for  (auto& comm : dataFilter)
	{
		comm.print();
	}*/
	dataFilter = algoritmus.filter(data.begin(), data.end(), "ß");
	for (auto& comm : dataFilter)
	{
		comm.print();
	}
	
}

