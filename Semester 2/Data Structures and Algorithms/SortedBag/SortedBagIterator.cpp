#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	this->first();
}

TComp SortedBagIterator::getCurrent() {
    if (!this->valid()) {
        throw std::exception();
    }
	return this->lst.top()->info;
}

bool SortedBagIterator::valid() {
	return (this->bag.root != nullptr && !this->lst.empty());
}

void SortedBagIterator::next() {
	if (this->valid()) {
        Node* current = this->lst.top()->right;
        this->lst.pop();
        while (current != nullptr) {
            this->lst.push(current);
            current = current->left;
        }
    } else {
        throw std::exception();
    }
}

void SortedBagIterator::first() {
    while (!this->lst.empty()) {
        this->lst.pop();
    }
    Node* current = this->bag.root;
    while (current != nullptr) {
        this->lst.push(current);
        current = current->left;
    }
}
