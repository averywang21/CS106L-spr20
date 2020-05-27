#include <iostream> 

using namespace mycollection;
// using namespace std;

template <typename T>
vector<T>::vector(size_t capacity) {
    _capacity = capacity;
    _size = 0;
    _elems = new T[_capacity];
}

template <typename T>
vector<T>::~vector() {
    delete[] _elems;
}

// Element Access
template <typename T>
typename vector<T>::value_type& vector<T>::at(size_t index) {
    if (index < 0 || index >= _size) 
        throw std::out_of_range("Out of bounds!");
    return _elems[index];
}

template <typename T>
typename vector<T>::value_type& vector<T>::front() {
    return *begin();
}

template <typename T>
typename vector<T>::value_type& vector<T>::back() {
    return *(end()-1);
}
    
// Iterators
template <typename T>
typename vector<T>::iterator vector<T>::begin() {
    return _elems;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
    return _elems + size();
}

// Capacity

template <typename T>
bool vector<T>::empty() {
    return size() == 0;
}

template <typename T>
size_t vector<T>::size() {
    return _size;
}

template <typename T>
size_t vector<T>::capacity() {
    return _capacity;
}

// Modifiers

template <typename T>
void vector<T>::clear() {
    _size = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos, const value_type& value) {
    if (size() == capacity()) 
        throw std::length_error("Exceeded maximum capacity!");
    std::copy_backward(pos, end(), end()+1);
    *pos = value;
    ++_size;
    return pos;
}

template <typename T>
typename vector<T>::iterator vector<T>::erase(iterator pos) {
    std::copy(pos+1, end(), pos);
    --_size;
    return pos;
}

template <typename T>
void vector<T>::push_back(const value_type& value) {
    if (size() == capacity()) 
        throw std::length_error("Exceeded maximum capacity!");
    insert(end(), value);
}

template <typename T>
void vector<T>::pop_back() {
    --_size;
}

template <typename T>
void vector<T>::debug() {
    std::copy(begin(), end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
}

template <typename T>
template <typename InputIt>
void vector<T>::swap_elements(InputIt first, InputIt last) {
    if (std::distance(first, last) != static_cast<int>(size())) 
        throw std::length_error("Can't swap vector with a range of different size");
    std::swap_ranges(first, last, begin());
}

// TODO - if n > capacity, then resize the underlying array
// so that the capcity is n.
// if n <= capcity, don't do anything
template <typename T>
void vector<T>::reserve(size_t n) {
    // depends on if we have time
}
