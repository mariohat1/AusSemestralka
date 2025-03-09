#pragma once
#include <iostream>
#include <Windows.h>
class commune
{
private:
	char* name = nullptr;
	char* code = nullptr;
	unsigned int male = 0;
	unsigned int female = 0;
public:
	commune(const  char* name, const  char* code, unsigned int male, unsigned int female);
	commune(const commune& other);
	commune& operator=(const commune& other);
	~commune();
	unsigned int getPopulation();
	void print();
	std::string convert_utf8(const char* name);
	
};

