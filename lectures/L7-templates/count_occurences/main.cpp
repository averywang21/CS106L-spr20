#include <iostream>     // for cout, cin
#include <utility>      // for pair
#include <tuple>        // for tuple
#include <array>        // for array
#include <vector>       // for vector
#include <list>         // for list
#include <fstream>      // for ifstream
#include <sstream>      // for istringstream
#include <iomanip>      // for setprecision
#include <map>          // for map
#include <set>          // for set

// TODO: concept-lift this function so it becomes more general
// right now: count how many times int [val] appears in a vector of ints
int count_occurences(const std::vector<int>& vec, int val) {
  int count = 0; 
  for (size_t i = 0; i < vec.size(); ++i) { 
    if (vec[i] == val) ++count; 
  } 
  return count; 
}

int main() {
    // Goal: solve the following five questions with five calls to the same function
    std::vector<int> vec{5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5};
    std::list<double> list{4.7, 3, 4, 3.7, 4.7, 2.9, 4.7};
    std::string s{"Hello world!"};

    // Count how many times 3 appears in a vector<int> (answer is 10)
    auto count = count_occurences(vec, 3);
    std::cout << count << std::endl;
    // Count how many times 4.7 appears in a list<double> (answer is 3)
    // Count how many times ‘X’ appears in a string (answer is 0)
    // Count how many times 5 appears in the second half of a vector<int> (answer is 1)
    // Count how many elements in the second half of a vector<int> are at most 5 (answer is 6)
}