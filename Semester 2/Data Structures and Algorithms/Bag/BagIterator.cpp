#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag &c) : bag(c) {
    this->current = nullptr;
    this->pos = 0;
    this->frequency = -1;
    this->first();
}
// BC=Theta(1), WC=Theta(capacity), AC=O(capacity)

void BagIterator::first() {
    if (this->bag.isEmpty()) return;
    int i = 0;
    while (this->bag.elements[i] == nullptr) { ++i; }

    this->pos = i;
    this->frequency = this->bag.elements[i]->frequency;
    this->current = this->bag.elements[i];
}
// BC=Theta(1), WC=Theta(capacity), AC=O(capacity)

void BagIterator::next() {
    if (this->bag.isEmpty() || this->current == nullptr) {
        throw std::exception();
    }
    if (this->frequency > 1) {
        --this->frequency;
    } else if (this->current->next != nullptr) {
        this->current = this->current->next;
        this->frequency = this->current->frequency;
    } else {
        int i = pos + 1;
        while (this->bag.elements[i] == nullptr && i < this->bag.capacity) { ++i; }
        if (i >= this->bag.capacity) {
            this->current = nullptr;
        } else {
            this->pos = i;
            this->frequency = this->bag.elements[i]->frequency;
            this->current = this->bag.elements[i];
        }
    }
}
// BC=Theta(1), WC=Theta(capacity), AC=O(capacity)

bool BagIterator::valid() const {
    return (this->current != nullptr);
}
// O(1)

TElem BagIterator::getCurrent() const {
    if (this->valid()) {
        return this->current->unique_element;
    } else {
        throw std::exception();
    }
}
// O(1)

void BagIterator::prev() {
    if (this->bag.isEmpty() || this->current == nullptr) {
        throw std::exception();
    }
    if (this->frequency < this->current->frequency) {
        ++this->frequency;
    } else if (this->current->prev != nullptr) {
        this->current = this->current->prev;
        this->frequency = this->current->frequency;
    } else {
        int i = pos - 1;
        while (this->bag.elements[i] == nullptr && i >= 0) { --i; }
        if (i < 0) {
            this->current = nullptr;
        } else {
            this->pos = i;
            this->frequency = this->bag.elements[i]->frequency;
            this->current = this->bag.elements[i];
        }
    }
}
// BC=Theta(1), WC=Theta(capacity), AC=O(capacity)
