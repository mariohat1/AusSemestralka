#pragma once
#include "file_reader.h"
#include "commune.h"
#include <functional>

class algorithm
{

	
public:
	
	template<typename Iterator>
	void hasMinResidentsFilter(Iterator begin, Iterator end, int min, std::function<bool( commune&,unsigned int min)> pred);
	template<typename Iterator>
	void print_results(Iterator begin, Iterator end);

};

template<typename Iterator>
void algorithm::hasMinResidentsFilter(Iterator begin, Iterator end, int min, std::function<bool(commune&, unsigned int)> pred)
{
	std::vector<commune> result;
	for (Iterator it = begin; it != end; ++it) {

		commune& comm = *it;
		if (pred(comm, min))
		{
			result.push_back(comm);
		}

	}
	print_results(result.begin(),result.end());

}

template<typename Iterator>
inline void algorithm::print_results(Iterator begin, Iterator end)
{
	for (Iterator it = begin; it != end ; it++)
	{
		commune com = *it;
		com.print();
	}
}
