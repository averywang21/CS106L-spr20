#include "median.h"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using mycollection::StreamingMedianTracker;
using std::vector;

int main() {
    StreamingMedianTracker<int> tracker;
    tracker.insert(3);
    tracker.insert(5);
    tracker.insert(15);
    cout << "The median so far is: " << tracker.getMedian() << " (expected 5)" << endl;
    tracker.insert(20);
    cout << "The median so far is: " << tracker.getMedian() << " (expected 15)" << endl;

    vector<int> vec{1, 2, 3, 4, 6, 7, 30, 40};
    tracker.insert(vec.begin(), vec.end());
    cout << "The median so far is: " << tracker.getMedian() << " (expected 6)" << endl;
    return 0;
}
