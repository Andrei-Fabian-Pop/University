#pragma once
#include "SortedBag.h"
#include <stack>

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	explicit SortedBagIterator(const SortedBag& b);

	std::stack<Node*> lst;

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

