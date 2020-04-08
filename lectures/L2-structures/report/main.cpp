#include <iostream>
#include <utility>
#include <vector>
#include <math.h>


// report_lines function:
// prompts the user to type in lines of text
// until they press enter (empty line)
// then report the longest string, and the number of lines.

// main function: calls report_lines
int main() {
    std::string prompt = "Enter a bunch of words (press enter when you are done):";
    size_t number_of_lines = 0;
    std::string longest;


    std::cout << "You typed in: " << number_of_lines << " lines" << std::endl;
    std::cout << "The longest line is: " << longest << std::endl;
}