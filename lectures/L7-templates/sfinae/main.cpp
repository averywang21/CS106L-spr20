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

/*
  Note to reader:

  This is an optional topic that I may cover at the end of lecture 7.
  You are not expected to know or understand any of the following - it's an extremely
  advanced topic that gives you some insight into how overload solution works inside
  C++, and touches on something known as SFINAE. 

  Substitution Failure Is Not An Error
  When the compiler tries to substitute an explicitly speicfied or deduced type 
  into a template and fails, the specialization is discarded from the overload set,
  and does not cause a compiler error. The easiest way to achieve this 
  is using SFINAE on the trailing return type.

  If you dare venture into this dangerous terrain, I'd first recommend understanding
  the three print_size functions. Do not attempt to parse the duck structs until
  you understand the print_size functions.
*/

struct RubberDuck {
  int duck_radius;
  size_t size() const {
    std::cout << "Measuring the size of rubber duck: ";
    double volume = 4*3.14*duck_radius*duck_radius*duck_radius/3; // pretend duck is a cube
    return static_cast<size_t>(volume);
  }
};

struct NumberLikeDuck {
  // warning: usually not good practice to define a conversion operator
  operator int() const {
    std::cout << "Printing with conversion operator ";
    return 7;
  }
};

struct ConfusedDuck {
  // here, both the size() operator and the negative size will work!
  int duck_radius;
  size_t size() const {
    std::cout << "Measuring the size of rubber duck: ";
    double volume = 4*3.14*duck_radius*duck_radius*duck_radius/3; // pretend duck is a cube
    return static_cast<size_t>(volume);
  }

  operator int() const {
    std::cout << "Printing with conversion operator ";
    return 7;
  }
};

// what does (void) [condition], size_t() mean?
// it means try substituting [condition] to ensure it semantically compiles
// but discard that result (hence the (void)). The comma operator ignores
// the left-hand side, and returns the default value of size_t(),
// which is how the return value is determined.

template <typename T>
auto print_size(const T& a) -> decltype((void) a.size(), size_t()) {

  std::cout << "printing with size member function: ";
  auto size = a.size();
  std::cout << size << std::endl;
  return size;
}

template <typename T>
auto print_size(const T& a) -> decltype((void) -a, size_t()) {

  std::cout << "printing with negative numeric function: ";
  auto size = a < 0 ? -a : a;
  std::cout << size << std::endl;
  return size;
}

template <typename T>
auto print_size(const T& a) -> decltype((void) a->size(), size_t()) {

  std::cout << "printing with pointer function: ";
  auto size = a->size();
  std::cout << size << std::endl;
  return size;
}

int main() {
    std::vector<int> vec{1, 2, 3};
    print_size(vec); 		          // calls first overload
    print_size(vec[1]);	          // calls second overload
    print_size(&vec);		          // calls third overload


    // RubberDuck duck{3};           // initializes duck with radius 3
    // print_size(duck);             // calls first overload
    // NumberLikeDuck number_duck{};
    // print_size(number_duck);      // calls second overload - interesting that operator is called in decltype as well!
    // ConfusedDuck confused_duck{3};
    // print_size(confused_duck); // ambiguous - both first and second overload would work
    // print_size(nullptr);          // no matching call
}