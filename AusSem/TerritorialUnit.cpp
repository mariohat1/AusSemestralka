#include "TerritorialUnit.h"

TerritorialUnit::TerritorialUnit(const  char* name, unsigned int code)
{
	size_t length = strlen(name) + 1;
	this->name = new char[length];
	strcpy_s(this->name, length, name);
	this->level = 0;
	this->code = code;
}

TerritorialUnit::TerritorialUnit(const TerritorialUnit& other)
{
	if (other.name && *other.name)
	{
		size_t length = strlen(other.name) + 1;
		name = new char[length];
		strcpy_s(name, length, other.name);
	}
	this->level = other.level;
	this->code = other.code;
	this->years = other.years;

}

TerritorialUnit& TerritorialUnit::operator=(const TerritorialUnit& other)
{
	if (this != &other)
	{
		delete[] name;
		name = nullptr;
		if (other.name && *other.name)
		{
			size_t length = strlen(other.name) + 1;
			name = new char[length];
			strcpy_s(name, length, other.name);

		}
		this->code = other.code;
		this->years = other.years;
	}
	return *this;
}

unsigned int TerritorialUnit::getCode()
{
	return this->code;
}


TerritorialUnit::~TerritorialUnit()
{
	delete[] name;
	name = nullptr;
	this->years.clear();
}

unsigned int  TerritorialUnit::getPopulation(unsigned int year)
{
	for (auto& ye : years) {
		if (ye.year == year) {
			return ye.male + ye.female;
		}
	}
	return 0;
}

void TerritorialUnit::print()
{

	std::cout << this->name << " <" << this->code << "> " << std::endl;

}

unsigned int TerritorialUnit::getPopulation(unsigned int year, unsigned int gender) const
{
	for (auto& ye : this->years)
	{
		if (ye.year == year)
		{
			switch (gender)
			{
			case 0:
				return ye.male;
			case 1:
				return ye.female;
			case 2:
				return ye.female + ye.male;
			default:
				break;
			}
		}
	}
	return 0;
}


void TerritorialUnit::print(unsigned int year)
{
	std::cout << this->name << " <" << this->code << "> ";

	for (const auto& y : years) {
		if (y.year == year) {
			std::cout << "F: " << y.female << " M: " << y.male << " Population: " << this->getPopulation(year) << std::endl;
		}
	}
}

void TerritorialUnit::addYear(Year yearP)
{
	this->years.push_back(yearP);
}

std::vector<Year>& TerritorialUnit::getYears()
{
	return this->years;
}

const char* TerritorialUnit::getName() const
{
	return this->name;
}

void TerritorialUnit::setLevel(size_t level)
{
	this->level = level;
}

size_t TerritorialUnit::getLevel()
{
	return this->level;
}

void TerritorialUnit::print(unsigned int year, unsigned int gender)
{
	for (auto& ye : this->years)
	{
		if (ye.year == year)
		{
			switch (gender)
			{
			case 0:
				std::cout << this->name << " <" << this->code << "> Year: " << ye.year << " Male: " << ye.male << std::endl;
				break;
			case 1:
				std::cout << this->name << " <" << this->code << "> Year: " << ye.year << " Female: " << ye.female << std::endl;
				break;
			case 2:
				std::cout << this->name << " <" << this->code << "> Year: " << ye.year << " Total: " << getPopulation(year) << std::endl;
				break;
			default:
				break;
			}
		}
	}

}

void TerritorialUnit::printAll()
{

	std::cout << this->name << " <" << this->code << "> " << std::endl;
	for (auto& ye : this->years)
	{
		std::cout << "Year: " << ye.year << " Male: " << ye.male << " Female: "  << ye.female << std::endl;
	}

}





