#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	this->current = this->multime.first;
}
// Theta(1)

void SortedSetIterator::first() {
	this->current = this->multime.first;
}
// Theta(1)

void SortedSetIterator::next() {
	if (this->valid()) {
        this->current = this->current->next;
    } else {
        throw std::exception();
    }
}
// Theta(1)

TElem SortedSetIterator::getCurrent()
{
	if (this->valid()) {
        return this->current->value;
    } else {
        throw std::exception();
    }
}
// Theta(1)

bool SortedSetIterator::valid() const {
    if (this->current != nullptr) {
        return true;
    }
	return false;
}
// Theta(1)
