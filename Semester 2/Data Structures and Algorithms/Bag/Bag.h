#pragma once
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111;
typedef int TElem;
class BagIterator;

struct Node {
    TElem unique_element = NULL_TELEM;
    int frequency = 0;
    Node *next = nullptr;
    Node *prev = nullptr;
};

class Bag {
private:
    Node** elements;
    int _size;
    int capacity;
    const float loadFactor;

    int hash(int key) const;

    void resize();

	//DO NOT CHANGE THIS PART
	friend class BagIterator;

public:
	//constructor
	explicit Bag(int capacity=100);

	//adds an element to the bag
	void add(TElem e);

	//removes one occurrence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appears is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	//destructor
	~Bag();
};