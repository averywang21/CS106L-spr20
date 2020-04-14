#include <iostream>     // for cout, cin
#include <utility>      // for pair
#include <tuple>        // for tuple
#include <array>        // for array
#include <vector>       // for vector
#include <fstream>      // for ifstream
#include <sstream>      // for istringstream
#include <iomanip>      // for setprecision
template <typename T> void print_vector(const std::vector<T>& vec);

int main() {
    std::vector<int> original{1, 2};
    std::vector<int> copy = original;
    std::vector<int>& lref = original;

    original.push_back(3);
    copy.push_back(4);
    lref.push_back(5);
    // original (lref) = {1, 2, 3, 5}
    // copy = {1, 2, 4}
    std::cout << "Example in class: \n";
    std::cout << "original (lref) = ";
    print_vector(original);
    std::cout << "copy = ";
    print_vector(copy);
    std::cout << "\n";

    lref = copy;
    copy.push_back(6);
    original.push_back(7);
    // Q1: what are contents of original?
    // Q2: what are contents of copy?

    std::cout << "Poll question in class:\n";
    std::cout << "original (lref) = ";
    print_vector(original);
    std::cout << "copy = ";
    print_vector(copy);
}

template <typename T>
void print_vector(const std::vector<T>& vec) {
    std::cout << "{";
    for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
        std::cout << *iter;
        if (iter + 1 != vec.end()) std::cout << ", ";
    }
    std::cout << "}\n";
}