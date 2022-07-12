#include "Bag.h"

class BagIterator
{
	//DO NOT CHANGE THIS PART
	friend class Bag;
	
private:
	const Bag& bag;
    int pos;
    int frequency;
    Node* current;

	explicit BagIterator(const Bag& c);
public:
	void first();
	void next();
    void prev();
    TElem getCurrent() const;
	bool valid() const;
};
