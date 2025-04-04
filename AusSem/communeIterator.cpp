#include "communeIterator.h"

void communeIterator::hierarchyIterator(iterator currentIteratorCopy, iterator end)
{
	while (currentIteratorCopy != end) {
		commune* it = *currentIteratorCopy;
		std::cout << it->getName() << std::endl;
		++currentIteratorCopy;
	
	}

	
}
