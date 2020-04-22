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

template <typename T>
void print_non_map(const T& collection) {
    std::cout << "{";
    for (auto iter = collection.begin(); iter != collection.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout <<  "}" << '\n';
}

template <typename T>
void print_map(const T& collection) {
    std::cout << "{";
    for (auto iter = collection.begin(); iter != collection.end(); ++iter) {
        std::cout << iter->first << ":" << iter->second << " ";
    }
    std::cout <<  "}" << '\n';
}

int main() {

    std::deque<int> d{1, 2, 3, 5, 6};
    
    // how would you insert 7 after the 6?

    // how would you erase 2?

    // how would you insert 4 right before the 5?

    // how would you erase all elements after the 3?


    // your exercise to complete on your own
    std::map<int, int> map{{3, 4}, {1, 2}, {5, 6}}; // remember! internally the map is sorted
    // insert doesn't take in a position, since for a map the elements are sorted by the key
    
    // how would you insert {7, 8}?

    // how would you insert {3, 0}? that shouldn't work - you can't just overwrite a key

    // how would you change {3, 4} to {3, 0}? 

    std::vector<int> vec{10, 20, 30, 40, 50, 60};
    std::set<int> set1{15, 35, 55, 75};
    std::set<int> set2{25, 35, 45, 65, 80, 100};

    // how would you convert vec into a std::set<int> called set3?

    // how would you insert the contents of set1 into the beginning of vec?    

}
