#include "Set.h"
#include "SetIterator.h"

Set::Set() {
    this->_size = 0;
    this->elements = new TElem [this->_size];
}
// Theta(1)

bool Set::add(TElem elem) {
    auto aux = new TElem [this->_size+1];
    for (int i = 0; i < this->_size; ++i) {
        if (this->elements[i] == elem) {
            delete[] aux;
            return false;
        }
        aux[i] = this->elements[i];
    }
    aux[this->_size] = elem;
    ++this->_size;
    delete[] this->elements;
    this->elements = aux;

	return true;
}
// BC=1, WC=size, AC=size, OC=O(size)

bool Set::remove(TElem elem) {
    if (this->_size == 0) {
        return false;
    }
    auto aux = new TElem [this->_size-1];
    bool found = false;
    for (int i = 0; i < this->_size - 1; ++i) {
        if (this->elements[i] == elem) {
            found = true;
        }
        if (!found) {
            aux[i] = this->elements[i];
        } else {
            aux[i] = this->elements[i+1];
        }
    }
    if (this->elements[this->_size-1] == elem) {
        found = true;
    }

    if (!found) {
        delete[] aux;
        return false;
    } else {
        delete[] this->elements;
        this->elements = aux;
        --this->_size;

        return true;
    }

}
// Theta(size)

bool Set::search(TElem elem) const {
	for (int i = 0; i < this->_size; ++i) {
        if (this->elements[i] == elem) {
            return true;
        }
    }

	return false;
}
// Theta(size)

int Set::size() const {
	return this->_size;
}
// Theta(0)

bool Set::isEmpty() const {
	return (bool)(this->_size == 0);
}
// Theta(0)

Set::~Set() {
	delete[] this->elements;
}
// Theta(0)

SetIterator Set::iterator() const {
	return SetIterator(*this);
}
// Theta(0)

