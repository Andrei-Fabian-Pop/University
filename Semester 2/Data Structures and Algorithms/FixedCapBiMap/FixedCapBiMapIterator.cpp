#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>


FixedCapBiMapIterator::FixedCapBiMapIterator(const FixedCapBiMap& d) : map(d)
{
    this->current = 0;
}
// Theta(1)

void FixedCapBiMapIterator::first() {
    this->current = 0;
}
// Theta(0)

void FixedCapBiMapIterator::next() {
    if (this->valid()) {
        ++this->current;
    } else {
        throw std::exception();
    }
}
// Theta(0)

TElem FixedCapBiMapIterator::getCurrent(){
    if (this->valid()) {
        return this->map.elements[this->current];
    } else {
        throw std::exception();
    }
}
// Theta(0)

bool FixedCapBiMapIterator::valid() const {
	if (this->current >= 0 && this->current < this->map.nrPairs) {
        return true;
    } else {
        return false;
    }
}
// Theta(0)
