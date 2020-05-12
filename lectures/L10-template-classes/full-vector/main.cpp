#include "vector.h"
#include <iostream>

// using namespace std;
using namespace mycollection;

int main() {
    BoundedVector<int> vec;
    vec.push_back(3);
    vec.push_back(7);
    vec.push_back(11);
    vec.debug();
    vec.insert(vec.begin(), 2);
    vec.debug();
    vec.insert(vec.begin()+1, 4);
    vec.debug();
    cout << *(vec.end()-1) << endl;
    vec.erase(vec.end()-1);
    vec.debug();
    vec.insert(vec.begin(), 15);
    vec.debug();
    vec.insert(vec.end(), 5);
    vec.debug();
    vec.erase(vec.begin());
    vec.debug();
}