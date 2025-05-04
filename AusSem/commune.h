#pragma once
#include <iostream>
#include "year.h"
#include <vector>

class commune
{
private:
	char* name = nullptr;
	unsigned int  code = 0;
	std::vector<year> years;
	size_t level = 0;
	
public:
	commune(const  char* name, const  unsigned int code);
	commune(const commune& other);
	commune& operator=(const commune& other);
	unsigned int getCode();
	~commune();
	unsigned getPopulation(unsigned int yearP);
	void print();

	void print(unsigned int yearP);
	void addYear(year yearP);
	std::vector<year>& getYears();
	const char* getName();
	void setLevel(size_t level);
	size_t getLevel();
};

