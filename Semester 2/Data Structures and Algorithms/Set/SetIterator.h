#pragma once
#include "Set.h"
#include <exception>

class SetIterator
{
	//DO NOT CHANGE THIS PART
	friend class Set;
private:
	//DO NOT CHANGE THIS PART
	const Set& set;
	explicit SetIterator(const Set& s);

    int index;

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
    void jumpForward(int k);
};


