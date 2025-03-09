#pragma once
#include "file_reader.h"
#include "commune.h"
#include <functional>

class algorithm
{


public:

	template<typename Iterator>
	void filter(Iterator begin,
		Iterator end,
		int min,
		std::function<bool(commune&, unsigned int min)> pred = [](commune& comm, unsigned int min) -> bool {
			return comm.getPopulation() >= min;
		});

	template<typename Iterator>
	void print_results(Iterator begin, Iterator end);

	template<typename Iterator>
	void filter(Iterator begin,
		Iterator end,
		const char* retazec,
		std::function<bool(commune&, const char*)> pred = [](commune& comm, const char* retazec) -> bool {
			const char* name = comm.getName();
			size_t name_len = strlen(name);
			size_t retazec_len = strlen(retazec);
			bool found = true;
			if (retazec_len > name_len)
			{
				return false;
			}

			for (size_t i = 0; i < name_len; i++)
			{
				found = true;
				for (size_t j = 0; j < retazec_len; j++)
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
void algorithm::filter(Iterator begin, Iterator end, int min, std::function<bool(commune&, unsigned int)> pred)
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

template<typename Iterator>
inline void algorithm::filter(Iterator begin, Iterator end, const char* retazec, std::function<bool(commune& comm, const char* retazec)> pred)
{
	std::vector<commune> result;
	for (Iterator it = begin; it != end; ++it) {

		commune& comm = *it;
		if (pred(comm, retazec))
		{
			result.push_back(comm);
		}

	}
	print_results(result.begin(), result.end());
}




