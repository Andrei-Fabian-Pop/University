#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {
    this->relation = r;
    this->first = nullptr;
    this->last = nullptr;
    this->_size = 0;
}
// Theta(1)

bool SortedSet::add(TComp elem) {
    // add the first element
    if (this->first == nullptr) {
        this->first = new DLL;
        this->first->value = elem;
        ++this->_size;
        return true;
    }
    // add the second element in order
    if (this->last == nullptr && this->first->value != elem) {
        this->last = new DLL;
        if (this->relation(this->first->value, elem)) {
            this->last->value = elem;
            this->last->prev = this->first;
        } else {
            this->last->value = this->first->value;
            this->first->value = elem;
        }
        this->first->next = this->last;
        this->last->prev = this->first;
        ++this->_size;
        return true;
    }

    // search for the right position
    DLL * current = this->first;
    while (current != nullptr && this->relation(current->value, elem)) {
        if (current->value == elem) {
            return false;
        }
        current = current->next;
    }

    // add to last position
    if (current == nullptr) {
        current = new DLL;
        current->value = elem;
        current->prev = this->last;
        this->last->next = current;
        this->last = current;
    } else if (current->prev == nullptr) { // add to first position
        current->prev = new DLL;
        current->prev->value = elem;
        current->prev->next = current;
        this->first = current->prev;
    } else { // add to found position
        DLL * new_DLL = new DLL;
        new_DLL->prev = current->prev;
        new_DLL->next = current;
        new_DLL->value = elem;

        current->prev->next = new_DLL;
        current->prev = new_DLL;
    }
    ++this->_size;
    return true;
}
// BC=Theta(1), WC=size, AC=size, OC=O(size)

bool SortedSet::remove(TComp elem) {
    DLL * current = this->first;
    while (current != nullptr) {
        if (current->value == elem) {
            // delete current
            if (this->_size == 1) {
                delete current;
                this->first = nullptr;
                this->last = nullptr;
            } else if (current->prev == nullptr) {
                // delete the first element from the set
                DLL * aux = this->first;
                this->first = this->first->next;
                this->first->prev = nullptr;
                delete aux;
            } else if (current->next == nullptr) {
                // delete last element
                DLL * aux = this->last;
                this->last = this->last->prev;
                this->last->next = nullptr;
                delete aux;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
            }
            --this->_size;
            return true;
        }
        current = current->next;
    }
	return false;
}
// BC=1, WC=size, AC=size, OC=O(size)

bool SortedSet::search(TComp elem) const {
	DLL * current = this->first;
    while (current != nullptr) {
        if (current->value == elem) {
            return true;
        }
        current = current->next;
    }
	return false;
}
// BC=1, WC=size, AC=size, OC=O(size)

int SortedSet::size() const {
	return this->_size;
}
// Theta(1)

bool SortedSet::isEmpty() const {
	return (this->first == nullptr);
}
// Theta(1)

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}
// Theta(1)

SortedSet::~SortedSet() {
    DLL *current = this->first;
    while (current != nullptr) {
        DLL *aux = current;
        current = current->next;
        delete aux;
    }
}
// O(size)

void SortedSet::filter(Condition cond) {
    DLL *current = this->first;
    while (current != nullptr) {
        if (!cond(current->value)) {
            DLL *next = current->next;

            if (this->_size == 1) {
                delete current;
                this->first = nullptr;
                this->last = nullptr;
            } else if (current->prev == nullptr) {
                // delete the first element from the set
                DLL * aux = this->first;
                this->first = this->first->next;
                this->first->prev = nullptr;
                delete aux;
            } else if (current->next == nullptr) {
                // delete last element
                DLL * aux = this->last;
                this->last = this->last->prev;
                this->last->next = nullptr;
                delete aux;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
            }
            --this->_size;

            current = next;
        } else {
            current = current->next;
        }
    }
}
// Theta (size)
