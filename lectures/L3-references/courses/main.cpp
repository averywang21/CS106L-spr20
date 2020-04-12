#include <iostream>     // for cout, cin
#include <utility>      // for pair
#include <tuple>        // for tuple
#include <array>        // for array
#include <vector>       // for vector
#include <fstream>      // for ifstream
#include <sstream>      // for istringstream
#include <iomanip>      // for setprecision

// forward declarations
struct Time;
struct Course;
void print_time(const Time& time);
void print_course(const Course& course);
void print_all_courses(const std::vector<Course>& courses);


struct Time {
  int hour, minute;
};

struct Course {
  std::string code;
  std::pair<Time, Time> time;
  std::vector<std::string> instructors;
};

std::pair<Course, bool> find(std::vector<Course>& courses, std::string& target) {
    // TODO
    (void) courses, (void) target;     // silence warnings
    return {{}, false};         // just here so it compiles
}

void shift(std::vector<Course>& courses) {
    // TODO
    (void) courses;             // silence warnings
}

int main() {
    // Courses
    Course now {"CS106L", { {16, 30}, {17, 50} }, {"Wang", "Zeng"} };
    Course before {"CS106B", { {14, 30}, {15, 20} }, {"Gregg", "Zelenski"} };
    Course future {"CS107", { {12, 30}, {13, 50} }, {"Troccoli"} };
    std::vector<Course> courses{now, before, future};
    
    std::cout << "Testing find function.\n";
    std::string target = "CS106L";
    auto [result, found] = find(courses, target);
    if (found) {
        print_course(result);
    } else {
        std::cout << "Not found" << std::endl;
    }

    std::cout << "\nTesting shift function.\n";
    std::cout << "Original list of courses:\n";
    print_all_courses(courses);
    shift(courses);
    std::cout << "\nAfter shifting all courses:\n";
    print_all_courses(courses);
}



// bonus stuff to make it easier to test your results
// don't worry about any of the below


void print_time(const Time& time) {
    std::cout << time.hour << ":" << time.minute;
}

// we'll overload operators instead, as this was really tedious.
void print_course(const Course& course) {
    std::cout << course.code << " ";
    print_time(course.time.first);
    std::cout << "-";
    print_time(course.time.second);
    std::cout << " ";
    for (const auto& in : course.instructors) {
        std::cout << in << " ";
    }
    std::cout << '\n';
}

void print_all_courses(const std::vector<Course>& courses) {
    for (const auto& course : courses) {
        print_course(course);
    }
}








