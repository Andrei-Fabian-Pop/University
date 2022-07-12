#include "SetIterator.h"
#include "Set.h"


SetIterator::SetIterator(const Set& m) : set(m)
{
	this->index = 0;
}
// Theta(1)

void SetIterator::first() {
	this->index = 0;
}
// Theta(1)

void SetIterator::next() {
	if (this->valid()) {
        ++this->index;
    } else {
        throw std::exception();
    }
}
// Theta(1)

TElem SetIterator::getCurrent()
{
    if (this->valid()) {
        return this->set.elements[index];
    } else {
        throw std::exception();
    }
}
// Theta(1)

bool SetIterator::valid() const {
    if (this->index >= 0 && this->index < this->set._size && !set.isEmpty()) {
        return true;
    }
	return false;
}

void SetIterator::jumpForward(int k) {
    if (valid() && this->index+k >= this->set.size()) {
        throw std::exception();
    } else {
        this->index = this->index + k;
    }
}
// Theta(1)
