#include "vector.h"
#include <iostream>
#include <deque>
#include <algorithm>
using namespace mycollection;

using std::cout;
using std::endl;

void print_information(const vector<int>& vec) {
    cout << "these two lines would not compile without today's lecture" << endl;
    cout << vec.size() << endl;
    cout << vec.at(0) << endl;
    
    // cout << "these two lines will not compile without supplemental material (const_iterator implementation)" << endl;
    // auto max = *std::max_element(vec.begin(), vec.end());
    // cout << max << endl;
}

void still_crashes(vector<int> vec) {
    vector<int> copy = vec;
    cout << "Before we change copy: " << vec.at(1) << endl;
    copy.at(1) = 2;
    cout << "After we change copy: " << vec.at(1) << " (why does changing copy impact vec?)" << endl;
    cout << "The next line will crash!" << endl;
} // the code crashes here due to a triple free (delete called on same pointer three times). Why?


int main() {
    vector<int> vec;
    vec.push_back(3);

    cout << "After push_back(3)" << endl;
    vec.debug();
    vec.push_back(7);
    cout << "After push_back(7)" << endl;
    vec.debug();
    vec.push_back(11);
    cout << "After push_back(11)" << endl;
    vec.debug();
    vec.insert(vec.begin(), 2);
    cout << "After insert(vec.begin(), 2)" << endl;
    vec.debug();
    vec.insert(vec.begin()+1, 4);
    cout << "After insert(vec.begin()+1, 4)" << endl;
    vec.debug();
    vec.erase(vec.end()-1);
    cout << "After erase(vec.end()-1)" << endl;
    vec.debug();
    vec.insert(vec.begin(), 15);
    cout << "After insert(vec.begin(), 15)" << endl;
    vec.debug();
    vec.insert(vec.end(), 5);
    cout << "After insert(vec.end(), 5)" << endl;
    vec.debug();
    vec.erase(vec.begin());
    cout << "After erase(vec.begin())" << endl;
    vec.debug();

    std::deque<int> d {10, 11, 12, 13, 14};
    cout << "After swap elements with a deque{10, 11, 12, 13, 14}" << endl;
    vec.swap_elements(d.begin(), d.end());
    vec.debug();

    vec.at(0) = -10;
    print_information(vec);

    still_crashes(vec);
}