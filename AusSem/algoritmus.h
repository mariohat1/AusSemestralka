#pragma once

#include <functional>
#include "TerritorialUnit.h"
#include "libds/amt/explicit_hierarchy.h"

class algoritmus
{
private:



public:
	using CommuneBlock = ds::amt::MultiWayExplicitHierarchyBlock<TerritorialUnit*>;
	template<typename Iterator>
	auto filter(Iterator begin,
		Iterator end,
		unsigned int value,
		unsigned int year,
		std::function<bool(TerritorialUnit&, unsigned int  value, unsigned int year)> predicate);

	template<typename Iterator>
	auto filter(Iterator begin,
		Iterator end,
		const char*,
		std::function<bool(TerritorialUnit&, const char*)> predicate);

	template<typename Iterator>
	auto filter(Iterator begin,
		Iterator end, 
		unsigned int level,
		std::function<bool(TerritorialUnit&, unsigned int level) > predicate);

};






template<typename Iterator>
auto algoritmus::filter(Iterator begin, Iterator end, unsigned int value, unsigned int year, std::function<bool(TerritorialUnit&, unsigned int min, unsigned int year)> predicate)
{
	std::vector<TerritorialUnit> result;
	for (Iterator it = begin; it != end; ++it) {
		TerritorialUnit& iteratorValue = **it;

		if (predicate(iteratorValue, value, year))
		{
			result.push_back(iteratorValue);
		}



	}
	return result;
}



template<typename Iterator>
auto algoritmus::filter(Iterator begin, Iterator end, const char* retazec, std::function<bool(TerritorialUnit& comm, const char* retazec)> predicate)
{
	std::vector<TerritorialUnit> result;
	int count = 0;
	for (Iterator it = begin; it != end; ++it) {
		TerritorialUnit& iteratorValue = **it;
		
		if (predicate(iteratorValue, retazec))
		{
			result.push_back(iteratorValue);
		}


	}
	return result;
}

template<typename Iterator>
 auto algoritmus::filter(Iterator begin, Iterator end,unsigned int level, std::function<bool(TerritorialUnit& node, unsigned int level)> predicate)
{
	std::vector<TerritorialUnit> result;
	int count = 0;
	for (Iterator it = begin; it != end; ++it) {
		TerritorialUnit& iteratorValue = **it;
		
		if (predicate(iteratorValue, level))
		{

			result.push_back(iteratorValue);
		}


	}
	return result;


}



