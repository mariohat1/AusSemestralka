#include "commune.h"

commune::commune(const  char* name, unsigned int code)
{


	size_t length = strlen(name) + 1;
	this->name = new char[length];
	strcpy_s(this->name, length, name);
	this->level = 0;
	this->code = code;


}

commune::commune(const commune& other)
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

commune& commune::operator=(const commune& other)
{
	if (this != &other)
	{
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

unsigned int commune::getCode()
{
	return this->code;
}


commune::~commune()
{
	delete[] name;
	name = nullptr;
	this->years.clear();
	

}

unsigned int  commune::getPopulation(unsigned int year)
{
	for (auto& ye : years) {
		if (ye.year == year) {
			return ye.male + ye.female;
		}
	}
	return 0;
}

void commune::print()
{

	std::cout << this->name << " <" << this->code << "> "   << std::endl;

}

unsigned int commune::getPopulation(unsigned int year, unsigned int gender) const
{
	for  (auto& ye : this->years)
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


void commune::print(unsigned int year)
{
	std::cout << this->name << " <" << this->code << "> ";

	for (const auto& y : years) {
		if (y.year == year) {
			std::cout << "F: " << y.female<< " M: " << y.male << " Population: " << this->getPopulation(year) << std::endl;
		}
	}

	
}

void commune::addYear(year yearP)
{
	this->years.push_back(yearP);
}

std::vector<year>& commune::getYears()
{
	return this->years;
}




const char* commune::getName() const
{
	return this->name;
}

void commune::setLevel(size_t level)
{
	this->level = level;
}

size_t commune::getLevel()
{
	return this->level;
}





