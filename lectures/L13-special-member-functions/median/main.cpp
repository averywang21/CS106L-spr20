#include "median.h"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using mycollection::StreamingMedianTracker;
using std::vector;

struct Patient {
    std::string name;
    int priority;
};

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

    auto compare_patient_priority = [](const auto& p1, const auto& p2) {return p1.priority < p2.priority; };
    StreamingMedianTracker<Patient, decltype(compare_patient_priority)> hospital(compare_patient_priority);
    hospital.insert({"Avery", 3});
    hospital.insert({"Anna", 5});
    hospital.insert({"Ali", 7});
    auto mid_patient = hospital.getMedian();
    cout << "The median patient is: " << hospital.getMedian().name << " (expected Anna)" << endl;
    hospital.insert({"Mike", 10});
    cout << "The median patient is: " << hospital.getMedian().name << " (expected Ali)" << endl;

    auto copy = hospital;
    
    return 0;
}
