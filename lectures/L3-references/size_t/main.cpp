#include <iostream>     // for cout, cin
#include <utility>      // for pair
#include <tuple>        // for tuple
#include <array>        // for array
#include <vector>       // for vector
#include <fstream>      // for ifstream
#include <sstream>      // for istringstream
#include <iomanip>      // for setprecision
std::string chopBothEnds(const std::string& str);

int main() {
    std::cout << "First example: printing each letter on a new line" << std::endl;
    std::cout << "You should get a warning about comparing signed and unsigned integers." << std::endl;
    std::string str = "Hello World";
    for (int i = 0; i < str.size(); ++i) {
        std::cout << str[i] << std::endl;
    }

    std::cout << "Second example: testing a very common bug with size_t. How would you fix?" << std::endl;
    std::cout << "Test case 1: " << chopBothEnds("rubber duck") << std::endl;
    std::cout << "Test case 2: " << chopBothEnds("Ito-En Green Tea") << std::endl;
    std::cout << "Test case 3: " << chopBothEnds("AB") << std::endl;
    std::cout << "Test case 4: " << chopBothEnds("A") << std::endl;
    std::cout << "Test case 5: " << chopBothEnds("") << std::endl;

    std::cout << "DONE!" << std::endl;
}

std::string chopBothEnds(const std::string& str) {
	std::string result = "";	
	for (size_t i = 1; i < str.size()-1; ++i) {			   
        result += str[i];
	}
	return result;
}



