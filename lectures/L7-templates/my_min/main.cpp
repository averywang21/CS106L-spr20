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

int my_min(int a, int b) {
    return a < b ? a : b;

    // this is equivalent to:
    // if (a < b) return a;
    // else return b;
}

// TODO: add more templatized versions

int main() {
    auto min1 = my_min(3, 4);
    std::cout << min1 << std::endl;

    auto min2 = my_min(3.4, 4);         // this causes a warning
    std::cout << min2 << std::endl;

    auto min3 = my_min(2.1, 5.4);       // this causes a warning
    std::cout << min3 << std::endl;

    // TODO: add calls to your templatized my_min function.
}
