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

void print_pair (const std::pair<int, int>& p) {
    std::cout << p.first << ":" << p.second << std::endl;
}

int main() {
    std::map<int, int> map{{1, 2}, {3, 4}};
    auto iter = map.begin();
    // what is *iter at this line?
    ++iter;
    std::cout << "First line is a pair" << std::endl;
    print_pair(*iter);
    // what is (*iter).second at this line?
    std::cout << "Second line is an int " << std::endl;
    std::cout << (*iter).second << std::endl;
    auto iter2 = iter;
    ++iter;
    std::cout << "Third line is undefined behavior " << std::endl;
    // std::cout << (*iter).first << std::endl;
    // what is (*iter).first at this line?
    std::cout << "Fourth line is a pair" << std::endl;
    print_pair(*iter2);
    // what is *iter2 at this line?
}
