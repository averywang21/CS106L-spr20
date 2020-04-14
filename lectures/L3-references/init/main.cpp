#include <iostream>     // for cout, cin
#include <utility>      // for pair
#include <tuple>        // for tuple
#include <array>        // for array
#include <vector>       // for vector
#include <fstream>      // for ifstream
#include <sstream>      // for istringstream
#include <iomanip>      // for setprecision

// forward declarations
template <typename T> void print_vector(const std::vector<T>& vec);

int main() {
    // Uniform initialization
    std::cout << "Testing out the cool constructors using uniform initialization\n";
    std::vector<std::string> default_init;

    std::vector<std::string> vec(10, "Ito-En");


    std::vector<std::string> value_init{};

    std::vector<std::string> direct_init{3, "init"};
    std::vector<std::string> copy_init = {3, "init"};
    std::vector<std::string> list_init{"1", "2", "3"};
    std::vector<std::string> aggr_init = {"1", "2", "3"};

    print_vector(default_init);
    print_vector(value_init);
    print_vector(direct_init);
    print_vector(copy_init);
    print_vector(list_init);
    print_vector(aggr_init);

    std::cout << "\nCareful about ambiguous uniform initialization vs. initializer_list\n";
    std::vector<int> int_list_init{3, 2}; // {3, 2}
    std::vector<int> int_fill_ctor(3, 2); // {2, 2, 2}
    // auto list_init{3, 2};          // just found out this doesn't compile anymore, neat! 
    print_vector(int_list_init);
    print_vector(int_fill_ctor);
 
}



// bonus stuff to make it easier to test your results
// don't worry about any of the below


// generic function to print any kind of vector
template <typename T>
void print_vector(const std::vector<T>& vec) {
    std::cout << "{";
    for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
        std::cout << *iter;
        if (iter + 1 != vec.end()) std::cout << ", ";
    }
    std::cout << "}\n";
}
