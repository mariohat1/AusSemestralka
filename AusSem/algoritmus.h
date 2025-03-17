#pragma once

#include <functional>
#include "commune.h"
class algoritmus
{


public:

	template<typename Iterator>
	auto filter(Iterator begin,
		Iterator end,
		unsigned int min,
		std::function<bool(commune&, unsigned int  min)> pred);

	template<typename Iterator>
	auto filter(Iterator begin,
		Iterator end,
		const char* retazec,
		unsigned int year,
		std::function<bool(commune&, const char*)> pred = [](commune& comm, const char* retazec) -> bool {
			const char* name = comm.getName();
			size_t nameLen = strlen(name);
			size_t retazecLen = strlen(retazec);
			bool found = true;
			if (retazecLen > nameLen)
			{
				return false;
			}

			for (size_t i = 0; i < nameLen; i++)
			{
				found = true;
				for (size_t j = 0; j < retazecLen; j++)
				{
					if (name[i + j] != retazec[j])
					{
						found = false;
					}
				}
				if (found) {
					break;
				}

			}
			return found;



		});
	
};

		 




template<typename Iterator>
auto algoritmus::filter(Iterator begin, Iterator end, unsigned int value, std::function<bool(commune&, unsigned int min)> pred)
{
	std::vector<commune> result;
	for (Iterator it = begin; it != end; ++it) {

		commune& iteratorValue = *it;
		if (pred(iteratorValue, value))
		{
			result.push_back(iteratorValue);
		}

	}
	return result;
}


template<typename Iterator>
auto algoritmus::filter(Iterator begin, Iterator end, const char* retazec,unsigned int year, std::function<bool(commune& comm, const char* retazec)> pred)
{	
	std::vector<commune> result;
	for (Iterator it = begin; it != end; ++it) {
		commune& iteratorValue = *it;
		if (iteratorValue.getYear() == year)
		{
			if (pred(iteratorValue, retazec))
			{
				result.push_back(iteratorValue);
			}
		}
		

	}

	
	

	return result;
}



