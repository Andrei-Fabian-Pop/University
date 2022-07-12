#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>

FixedCapBiMap::FixedCapBiMap(int capacity) {
    if  (capacity < 0) {
        throw std::exception();
    }

    this->capacity = capacity;
    this->nrPairs = 0;
    this->elements = new TElem [capacity];
}
// time complexity = O(1)

FixedCapBiMap::~FixedCapBiMap() {
    delete[] this->elements;
}
// time complexity = O(1)

bool FixedCapBiMap::add(TKey c, TValue v){
    if (this->capacity == this->nrPairs) {
        throw std::exception();
    }

    int count = 0;
    for (int i = 0; count < 2 && i < this->nrPairs; ++i) {
        if (this->elements[i].first == c) {
            ++count;
        }
    }

    if (count == 2) {
        return false;
    } else {
        this->elements[this->nrPairs].first = c;
        this->elements[this->nrPairs++].second = v;
        return true;
    }
}
// BC = Theta(1), WC = Theta(nrPairs), AC = O(nrPairs)

ValuePair FixedCapBiMap::search(TKey c) const {
    int count = 0;
    ValuePair aux(NULL_TVALUE, NULL_TVALUE);
    for (int i = 0; count < 2 && i < this->nrPairs; ++i) {
        if (this->elements[i].first == c) {
            if (count == 0) {
                aux.first = this->elements[i].second;
            } else {
                aux.second = this->elements[i].second;
            }
            ++count;
        }
    }

    return aux;
}
// BC = Theta(1), WC = Theta(nrPairs), AC = O(nrPairs)

bool FixedCapBiMap::remove(TKey c, TValue v){
    bool found = false;
    for (int i = 0; i < this->nrPairs && !found; ++i) {
        if (this->elements[i].first == c && this->elements[i].second == v) {
            found = true;
            this->elements[i] = this->elements[this->nrPairs-1];
            --this->nrPairs;
        }
    }

	return found;
}
// BC = Theta(1), WC = Theta(nrPairs), AC = O(nrPairs)


int FixedCapBiMap::size() const {
	return this->nrPairs;
}
// time complexity = O(1)

bool FixedCapBiMap::isEmpty() const {
	return (bool)(this->nrPairs == 0);
}
// time complexity = O(1)

bool FixedCapBiMap::isFull() const {
	return (bool)(this->nrPairs == this->capacity);
}
// time complexity = O(1)

FixedCapBiMapIterator FixedCapBiMap::iterator() const {
	return FixedCapBiMapIterator(*this);
}
// time complexity = O(1)

// at the lab
ValuePair FixedCapBiMap::removeKey(TKey k) {
    int count = 0;
    ValuePair aux(NULL_TVALUE, NULL_TVALUE);
    for (int i = 0; count < 2 && i < this->nrPairs; ++i) {
        if (this->elements[i].first == k) {
            if (count == 0) {
                aux.first = this->elements[i].second;
            } else {
                aux.second = this->elements[i].second;
            }
            this->elements[i] = this->elements[this->nrPairs-1];
            --this->nrPairs;
            ++count;
            --i;
        }
    }

    return aux;
}
