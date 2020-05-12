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
        using const_iterator = const T*;

        // Special Member Functions
        vector(size_t capacity = 10);
        ~vector();

        // Element Access
        value_type& at(size_t index);
        value_type& front();
        value_type& back();

        const value_type& at(size_t index) const;
        const value_type& front() const;
        const value_type& back() const;
    
        // Iterators
        iterator begin();
        iterator end();

        // const_iterator
        const_iterator begin() const;
        const_iterator end() const;

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

    private:
        value_type* _elems;
        size_t _capacity;
        size_t _size;
    };
}

#include "vector.cpp"
#endif /* BOUNDED_VECTOR */