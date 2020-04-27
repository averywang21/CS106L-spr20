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
    d.insert(d.end(), 7);
    print_non_map(d);       // d = {1, 2, 3, 5, 6, 7}

    // how would you erase 2?
    d.erase(++d.begin());
    print_non_map(d);       // d = {1, 3, 5, 6, 7}

    // how would you insert 4 right before the 5?
    d.insert(d.begin()+2, 4);
    print_non_map(d);       // d = {1, 3, 4, 5, 6, 7}

    // how would you erase all elements after the 3?
    d.erase(d.begin() + 2, d.end());
    print_non_map(d);       // d = {1, 3, 4, 5, 6, 7}

        


    // your exercise to complete on your own
    std::map<int, int> map{{3, 4}, {1, 2}, {5, 6}}; // remember! internally the map is sorted
    // insert doesn't take in a position, since for a map the elements are sorted by the key
    
    // how would you insert {7, 8}?
    map.insert({7, 8});
    print_map(map);         // map = {1:2, 3:4, 5:6, 7:8}

    // how would you insert {3, 0}? that shouldn't work - you can't just overwrite a key
    auto [map_iter, success] = map.insert({3, 0});
    // iter points to {3, 4}, success is false

    print_map(map);         // map = {1:2, 3:4, 5:6, 7:8}

    // how would you change {3, 4} to {3, 0}? 
    // we could do map[3] = 0, or
    map_iter->second = 0;

    print_map(map);         // map = {1:2, 3:0, 5:6, 7:8}

    std::vector<int> vec{40, 60, 30, 70, 10, 20};
    std::set<int> set1{15, 35, 55, 75};
    std::set<int> set2{25, 35, 45, 65, 80, 100};

    // how would you convert vec into a std::set<int> called set3?
    std::set<int> set3{vec.begin(), vec.end()};
    print_non_map(set3);    // set3 = {10, 20, 30, 40, 60, 70};
    // how would you insert the contents of set1 into the beginning of vec?    
    vec.insert(vec.begin(), set1.begin(), set1.end());
    print_non_map(vec);     // vec = {15, 35, 55, 75, 40, 60, 30, 70, 10, 20};
}