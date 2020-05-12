#include <string>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <random>

// We will represent a course on Carta/explorecourses with this struct.
struct Course {
    std::string name;
    double rating;
};

// This function allows you to print a Course struct to any ostream.
// Usage: std::cout << c << std::endl;
// We'll cover how to overload operators in about a week.
std::ostream& operator<<(std::ostream& os, const Course& c) {
    os << std::setw(15) << std::setfill(' ') << c.name << "   " << c.rating;
    return os;
}

// This is the function template we wrote last lecture.
// Solves the problem "how many times does [type] [val] appear in [range of elements]"
template <typename InputIt, typename DataType>
int countOccurences(InputIt begin, InputIt end, const DataType& val) {
    int count = 0;
    for (auto iter = begin; iter != end; ++iter) {
        if (*iter == val) ++count;
    }
    return count;
}

// A predicate function that is specialized to limit = 5.
bool isLessThan5(int val) {
    return val < 5;
}

// A predicate function, returns true if val < limit, false otherwise.
bool isLessThanLimit(int val, int limit) {
    return val < limit;
}

// A function which returns a fixed vector.
// This is just a quick survey of common courses.
// Sorry for the bias towards the CS core.
std::vector<Course> readCourses() {
    std::vector<Course> v = {{"CS 106A", 4.4337}, {"CS 106B", 4.4025},
        {"CS 107", 4.6912}, {"CS 103", 4.0532},
        {"CS 109", 4.6062}, {"CS 110", 4.343},
        {"Math 51", 3.6119}, {"Math 52", 4.325},
        {"Math 53", 4.3111}, {"Econ 1", 4.2552},
           {"Anthro 3", 3.71}, {"Educ 342", 4.55},
           {"Chem 33", 3.50}, {"German 132", 4.83},
           {"Econ 137", 4.84}, {"CS 251", 4.24},
           {"TAPS 103", 4.79}, {"Music 21", 4.37},
           {"English 10A", 4.41}};
    std::shuffle(v.begin(), v.end(), std::default_random_engine {});
    return v;
}

// A function which returns a vector of a bunch of numbers.
std::vector<double> readNumbers() {
    std::vector<double> numbers;
    std::generate_n(std::back_inserter(numbers), 500, std::rand);
    return numbers;
}

int main() {

    // Fun with algorithms.
    auto courses = readCourses();
    auto numbers = readNumbers();

    std::sort(numbers.begin(), numbers.end());

    // given two courses, return true if the left course is less than the right course, false otherwise
    // course1 < course2 if course1's rating is less than course2's rating
    auto course_less_than = [](const auto& c1, const auto& c2) {
        return c1.name < c2.name;
    };
    std::sort(courses.begin(), courses.end(), course_less_than);

    std::copy(courses.begin(), courses.end(),
              std::ostream_iterator<Course>(std::cout, "\n"));

    // FILL IN YOUR CODE HERE
}

