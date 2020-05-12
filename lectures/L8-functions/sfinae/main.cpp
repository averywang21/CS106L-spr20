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

int main() {

  auto plus_three = [](int val) -> int {
    return val + 3;
  };

  int factor = 2;
  auto multiply = [factor](int val) -> int {
    return factor * val;
  };
}