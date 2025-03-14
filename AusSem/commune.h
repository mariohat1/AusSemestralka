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
	commune(const  char* name, const  char* code, size_t male, size_t female);
	commune(const commune& other);
	commune& operator=(const commune& other);
	~commune();
	unsigned getPopulation();
	void print();
	
	const char* getName();
	
};

