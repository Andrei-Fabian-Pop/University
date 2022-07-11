////
//// Created by andre on 19/03/2022.
////
//
//#include "DynamicVector.h"
//
//template<typename TElement>
//DynamicVector<TElement>::DynamicVector(int capacity) {
//    this->size = 0;
//    this->capacity = capacity;
//    this->elems = new TElement[capacity];
//}
//
//template<typename TElement>
//DynamicVector<TElement>::DynamicVector(const DynamicVector& v)
//{
//    this->size = v.size;
//    this->capacity = v.capacity;
//    this->elems = new TElement[this->capacity];
//    for (int i = 0; i < this->size; i++)
//        this->elems[i] = v.elems[i];
//}
//
//template<typename TElement>
//DynamicVector<TElement>::~DynamicVector() {
//    delete[] this->elems;
//}
//
//template<typename TElement>
//DynamicVector<TElement>& DynamicVector<TElement>::operator=(const DynamicVector& v)
//{
//    if (this == &v)
//        return *this;
//
//    this->size = v.size;
//    this->capacity = v.capacity;
//
//    delete[] this->elems;
//    this->elems = new TElement[this->capacity];
//    for (int i = 0; i < this->size; i++)
//        this->elems[i] = v.elems[i];
//
//    return *this;
//}
//
//template<typename TElement>
//int DynamicVector<TElement>::add(const TElement& e)
//{
//    if (valid(e)) {
//        if (this->size == this->capacity)
//            this->resize(this->size + 1);
//        this->elems[this->size] = e;
//        this->size++;
//
//        return 1;
//    } else {
//        return 0;
//    }
//}
//
//template<typename TElement>
//void DynamicVector<TElement>::resize(int new_size)
//{
//    this->capacity = new_size;
//
//    auto* els = new TElement[this->capacity];
//    for (int i = 0; i < this->size; i++)
//        els[i] = this->elems[i];
//
//    delete[] this->elems;
//    this->elems = els;
//}
//template<typename TElement>
//TElement & DynamicVector<TElement>::operator[](int pos)
//{
//    return this->elems[pos];
//}
//
//template<typename TElement>
//int DynamicVector<TElement>::getSize() const
//{
//    return this->size;
//}
//
//template<typename TElement>
//void DynamicVector<TElement>::remove(int index) {
//    for (int i = index; i < this->size - 1; ++i) {
//        this->elems[i] = this->elems[i+1];
//    }
//    --this->size;
//}
//
//template<typename TElement>
//int DynamicVector<TElement>::get_index(const std::string& title, const std::string& presenter, const std::string& link) {
//    for (int i = 0; i < this->size; ++i) {
//        if (this->elems[i].get_title() == title &&
//                this->elems[i].get_presenter() == presenter &&
//                this->elems[i].get_link() == link) {
//            return i;
//        }
//    }
//
//    return -1;
//}
//
//template<typename TElement>
//DynamicVector<TElement>::DynamicVector() {
//    this->elems = new TElement [0];
//    this->size = 0;
//    this->capacity = 0;
//}
//
//template<typename TElement>
//bool DynamicVector<TElement>::valid(const Tutorial& e) const {
//    for (int i = 0; i < this->size; ++i) {
//        if (this->elems[i].get_title() == e.get_title() &&
//            this->elems[i].get_presenter() == e.get_presenter() &&
//            this->elems[i].get_link() == e.get_link()) {
//            return false;
//        }
//    }
//    return true;
//}
//
//template<typename TElement>
//bool DynamicVector<TElement>::valid_index(int index) const {
//    if (index >= 0 && index < this->size) {
//        return true;
//    }
//    return false;
//}
//
//template<typename TElement>
//void DynamicVector<TElement>::operator+(const TElement& e) {
//    if (valid(e)) {
//        if (this->size == this->capacity)
//            this->resize(this->size + 1);
//        this->elems[this->size] = e;
//        this->size++;
//    }
//}
