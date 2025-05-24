#pragma once
#include <functional>
#include "TerritorialUnit.h"

class Algoritmus
{
private:
public:
	template<typename Iterator>
	auto filter(Iterator begin,
		Iterator end,
		std::function<bool(TerritorialUnit&)> predicate);
};

template<typename Iterator>
inline auto Algoritmus::filter(Iterator begin, Iterator end, std::function<bool(TerritorialUnit&)> predicate)
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
