#pragma once
#include "IndexedList.h"


class ListIterator{
    //DO NOT CHANGE THIS PART
	friend class IndexedList;
private:
	IndexedList& list;
    int current;

    explicit ListIterator(IndexedList& list);
public:
    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;

    TElem remove();
};

