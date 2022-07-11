//
// Created by andre on 09/04/2022.
//

#ifndef A5_6_ANDREIFABIANPOP_REPOSITORY_H
#define A5_6_ANDREIFABIANPOP_REPOSITORY_H

#include <cstring>
#include <vector>
#include <algorithm>
#include "../Domain/Tutorial.h"

template <typename TElement>
class Repository {
private:
    std::vector<TElement> elems;

public:
    explicit Repository();

    Repository(const Repository& aux);

    Repository& operator=(const Repository& v);

    // Adds an element to the current DynamicVector.
    int add(const TElement& e);

    // Removes the element from the specified index
    void remove(int index);

    // Returns the index of the element with the specified values, returns -1 if it is not found
    int get_index(const std::string&  title, const std::string&  presenter, const std::string&  link);

    bool valid(const Tutorial& e) const;
    // Checks if e is not already in the array, returns false if it is, true if it is not

    bool valid_index(unsigned int index) const;
    // Checks if there is an entry at the index 'index'

    /*
    Overloading the subscript operator
    Input: pos - a valid position within the vector.
    Output: a reference to the element o position pos.
    */
    TElement& operator[](int pos);

    void operator+(const TElement& e);

    int getSize() const;

    std::vector<TElement> get_all();
};

template<typename TElement>
Repository<TElement>::Repository() {
    this->elems.clear();
}

template<typename TElement>
Repository<TElement>::Repository(const Repository &aux) {
    this->elems = aux.elems;
}

template<typename TElement>
Repository<TElement>& Repository<TElement>::operator=(const Repository &v) {
    if (this == &v) {
        return *this;
    }

    this->elems = v.elems;

    return *this;
}

template<typename TElement>
int Repository<TElement>::add(const TElement &e) {
    if (valid(e)) {
        this->elems.push_back(e);
        return 1;
    } else {
        return 0;
    }
}

template<typename TElement>
void Repository<TElement>::remove(int index) {
    this->elems.erase(this->elems.begin() + index);
}

template<typename TElement>
int Repository<TElement>::get_index(const std::string &title, const std::string &presenter, const std::string &link) {
    for (int i = 0; i < this->elems.size(); ++i) {
        if (this->elems[i].get_title() == title &&
            this->elems[i].get_presenter() == presenter &&
            this->elems[i].get_link() == link) {
            return i;
        }
    }
    return -1;
}

template<typename TElement>
bool Repository<TElement>::valid(const Tutorial &e) const {
    bool val = true;
    std::for_each(this->elems.begin(), this->elems.end(), [&](const TElement& element) -> void {
        if (element.get_title() == e.get_title() && element.get_presenter() == e.get_presenter() && element.get_link() == e.get_link()) {
            val = false;
        }
    });
    return val;
}

template<typename TElement>
bool Repository<TElement>::valid_index(unsigned int index) const {
    return (index < this->elems.size());
}

template<typename TElement>
TElement &Repository<TElement>::operator[](int pos) {
    return this->elems[pos];
}

template<typename TElement>
void Repository<TElement>::operator+(const TElement &e) {
    this->elems.push_back(e);
}

template<typename TElement>
int Repository<TElement>::getSize() const {
    return this->elems.size();
}

template<typename TElement>
std::vector<TElement> Repository<TElement>::get_all() {
    return this->elems;
}

#endif //A5_6_ANDREIFABIANPOP_REPOSITORY_H
