#pragma once

#include <functional>
#include "commune.h"
class algoritmus
{
private:
	template<typename Iterator>
	bool contains(Iterator begin, Iterator end, commune& comm);

public:

	template<typename Iterator>
	auto filter(Iterator begin,
		Iterator end,
		unsigned int value,
		unsigned int year,
		std::function<bool(commune&, unsigned int  value)> predicate);

	
	

	template<typename Iterator>
	auto filter(Iterator begin,
		Iterator end,
		const char*,
		std::function<bool(commune&, const char*)> predicate);
	
};

		 




template<typename Iterator>
auto algoritmus::filter(Iterator begin, Iterator end, unsigned int value,unsigned int year, std::function<bool(commune&, unsigned int min)> predicate)
{
	std::vector<commune> result;
	for (Iterator it = begin; it != end; ++it) {
		commune& iteratorValue = *it;
		if (iteratorValue.getYear() == year)
		{
			if (predicate(iteratorValue, value))
			{
				result.push_back(iteratorValue);
			}
		}


	}
	return result;
}

template<typename Iterator>
inline bool algoritmus::contains(Iterator begin, Iterator end, commune& comm)
{
	for (Iterator i = begin; i < end; i++)
	{
		commune& iteratorValue = *i;
		if (iteratorValue.getCode() == comm.getCode())
		{
			return true;
		}
	}
	return false;
}


template<typename Iterator>
auto algoritmus::filter(Iterator begin, Iterator end, const char* retazec,std::function<bool(commune& comm, const char* retazec)> predicate)
{	
	std::vector<commune> result;
	for (Iterator it = begin; it != end; ++it) {
		commune& iteratorValue = *it;
		
			if (predicate(iteratorValue, retazec) && !contains(result.begin(), result.end(), iteratorValue))
			{
				result.push_back(iteratorValue);
			}
		
		

	}

	
	

	return result;
}



