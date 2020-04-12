/* 
 * In class example: your goal is to
 * make the solve_quadratic function better
 * by 
 */
#include <iostream>
#include <utility>
#include <math.h>

/*
 * Don't worry about this function - just use it
 * reads an int - we'll cover this in lecture 4
 * WARNING: does absolutely zero error-checking
 * terrible to use in your assignments or CS 106B.
 */
int read_int(std::string prompt) {
    int val;
    std::cout << prompt;
    std::cin >> val;
    return val;
}

struct Solution {
    double one;
    double two;
    bool has_solution;
};

// solves the quadratic equation using a, b, and c
// currently: returns true if a solution is found, false otherwise
// you might want to change that.
std::pair<std::pair<double, double>, bool> solve_quadratic(int a, int b, int c) {
    int D = b*b - 4*a*c;
    if (D >= 0) {
        double root1 = (-b + sqrt(D))/(2*a);
        double root2 = (-b - sqrt(D))/(2*a);
        return {{root1, root2}, true};
    } else {
        return {{0, 0}, false};
    }
}

int main() {
    int a = read_int("Type in a: ");
    int b = read_int("Type in b: ");
    int c = read_int("Type in c: ");
    auto [roots, found] = solve_quadratic(a, b, c);
    auto [root1, root2] = roots;
    if (found) {
        // if it's a double root (root1 == root2), this is fine as well
        std::cout << "The roots are: " << root1 << " and " << root2 << std::endl;
    } else {
        std::cout << "No roots found." << std::endl;
    }
    
}


// Summary of today
// std::pair, struct, std::tuple
// auto, structured binding
// multiple return value


// Next time
// uniform initialization
// overview of C++ classes (how to read documentation: std::vector)
// l-value references, what is a reference, returning references, 


// rules about in/out/in-out parameters


