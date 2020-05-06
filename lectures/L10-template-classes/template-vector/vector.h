#ifndef BOUNDED_VECTOR_H // include guard
#define BOUNDED_VECTOR_H

#include <cstddef>
#include <iostream>

namespace mycollection {
    template <typename T>
    class vector {
    public:
        // Type alises
        using value_type = T;
        using iterator = T*;

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
        iterator insert(iterator pos, const value_type& value);
        iterator erase(iterator pos);
        void push_back(const value_type& value);
        void pop_back();

        // For Debugging Only
        void debug();

        // An odd ball just for the sake of an example
        // Very common mistake is to use the same name for the 
        // function template parameter and the class template parameter
        template <typename InputIt>
        void swap_elements(InputIt first, InputIt last);

        void reserve(size_t n);
    private:
        value_type* _elems;
        size_t _capacity;
        size_t _size;
    };
}

#include "vector.cpp"

#endif /* BOUNDED_VECTOR */