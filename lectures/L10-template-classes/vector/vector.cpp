#include "vector.h" 
#include <iostream> 

using namespace mycollection;
using namespace std;

BoundedVector::BoundedVector(size_t capacity) {
    _capacity = capacity;
    _size = 0;
    _elems = new int[_capacity];
}

BoundedVector::~BoundedVector() {
    delete _elems;
}

BoundedVector::value_type& BoundedVector::at(size_t index) {
    if (index < 0 || index > size()) 
        throw std::out_of_range("Out of bounds!");
    return _elems[index];
}

BoundedVector::value_type& BoundedVector::front() {
    return *begin();
}

BoundedVector::value_type& BoundedVector::back() {
    return *(end() - 1);
}
    
BoundedVector::iterator BoundedVector::begin() {
    return _elems;
}

BoundedVector::iterator BoundedVector::end() {
    return _elems + size();
}

bool BoundedVector::empty() {
    return size() == 0;
}

size_t BoundedVector::size() {
    return _size;
}

size_t BoundedVector::capacity() {
    return _capacity;
}

void BoundedVector::clear() {
    _size = 0;
}

BoundedVector::iterator BoundedVector::insert(iterator pos, value_type value) {
    if (size() == capacity()) 
        throw std::length_error("Exceeded maximum capacity!");
    std::copy(pos, end(), pos+1);
    *pos = value;
    ++_size;
    return pos;
}

BoundedVector::iterator BoundedVector::erase(iterator pos) {
    std::copy(pos+1, end(), pos);
    --_size;
    return pos;
}

void BoundedVector::push_back(value_type value) {
    insert(end(), value);
}

void BoundedVector::pop_back() {
    --_size;
}

void BoundedVector::debug() {
    std::copy(begin(), end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
}