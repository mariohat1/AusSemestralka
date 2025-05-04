#pragma once

#include <functional>
#include "commune.h"
#include "libds/amt/explicit_hierarchy.h"

class algoritmus
{
private:



public:
	using CommuneBlock = ds::amt::MultiWayExplicitHierarchyBlock<commune*>;
	template<typename Iterator>
	auto filter(Iterator begin,
		Iterator end,
		unsigned int value,
		unsigned int year,
		std::function<bool(commune&, unsigned int  value, unsigned int year)> predicate);

	template<typename Iterator>
	auto filter(Iterator begin,
		Iterator end,
		const char*,
		std::function<bool(commune&, const char*)> predicate);

	template<typename Iterator>
	auto filter(Iterator begin,
		Iterator end, 
		unsigned int level,
		std::function<bool(commune&, unsigned int level) > predicate);

};






template<typename Iterator>
auto algoritmus::filter(Iterator begin, Iterator end, unsigned int value, unsigned int year, std::function<bool(commune&, unsigned int min, unsigned int year)> predicate)
{
	std::vector<commune> result;
	for (Iterator it = begin; it != end; ++it) {
		commune& iteratorValue = **it;

		if (predicate(iteratorValue, value, year))
		{
			result.push_back(iteratorValue);
		}



	}
	return result;
}



template<typename Iterator>
auto algoritmus::filter(Iterator begin, Iterator end, const char* retazec, std::function<bool(commune& comm, const char* retazec)> predicate)
{
	std::vector<commune> result;
	int count = 0;
	for (Iterator it = begin; it != end; ++it) {
		commune& iteratorValue = **it;
		
		if (predicate(iteratorValue, retazec))
		{
			result.push_back(iteratorValue);
		}


	}
	return result;
}

template<typename Iterator>
 auto algoritmus::filter(Iterator begin, Iterator end,unsigned int level, std::function<bool(commune& node, unsigned int level)> predicate)
{
	std::vector<commune> result;
	int count = 0;
	for (Iterator it = begin; it != end; ++it) {
		commune& iteratorValue = **it;
		
		if (predicate(iteratorValue, level))
		{

			result.push_back(iteratorValue);
		}


	}
	return result;


}



