#include "vector.h"
#include <iostream>
#include <deque>
using namespace mycollection;

using std::cout;
using std::endl;
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
}