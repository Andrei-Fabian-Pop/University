#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& multime;
	explicit SortedSetIterator(const SortedSet& m);

    DLL * current;

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};

