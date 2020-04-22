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

void print_pair_iterator(const std::pair<int, int>& p) {
    std::cout << p.first << ":" << p.second << std::endl;
}

int main() {
    std::map<int, int> map{{1, 2}, {3, 4}};
    auto iter = map.begin();
    // what is *iter at this line?


    ++iter;
    // what is (*iter).second at this line?


    auto iter2 = iter;
    ++iter;
    // what is (*iter).first at this line?


    // what is *iter2 at this line?


}
