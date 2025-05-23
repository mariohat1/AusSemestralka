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
		std::function<bool(TerritorialUnit&)> predicate);



};

template<typename Iterator>
inline auto algoritmus::filter(Iterator begin, Iterator end, std::function<bool(TerritorialUnit&)> predicate)
{
	std::vector<TerritorialUnit> result;
	int count = 0;
	for (Iterator it = begin; it != end; ++it) {
		TerritorialUnit& iteratorValue = **it;

		if (predicate(iteratorValue))
		{
			result.push_back(iteratorValue);
		}


	}
	return result;


}
