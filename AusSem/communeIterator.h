#pragma once
#include "libds/amt/explicit_hierarchy.h"
#include "commune.h"
class communeIterator
{

public:
	using CommuneBlock = ds::amt::MultiWayExplicitHierarchyBlock<commune*>;
	using iterator = ds::amt::MultiWayExplicitHierarchy<commune*>::PreOrderHierarchyIterator;
	void hierarchyIterator(iterator currentIteratorCopy, iterator end);
}; 

