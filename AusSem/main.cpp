
#include <iostream>
#include "algorithm.h"
#include "file_reader.h"
int main()
{
	algorithm algoritmus;
	file_reader reader;
	std::vector<commune> data = reader.read_file(2020);
	auto pred = [](commune& comm, unsigned int min) -> bool {
		return comm.getPopulation() >= min;
		};
	algoritmus.hasMinResidentsFilter(data.begin(), data.end(), 2000, pred);
	std::string name = "H‰rbranz"; // Reùazec s diakritikou
	std::cout << name << std::endl; //
}

