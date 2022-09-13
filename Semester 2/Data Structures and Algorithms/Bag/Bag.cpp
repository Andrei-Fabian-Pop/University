#include "Bag.h"
#include "BagIterator.h"
#include <exception>

using namespace std;


Bag::Bag(int capacity) : loadFactor(0.75) {
    this->capacity = capacity;
    this->_size = 0;
    this->elements = new Node *[this->capacity];
    for (int i = 0; i < this->capacity; ++i) {
        this->elements[i] = nullptr;
    }
}
// O(capacity)

void Bag::add(TElem elem) {
    if ((float)(this->_size) / (float)(this->capacity) >= this->loadFactor) {
        this->resize();
    }

    // first element
    int pos = hash(elem);
    if (this->elements[pos] == nullptr) {
        this->elements[pos] = new Node;
        this->elements[pos]->unique_element = elem;
        this->elements[pos]->frequency = 1;
        this->elements[pos]->next = nullptr;
        this->elements[pos]->prev = nullptr;
        ++this->_size;
        return;
    }

    // other elements
    Node *current = this->elements[pos];
    Node *prev;
    while (current != nullptr) {
        if (current->unique_element == elem) {
            ++current->frequency;
            ++this->_size;
            return;
        }
        prev = current;
        current = current->next;
    }
    current = new Node;
    prev->next = current;
    current->next = nullptr;
    current->prev = prev;
    current->frequency = 1;
    current->unique_element = elem;
    ++this->_size;
}
// BC=Theta(1), WC=Theta(length of collision chaining), AC=O(length of collision chaining)

bool Bag::remove(TElem elem) {
    int pos = hash(elem);
    if (this->elements[pos] == nullptr)
        return false;

    Node *current = this->elements[pos];
    Node *prev;
    while (current != nullptr) {
        if (current->unique_element == elem) {
            if (current->frequency > 1) {
                --current->frequency;
                --this->_size;
                return true;
            } else {
                if (current == this->elements[pos]) {
                    this->elements[pos] = current->next;
                    if (this->elements[pos] != nullptr) {
                        this->elements[pos]->prev = nullptr;
                    }
                } else {
                    prev->next = current->next;
                    if (current->next != nullptr)
                        current->next->prev = current->prev;
                }
                delete current;
                --this->_size;
                return true;
            }
        }

        prev = current;
        current = current->next;
    }

    return false;
}
// BC=Theta(1), WC=Theta(length of collision chaining), AC=O(length of collision chaining)

bool Bag::search(TElem elem) const {
    int pos = hash(elem);
    if (this->elements[pos] == nullptr) {
        return false;
    }

    Node *current = this->elements[pos];
    while (current != nullptr) {
        if (current->unique_element == elem) {
            return true;
        }
        current = current->next;
    }

    return false;
}
// BC=Theta(1), WC=Theta(length of collision chaining), AC=O(length of collision chaining)

int Bag::nrOccurrences(TElem elem) const {
    int pos = hash(elem);
    if (this->elements[pos] == nullptr) {
        return 0;
    }

    Node *current = this->elements[pos];
    while (current != nullptr) {
        if (current->unique_element == elem) {
            return current->frequency;
        }
        current = current->next;
    }
    return 0;
}
// BC=Theta(1), WC=Theta(length of collision chaining), AC=O(length of collision chaining)

int Bag::size() const {
    return this->_size;
}
// O(1)

bool Bag::isEmpty() const {
    return (this->_size == 0);
}
// O(1)

BagIterator Bag::iterator() const {
    return BagIterator(*this);
}


Bag::~Bag() {
    for (int i = 0; i < this->capacity && this->_size != 0; ++i) {
        if (this->elements[i] != nullptr) {
            Node *current = this->elements[i], *prev;
            while (current != nullptr) {
                prev = current;
                current = current->next;
                delete prev;
                --this->_size;
            }
        }
    }
}
// O(size)

int Bag::hash(int key) const {
    if (key < 0) key = -key;
    return key % this->capacity;
}

void Bag::resize() {
    auto newBag = new Bag(this->capacity * 2);
    BagIterator b = this->iterator();
    b.first();
    while (b.valid()) {
        newBag->add(b.getCurrent());
        b.next();
    }

    delete[] this->elements;

    this->elements = newBag->elements;
    this->_size = newBag->size();
    this->capacity = newBag->capacity;
}
// O(1)
