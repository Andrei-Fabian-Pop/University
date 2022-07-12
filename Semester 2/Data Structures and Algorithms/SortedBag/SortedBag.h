#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR

//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
typedef bool(*Condition)(TComp);
#define NULL_TCOMP (-11111)

class SortedBagIterator;

struct Node {
    TElem info = NULL_TCOMP;
    struct Node* left = nullptr;
    struct Node* right = nullptr;
};

class SortedBag {
	friend class SortedBagIterator;

private:
    Node* root;
    Relation relation;
    int _size;

    void deleteTree(struct Node* node);
public:
	//constructor
	explicit SortedBag(Relation r);

	//adds an element to the sorted bag
	void add(TComp e);

	//removes one occurrence of an element from a sorted bag
	//returns true if an element was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	//checks if an element appears is the sorted bag
	bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() const;

	//checks if the sorted bag is empty
	bool isEmpty() const;

	//destructor
	~SortedBag();

    // extra operation
    void filter(Condition cond);
};