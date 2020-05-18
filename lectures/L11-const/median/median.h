#ifndef BOUNDED_VECTOR_H // include guard
#define BOUNDED_VECTOR_H

#include <cstddef>
#include <iostream>
#include <vector>

// recall: namespaces used to prevent naming confilcts
// in main.cpp, notice we use a "using namespace mycollection" at the top
namespace mycollection {
    // template types are T and Compare (if not provided, uses the default comparison on T)
    template <typename T, typename Compare = std::less<T>>
    class StreamingMedianTracker {
    public:
        // type alias (they are typically cased with underscore_case rather than camelCase)
        using const_reference = const T&;

        // constructor uses a default parameter if no comparison function given
        StreamingMedianTracker(const Compare& comp = Compare());

        // insert takes in a const_reference to prevent copies, and to ensure method does not change parameter
        void insert(const_reference elem);

        // getMedian returns const reference to prevent copies, and is a const member method since it doesn't alter private members
        const_reference getMedian() const;
        
        // template method within a template class
        template <typename InputIt>
        void insert(InputIt first, InputIt last);
    private:
        std::vector<T> _elems;
        Compare _comp;  // we store the comparison function from the constructor to use later
    };
    
    // recall the syntax for template class member functions
    // note: there's a slight quirk with lambdas, requiring use of member initializer lists (the thing after the colon)
    // we will talk about member initializer lists on Monday
    template <typename T, typename Compare>
    StreamingMedianTracker<T, Compare>::StreamingMedianTracker(const Compare& comp) : _elems(), _comp(comp) {}

    template <typename T, typename Compare>
    void StreamingMedianTracker<T, Compare>::insert(const_reference element) {
        // lower_bound returns iterator to the first element greater than element (compared using _comp)
        auto pos = std::lower_bound(_elems.begin(), _elems.end(), element, _comp);

        // this is exactly where we want to insert so that _elems always remains sorted
        _elems.insert(pos, element);
    }

    // recall that if you use a type alias before the class specifier,
    // you must include the class name followed by the scope resolution operator and the alias
    // need to use typename right before that to avoid compiler ambiguity
    // (i.e. typename StreamingMedianTracker<T, Compare>::const_reference)
    template <typename T, typename Compare>
    typename StreamingMedianTracker<T, Compare>::const_reference
    StreamingMedianTracker<T, Compare>::getMedian() const {
        return _elems[_elems.size()/2]; // handles both odd and even cases (in case of tie, return larger one)
    }

    // for template methods within template classes
    // you first declare the class template parameters, then the function template parameters
    template <typename T, typename Compare>
    template <typename InputIt>
    void StreamingMedianTracker<T, Compare>::insert(InputIt first, InputIt last) {
        // you could just do a for each loop of course
        // why are we capturing this? insert is a member function, so we need something to call it on
        // in the context of a class, insert(elem) implies this->insert(elem)
        // however, lambdas create their own scope, so we must explicitly capture "this" to call insert.
        std::for_each(first, last, [this](const auto& elem) {return this->insert(elem); });
    }

    // Current runtimes:
    // insert: O(N)
    // getMedian: O(1)

    // can you figure out a more efficient solution where insert runs in O(log N) and median still runs in O(1)?
    // the CS 106B lecture from May 13 might be helpful!
    // btw, this is a common interview problem (without the optional template stuff)
    // isn't it crazy that we technically only wrote 4 lines of code beyond the class syntax stuff?

}

#endif /* STREAMING_MEDIAN_TRACKER */