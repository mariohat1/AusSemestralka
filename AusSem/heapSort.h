#pragma once
#include <vector>
#include <functional>
#include <algorithm>
class heapSort {
public:
	template<typename T>
	void sort(std::vector<T>& data, std::function<bool(const T&, const T&)> compare);



};

template<typename T>
inline void heapSort::sort(std::vector<T>& data, std::function<bool(const T&, const T&)> compare)
{
	for (size_t i = 1; i < data.size() - 1; i++)
	{
		bool swap = false;
		size_t current = i;
		do
		{
			swap = false;
			size_t parent = (current - 1) / 2;
			if (current > 0 && compare(data[parent], data[current]))
			{
				std::swap(data[current], data[parent]);
				current = parent;
				swap = true;

			}


		} while (swap);
	}
	for (size_t i = data.size() - 1; i > 0; i--)
	{
		std::swap(data[0], data[i]);
		size_t current = 0;
		bool swap = false;
		do
		{
			swap = false;
			size_t left = 2 * current + 1;
			size_t right = 2 * current + 2;
			size_t max;
			if (left < i && right < i)
			{
				max = compare(data[right], data[left]) ? left : right;
			}
			else {
				max = left < i ? left : right;
			}
			if (max < i && compare(data[current], data[max]))
			{
				std::swap(data[current], data[max]);
				current = max;
				swap = true;
			}


		} while (swap);




	}
}
