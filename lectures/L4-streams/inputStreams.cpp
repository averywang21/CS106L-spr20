#include <iostream>
#include <fstream>
#include <sstream>

using std::cout; 	using std::endl;
using std::string;	using std::cin;

int main() {
	/* We didn't get a chance to cover stringstreams explicitly 
	 * during lecture, so I want to recap it here.
	 * 
	 * The following code is a very idiomatic way to 
	 * read files from C++! Specifically, the code below is:
	 * - read in data from the file line by line (using getline)
	 * - for each line, process its contents using a stringstream
	 * - continue to do this until there's nothing more to read
	 *   (i.e. getline returns false)
	 */ 
	std::ifstream inputFile("input.txt");
	string line;
	while (std::getline(inputFile, line)) {
		// As we saw in lecture, the above line of code
		// is equivalent to (and is better than):
		// while (true) {
		//     std::getline(inputFile, line);
		//	   if (inputFile.fail()) break;
 	
		// Here we're converting line into a std::stringstream.
		// You can think of a stringstream as the equivalent
		// of the other streams we've seen so far, except the
		// external device isn't a console or file, but a
		// std::string object!
		std::stringstream ss(line);
		string name;
		int coolness;
		ss >> name >> coolness;

		// We're going to multiply coolness by 2, just to show
		// that the stringstream did in fact convert it to an int.
		cout << name << " is cool by a factor of " << coolness*2 << endl;
	}
    return 0;
}
