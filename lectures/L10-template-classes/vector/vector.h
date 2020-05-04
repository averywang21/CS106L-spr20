#ifndef BOUNDED_VECTOR_H // include guard
#define BOUNDED_VECTOR_H

#include <cstddef>
#include <deque>

namespace mycollection {
    class BoundedVector {
    public:
        // Type alises
        using value_type = int;
        using iterator = int*;

        // Special Member Functions
        BoundedVector(size_t capacity = 10);
        ~BoundedVector();

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

    private:
        value_type* _elems;
        size_t _capacity;
        size_t _size;
    };
}

template <typename InputIt>
void mycollection::BoundedVector::swap_elements(InputIt first, InputIt last) {
    if (std::distance(first, last) != static_cast<int>(size())) 
        throw std::length_error("Size of range does not match size");
    std::swap_ranges(first, last, begin());
}

#endif /* BOUNDED_VECTOR */