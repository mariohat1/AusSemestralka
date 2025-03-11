#pragma once
#include <iostream>
#include <Windows.h>
class commune
{
private:
	char* name = nullptr;
	char* code = nullptr;
	size_t male = 0;
	size_t female = 0;
public:
	commune(const  char* name, const  char* code, size_t male, size_t female);
	commune(const commune& other);
	commune& operator=(const commune& other);
	~commune();
	size_t getPopulation();
	void print();
	
	const char* getName();
	
};

