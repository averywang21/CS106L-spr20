#include "vector.h"
#include <iostream>
#include <deque>
using namespace mycollection;

using std::cout;
using std::endl;

void test1(vector& vec) {
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
    cout << "DEQUE" << endl;
    std::copy(d.begin(), d.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
    vec.debug();

    
    //TODO: add resizing!
    cout << "Adding 15 16 17 17 18 19 (requires resizing!)" << endl;
    vec.push_back(15);
    vec.push_back(16);
    vec.push_back(17);
    vec.push_back(18);
    vec.push_back(19);
    vec.debug();
    vec.push_back(20);
    vec.debug();
}

int main() {
    vector vec;
    test1(vec);
} 