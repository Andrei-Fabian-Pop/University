#include "ListIterator.h"
#include "IndexedList.h"
#include <exception>

ListIterator::ListIterator(IndexedList& list) : list(list){
    this->current = this->list.head;
}
// Theta(1)

void ListIterator::first(){
    this->current = this->list.head;
}
// Theta(1)

void ListIterator::next(){
    if (valid()) {
        current = this->list.next[current];
    } else {
        throw std::exception();
    }
}
// Theta(1)

bool ListIterator::valid() const {
	return (this->current != -1);
}
// Theta(1)

TElem ListIterator::getCurrent() const{
    if (valid()) {
        return this->list.elems[this->current];
    } else {
        throw std::exception();
    }
}

TElem ListIterator::remove() {
    if (valid()) {
        int toRemove = current;
        this->next();
        TElem elem = this->list.remove(toRemove);
        return elem;
    } else {
        throw std::exception();
    }
}
// Theta(pos)
