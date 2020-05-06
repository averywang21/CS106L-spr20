#ifndef BOUNDED_VECTOR_H // include guard
#define BOUNDED_VECTOR_H

#include <cstddef>
#include <deque>

namespace mycollection {
    class vector {
    public:
        // Type alises
        using value_type = int;
        using iterator = int*;

        // Special Member Functions
        vector(size_t capacity = 10);
        ~vector();

        // Element Access
        value_type& at(size_t index);
        value_type& front();
        value_type& back();
    
        // Iterators
        iterator begin();
        iterator end();

        // Capacity
        bool empty();
        size_t size();
        size_t capacity();

        // Modifiers
        void clear();
        iterator insert(iterator pos, value_type value);
        iterator erase(iterator pos);
        void push_back(value_type value);
        void pop_back();

        // For Debugging Only
        void debug();

        // An odd ball just for the sake of an example
        // realistically a vector class should not have this method
        template <typename InputIt>
        void swap_elements(InputIt first, InputIt last);

        void reserve(size_t n);

    private:
        value_type* _elems;
        size_t _capacity;
        size_t _size;
    };
}

template <typename InputIt>
void mycollection::vector::swap_elements(InputIt first, InputIt last) {
    if (std::distance(first, last) != static_cast<int>(size())) 
        throw std::length_error("Can't swap vector with a range of different size");
    std::swap_ranges(first, last, begin());
}

#endif /* BOUNDED_VECTOR */