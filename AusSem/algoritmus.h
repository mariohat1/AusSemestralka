#pragma once

#include <functional>
#include "commune.h"
class algoritmus
{
private:
	
	

public:

	template<typename Iterator>
	auto filter(Iterator begin,
		Iterator end,
		unsigned int value,
		unsigned int year,
		std::function<bool(commune*, unsigned int  value, unsigned int year)> predicate);

	
	

	template<typename Iterator>
	auto filter(Iterator begin,
		Iterator end,
		const char*,
		std::function<bool(commune&, const char*)> predicate);
	
};

		 




template<typename Iterator>
auto algoritmus::filter(Iterator begin, Iterator end, unsigned int value,unsigned int year, std::function<bool(commune*, unsigned int min, unsigned int year)> predicate)
{
	std::vector<commune> result;
	for (Iterator it = begin; it != end; ++it) {
		commune& iteratorValue = *it;
		
			if (predicate(iteratorValue, value, year))
			{
				result.push_back(iteratorValue);
			}
		


	}
	return result;
}



template<typename Iterator>
auto algoritmus::filter(Iterator begin, Iterator end, const char* retazec,std::function<bool(commune& comm, const char* retazec)> predicate)
{	
	std::vector<commune> result;
	int count = 0;
	for (Iterator it = begin; it != end; ++it) {
		commune& iteratorValue = **it;
		std::cout << iteratorValue.getPopulation(2020) << std::endl;
		

			if (predicate(iteratorValue, retazec))
			{
				result.push_back(iteratorValue);
			}
		

	}
	return result;
}



