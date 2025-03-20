#pragma once
#include <iostream>
#include <Windows.h>
class commune
{
private:
	char* name = nullptr;
	unsigned int  code = 0;
	unsigned int male = 0;
	unsigned int female = 0;
	unsigned int year;
public:
	commune(const  char* name, const  unsigned int code, size_t male, size_t female, unsigned int year);
	commune(const commune& other);
	commune& operator=(const commune& other);
	unsigned int getCode();
	~commune();
	unsigned getPopulation();
	void print();
	unsigned int getYear();
	const char* getName();
	
};

