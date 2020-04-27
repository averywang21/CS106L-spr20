#include <iostream>     // for cout, cin
#include <utility>      // for pair
#include <tuple>        // for tuple
#include <array>        // for array
#include <vector>       // for vector
#include <fstream>      // for ifstream
#include <sstream>      // for istringstream
#include <iomanip>      // for setprecision
#include <map>          // for map
#include <set>          // for set

void print_deque(const std::deque<int>& collection) {
    std::cout << "{";
    for (auto iter = collection.begin(); iter != collection.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout <<  "}" << '\n';
}


void erase_elem_bad(std::deque<int>& d, int val) {
    for (auto iter = d.begin(); iter != d.end(); ++iter) {      // ++iter may not be valid!
        if (*iter == val) {
            d.erase(iter);          // careful - once you call erase, iter becomes invalid
        }
    }
}

void erase_elem(std::deque<int>& d, int val) {
    for (auto iter = d.begin(); iter != d.end();) {
        if (*iter == val) {
            iter = d.erase(iter);   // erase returns iter to next element
        } else {
            ++iter;                 // only increment if we did not erase
        }
    }
}

int main() {
    std::deque<int> d{3, 1, 4, 1, 5, 3, 3, 3, 4, 1, 1, 3};
    // erase_elem_bad(d, 3); // try uncommenting this and see what happens
    erase_elem(d, 3);
    print_deque(d);
}