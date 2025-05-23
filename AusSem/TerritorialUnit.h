#pragma once
#include <iostream>
#include "year.h"
#include <vector>

class TerritorialUnit
{
private:
	char* name = nullptr;
	unsigned int  code = 0;
	std::vector<year> years;
	size_t level = 0;
	
public:
	TerritorialUnit(const  char* name, const  unsigned int code);
	TerritorialUnit(const TerritorialUnit& other);
	TerritorialUnit& operator=(const TerritorialUnit& other);
	unsigned int getCode();
	~TerritorialUnit();
	unsigned getPopulation(unsigned int yearP);
	void print();
	unsigned int getPopulation(unsigned int year, unsigned int gender) const;

	void print(unsigned int yearP);
	void addYear(year yearP);
	std::vector<year>& getYears();
	
	const char* getName() const;
	void setLevel(size_t level);
	size_t getLevel();
};

