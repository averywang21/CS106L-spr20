#include "vector.h"
#include <iostream>
#include <deque>
#include <algorithm>
using namespace mycollection;

using std::cout;
using std::endl;
using std::string;

void badFunc() {
	throw std::out_of_range("Whoops");
}

int main() {
    vector<string> vec;	// This is mycollection::vector, not std::vector!
	vec.push_back("Avery");
	vec.push_back("Anna");
	vec.push_back("CS106L");
	
	try {
		string badString = vec.at(3);
		cout << badString << endl; 
		//badFunc();
	} catch (const std::exception& e) {
		cout << e.what() << endl;
		throw;
	}
}

