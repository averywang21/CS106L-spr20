#include "vector.h"
#include <iostream>
#include <deque>
#include <algorithm>
#include <memory>
using namespace mycollection;

using std::cout;
using std::endl;
using std::string;

void badFunc() noexcept {
	throw std::out_of_range("Whoops");
}

int main() {
    vector<string> vec;	// This is mycollection::vector, not std::vector!
	vec.push_back("Avery");
	vec.push_back("Anna");
	vec.push_back("CS106L");

	//vector<int> heapVec = new vector<int>();
	//std::unique_ptr<vector<int>> heapUp = std::make_unique<vector<int>>();

	try {
		string badString = vec.at(3); // 3 is out of bounds
		cout << badString << endl; 
		badFunc();
	} catch (const std::exception& e) {
		cout << e.what() << endl;
		throw;
	}

	std::shared_ptr<int> sp1(new int);
	int* rawPtr = sp1.get();
	std::shared_ptr<int> sp2(rawPtr); // This is undefined behavior!
	std::shared_ptr<int> sp3 = sp1;
}

