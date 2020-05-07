#include "vector.h" 
#include <iostream> 

using namespace mycollection;
// using namespace std; // ambiguous!

vector::vector(size_t capacity) {
    _capacity = capacity;
    _size = 0;
    _elems = new int[_capacity];
}

vector::~vector() {
    delete[] _elems;
}

vector::value_type& vector::at(size_t index) {
    if (index < 0 || index > size()) 
        throw std::out_of_range("Out of bounds!");
    return _elems[index];
}

vector::value_type& vector::front() {
    return *begin();
}

vector::value_type& vector::back() {
    return *(end() - 1);
}
    
vector::iterator vector::begin() {
    return _elems;
}

vector::iterator vector::end() {
    return _elems + size();
}

bool vector::empty() {
    return size() == 0;
}

size_t vector::size() {
    return _size;
}

size_t vector::capacity() {
    return _capacity;
}

void vector::clear() {
    _size = 0;
}

vector::iterator vector::insert(iterator pos, value_type value) {
    if (size() == capacity()) 
        throw std::length_error("Exceeded maximum capacity!");
    std::copy(pos, end(), pos+1);
    *pos = value;
    ++_size;
    return pos;
}

vector::iterator vector::erase(iterator pos) {
    std::copy(pos+1, end(), pos);
    --_size;
    return pos;
}

void vector::push_back(value_type value) {
    insert(end(), value);
}

void vector::pop_back() {
    --_size;
}

void vector::debug() {
    std::copy(begin(), end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
}

// TODO - if n > capacity, then resize the underlying array
// so that the capcity is n.
// if n <= capcity, don't do anything
void vector::reserve(size_t n) {
    (void) n; // silence compiler warnings
    // depends on if we have time
}