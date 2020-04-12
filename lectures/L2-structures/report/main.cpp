#include <iostream>
#include <utility>
#include <vector>
#include <math.h>

// report_lines function:
// prompts the user to type in lines of text
// until they press enter (empty line)
// then report the longest string, and the number of lines.
std::pair<int, std::string> report_lines() {
    std::string line;
    int number_of_lines = 0;
    std::string longest;

    while (getline(std::cin, line), line != "") {

        number_of_lines++;
        if (line.size() > longest.size()) {
            longest = line;
        }
    }
    return {number_of_lines, longest};
}

// main function: calls report_lines
int main() {
    std::string prompt = "Enter a bunch of words (press enter when you are done):";
    
    auto [number_of_lines, longest] = report_lines();


    std::cout << "You typed in: " << number_of_lines << " lines" << std::endl;
    std::cout << "The longest line is: " << longest << std::endl;
}