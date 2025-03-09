
#include <iostream>
#include "algorithm.h"
#include "file_reader.h"
int main()
{
	SetConsoleOutputCP(1250);
	algorithm algoritmus;
	file_reader reader;
	std::vector<commune> data = reader.read_file(2020);

	//algoritmus.hasResidentsFilter(data.begin(), data.end(), 1200);
	auto hasMaxResidents = [](commune& comm, unsigned int max) -> bool {
		return comm.getPopulation() <= max; 
		};
	//algoritmus.hasResidentsFilter(data.begin(), data.end(), 1200, hasMaxResidents);
	algoritmus.filter(data.begin(), data.end(), "Spiel");
	std::string str = "Sharp S: ß";
	char nieco = 225;
	std::cout << str << std::endl << nieco;
	UINT cp = GetConsoleOutputCP();
	std::cout << "Current console code page: " << cp << std::endl;
}

