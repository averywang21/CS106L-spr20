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
// right now: count how many times [X] appears in a [Container]

int main() {
    // Goal: solve the following five questions with five calls to the same function
    std::vector<int> vec{5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5};
    std::list<double> list{4.7, 3, 4, 3.7, 4.7, 2.9, 4.7};
    std::string s{"Hello world!"}

    // Count how many times 3 appears in a vector<int> (answer is 10)
    count_occurences(vec.begin(), vec.end(), 3);
    // Count how many times 4.7 appears in a list<double> (answer is 3)
    count_occurences(list.begin(), list.end(), 4.7);
    // Count how many times ‘X’ appears in a string (answer is 0)
    count_occurences(s.begin(), s.end(), 'X');
    // Count how many times 5 appears in the second half of a vector<int> (answer is 1)
    count_occurences(vec.begin() + vec.size()/2, vec.end(), 5);

    // Count how many elements in the second half of a vector<int> are at most 5 (answer is 6)
}

// check how many elements is the condition [val == 5] true?
// check how many elements is the condition [arbitrary predicate] true?
template <typename Iter, typename ElemType>
int count_occurences(Iter begin, Iter end, const ElemType& val) {
    int count = 0;
    for (auto iter = begin; iter != end; ++iter) {
        if (*iter == val) ++count;
    }
    return count;
}

template <typename Iter, typename ElemType, typename UniPred>
int count_occurences(Iter begin, Iter end, const ElemType& val, UniPred pred) {
    int count = 0;
    for (auto iter = begin; iter != end; ++iter) {
        if (pred(*iter)) ++count;
    }
    return count;
}
