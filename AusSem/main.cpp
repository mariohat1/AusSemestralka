
#include <iostream>
#include "algorithm.h"
#include "file_reader.h"
int main()
{
	SetConsoleOutputCP(1252);
	algorithm algoritmus;
	file_reader reader;
	std::vector<commune> data = reader.read_file(2020);
	auto pred = [](commune& comm, unsigned int min) -> bool {
		return comm.getPopulation() >= min;
		};
	algoritmus.hasMinResidentsFilter(data.begin(), data.end(), 1200, pred);
	std::string str = "Sharp S: ß";
	char nieco = 225;
    std::cout << str << std::endl << nieco;
	UINT cp = GetConsoleOutputCP();
	std::cout << "Current console code page: " << cp << std::endl;
}

