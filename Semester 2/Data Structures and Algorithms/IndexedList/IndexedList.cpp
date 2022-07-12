#include "IndexedList.h"
#include "ListIterator.h"
#include <exception>

IndexedList::IndexedList() {
    this->capacity = 16;
    this->_size = 0;
    this->elems = new TElem[this->capacity];
    this->next = new int[this->capacity];
    for (int i = 0; i < this->capacity; ++i)
        this->next[i] = i + 1;

    this->head = -1;
    this->firstFree = 0;
    this->lastIndex = -1;
}
// Theta(capacity)

int IndexedList::size() const {
    return this->_size;
}
// Theta(1)

bool IndexedList::isEmpty() const {
    return (this->_size == 0);
}
// Theta(1)

TElem IndexedList::getElement(int pos) const {
    if (pos < 0 || pos >= this->_size) {
        throw std::exception();
    } else {
        TElem elem;
        int current = this->head;
        for (int i = 0; i <= pos; ++i) {
            elem = this->elems[current];
            current = this->next[current];
        }
        return elem;
    }
}
// O(pos)

TElem IndexedList::setElement(int pos, TElem e) {
    if (pos < 0 || pos >= this->_size) {
        throw std::exception();
    } else {
        TElem elem;
        int current = this->head;
        int prev;
        for (int i = 0; i <= pos; ++i) {
            elem = this->elems[current];
            prev = current;
            current = this->next[current];
        }
        this->elems[prev] = e;
        return elem;
    }
}
// O(pos)

void IndexedList::doubleTheCapacity() {
    // double the capacity
    auto newElems = new TElem[this->capacity * 2];
    auto newNext = new int[this->capacity * 2];

    for (int i = 0; i < this->capacity; ++i) {
        newElems[i] = this->elems[i];
        newNext[i] = this->next[i];
    }
    for (int i = this->capacity; i < this->capacity * 2; ++i) {
        newNext[i] = i + 1;
    }

    this->capacity *= 2;

    delete[] this->elems;
    delete[] this->next;

    this->elems = newElems;
    this->next = newNext;
}
// O(capacity*2)

void IndexedList::addToEnd(TElem e) {
    if (this->_size + 1 >= this->capacity) {
        this->doubleTheCapacity();
    }
    if (this->head == -1) {
        this->head = 0;
        this->elems[0] = e;
        this->next[0] = -1;
        this->firstFree = 1;
        this->lastIndex = 0;
    } else {
        this->elems[this->firstFree] = e;

        int aux = this->firstFree;
        this->firstFree = this->next[this->firstFree];
        this->next[aux] = this->next[this->lastIndex];
        this->next[this->lastIndex] = aux;
        this->lastIndex = aux;
    }

    ++this->_size;
}
// O(1)

void IndexedList::addToPosition(int pos, TElem e) {
    if (pos < 0 || pos > this->_size) {
        throw std::exception();
    }
    if (this->_size + 1 >= this->capacity) {
        this->doubleTheCapacity();
    }

    int current = this->head;
    int prev = -1;
    for (int i = 0; i < pos; ++i) {
        prev = current;
        current = this->next[current];
    }

    if (pos == 0) {
        // add on the first pos
        if (this->head == -1) {
            this->head = 0;
            this->elems[0] = e;
            this->next[0] = -1;
            this->firstFree = 1;
            this->lastIndex = 0;
        } else {
            this->elems[this->firstFree] = e;
            this->head = this->firstFree;
            int aux = next[firstFree];
            next[firstFree] = current;
            firstFree = aux;
        }
    } else if (pos == _size) {
        // add to the last pos
        this->elems[this->firstFree] = e;

        int aux = this->firstFree;
        this->firstFree = this->next[this->firstFree];
        this->next[aux] = this->next[this->lastIndex];
        this->next[this->lastIndex] = aux;
        this->lastIndex = aux;
    } else {
        this->elems[this->firstFree] = e;

        int aux = next[firstFree];
        next[prev] = firstFree;
        next[firstFree] = current;
        firstFree = aux;
    }

    ++this->_size;
}
// BC=Theta(pos), WC=pos, AC=pos, OC=Theta(pos)

TElem IndexedList::remove(int pos) {
    if (pos < 0 || pos >= this->_size) {
        throw std::exception();
    } else {
        int current = this->head;
        int prev = -1;
        for (int i = 0; i < pos; ++i) {
            prev = current;
            current = this->next[current];
        }
        TElem elem = this->elems[current];

        if (current == this->head) {
            // if delete first
            this->head = this->next[head];
        } else {
            if (this->next[current] == -1) {
                // if delete last
                this->lastIndex = prev;
            }
            this->next[prev] = this->next[current];
        }

        next[current] = firstFree;
        firstFree = current;
        --this->_size;

        return elem;
    }
}
// BC=Theta(1), WC=pos, AC=pos, OC=O(pos)

int IndexedList::search(TElem e) const {
    int current = this->head;
    for (int index = 0; current != -1; ++index) {
        if (this->elems[current] == e) {
            return index;
        }
        current = this->next[current];
    }

    return -1;
}
// BC=Theta(1), WC=size, AC=size, OC=O(size)

ListIterator IndexedList::iterator() {
    return ListIterator(*this);
}
// Theta(1)

IndexedList::~IndexedList() {
    delete[] this->elems;
    delete[] this->next;
}
// Theta(1)
