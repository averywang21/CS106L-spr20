#ifndef BOUNDED_VECTOR_H // include guard
#define BOUNDED_VECTOR_H

#include <cstddef>
#include <iostream>
#include <vector>

namespace mycollection {
    template <typename T, typename Compare = std::less<T>>
    class StreamingMedianTracker {
    public:

        // constructor that takes in a comparison function used to compare elements
        StreamingMedianTracker(const Compare& comp = Compare());

        // insert a single element into our tracker
        void insert(const T& elem);

        // insert a range of elements into our tracker
        template <typename InputIt>
        void insert(InputIt first, InputIt last);

        // retrieves the median of all elements inserted so far
        // if the number of elements is even, return the smaller one
        const T& getMedian();

    private:
        /* TODO: add any private members here */
        Compare _comp;
        std::vector<int> _elems;
    };

    template <typename T, typename Compare>
    StreamingMedianTracker<T, Compare>::StreamingMedianTracker(const Compare& comp) {
        _comp = comp;
    }

    template <typename T, typename Compare>
    void StreamingMedianTracker<T, Compare>::insert(const T& elem) {
        auto pos = std::lower_bound(_elems.begin(), _elems.end(), elem, _comp);
        _elems.insert(pos, elem);
    }

    template <typename T, typename Compare>
    template <typename InputIt>
    void StreamingMedianTracker<T, Compare>::insert(InputIt first, InputIt last) {
        std::for_each(first, last, [this](const T& val) {insert(val);} );
    }

    template <typename T, typename Compare>
    const T& StreamingMedianTracker<T, Compare>::getMedian() {
        return _elems[_elems.size()/2];
    }




}

#endif /* STREAMING_MEDIAN_TRACKER */