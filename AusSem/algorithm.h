#pragma once

#include <functional>
template<typename T>
class algorithm
{


public:

	template<typename Iterator>
	auto filter(Iterator begin,
		Iterator end,
		int min,
		std::function<bool(T&, unsigned int min)> pred);

	template<typename Iterator>
	auto filter(Iterator begin,
		Iterator end,
		const char* retazec,
		std::function<bool(T&, const char*)> pred = [](commune& comm, const char* retazec) -> bool {
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
		 




template<typename T>
template<typename Iterator>
auto algorithm<T>::filter(Iterator begin, Iterator end, int min, std::function<bool(T&, unsigned int min)> pred)
{
	std::vector<T> result;
	for (Iterator it = begin; it != end; ++it) {

		T& iteratorValue = *it;
		if (pred(iteratorValue, min))
		{
			result.push_back(iteratorValue);
		}

	}
	return result;
}

template<typename T>
template<typename Iterator>
auto algorithm<T>::filter(Iterator begin, Iterator end, const char* retazec, std::function<bool(T& comm, const char* retazec)> pred)
{
	std::vector<T> result;
	for (Iterator it = begin; it != end; ++it) {

		T& iteratorValue = *it;
		if (pred(iteratorValue, retazec))
		{
			result.push_back(iteratorValue);
		}

	}
	return result;
}




