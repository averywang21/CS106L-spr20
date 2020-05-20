#include "vector.h"
#include <iostream>
#include <deque>
#include <algorithm>
using namespace mycollection;

using std::cout;
using std::endl;

void print_information(const vector<int>& vec) {
	cout << "-----" << endl;
	cout << "Printing vector information..." << endl;
    // these two lines would not compile without const correctness lecture
    cout << "Size: " << vec.size() << endl;
    cout << "First element: " << vec.at(0) << endl;
    
    // these two lines would not compile without supplemental material (const_iterator implementation)
    auto max = *std::max_element(vec.begin(), vec.end());
    cout << "Max of first and last element: " << max << endl;
	cout << "-----" << endl;
}

void no_longer_crashes(vector<int> vec) {
    vector<int> copy = vec;
    cout << "Before we change copy: " << vec.at(1) << endl;
    copy.at(1) = 2;
    cout << "After we change copy: " << vec.at(1) << " changing copy does not impact vec anymore!" << endl;
    cout << "The next line will no longer crash!" << endl;
} 

int main() {
    vector<int> vec;
    vec.push_back(3);
    cout << "After push_back(3)" << endl;
    vec.debug();
    vec.push_back(7);
    cout << "After push_back(7)" << endl;
    vec.debug();
    vec.push_back(11);
    cout << "After push_back(11)" << endl;
    vec.debug();
    vec.insert(vec.begin(), 2);
    cout << "After insert(vec.begin(), 2)" << endl;
    vec.debug();
    vec.insert(vec.begin()+1, 4);
    cout << "After insert(vec.begin()+1, 4)" << endl;
    vec.debug();
    vec.erase(vec.end()-1);
    cout << "After erase(vec.end()-1)" << endl;
    vec.debug();
    vec.insert(vec.begin(), 15);
    cout << "After insert(vec.begin(), 15)" << endl;
    vec.debug();
    vec.insert(vec.end(), 5);
    cout << "After insert(vec.end(), 5)" << endl;
    vec.debug();
    vec.erase(vec.begin());
    cout << "After erase(vec.begin())" << endl;
    vec.debug();

    std::deque<int> d {10, 11, 12, 13, 14};
    cout << "After swap elements with a deque{10, 11, 12, 13, 14}" << endl;
    vec.swap_elements(d.begin(), d.end());
    vec.debug();

    vec.at(0) = -10;
	cout << "After vec.at(0) = -10" << endl;
    vec.debug();
	print_information(vec);

	cout << "Testing operators now..." << endl;
	cout << "After vec += 3" << endl;
	vec += 3;
	vec.debug();
	cout << "After vec += vec2 (which contains {2, 1})" << endl;
	vector<int> vec2;
	vec2.push_back(2);
	vec2.push_back(1);
	vec += vec2;
	vec.debug();
	
	cout << vec << endl;
	
	// This test is broken until the copy constructors lecture!
	// cout << "After vec3 = vec + vec2" << endl;
	// vector<int> vec3 = vec + vec2;
	// vec.debug();
	cout << "Testing << operator" << endl;
	cout << vec << endl;
    cout << endl;

	no_longer_crashes(vec);
}