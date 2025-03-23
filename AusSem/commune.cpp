#include "commune.h"

commune::commune(const  char* name, unsigned int code, size_t male, size_t female, unsigned int year)
{
	this->male = male;
	this->female = female;
	this->year = year;

	size_t length = strlen(name) + 1;
	this->name = new char[length];
	strcpy_s(this->name, length, name);

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

	this->code = other.code;

	this->male = other.male;
	this->female = other.female;
	this->year = other.year;


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
		this->female = other.female;
		this->male = other.male;
		this->year = other.year;
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
	

}

unsigned commune::getPopulation()
{
	return this->male + this->female;
}

void commune::print()
{

	std::cout << this->name << " <" << this->code << "> F: " << this->female << " M: " << this->male << " " << std::endl;

}

unsigned int commune::getYear()
{
	return this->year;
}



const char* commune::getName()
{
	return this->name;
}





