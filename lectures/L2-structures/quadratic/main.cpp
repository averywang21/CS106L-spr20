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

// solves the quadratic equation using a, b, and c
// currently: returns true if a solution is found, false otherwise
// you might want to change that.
bool solve_quadratic(int a, int b, int c, double& root1, double& root2) {
    int D = b*b - 4*a*c;
    if (D >= 0) {
        root1 = (-b + sqrt(D))/(2*a);
        root2 = (-b - sqrt(D))/(2*a);
        return true;
    } else {
        return false;
    }
}

int main() {
    int a = read_int("Type in a: ");
    int b = read_int("Type in b: ");
    int c = read_int("Type in c: ");
    double root1, root2;

    if (solve_quadratic(a, b, c, root1, root2)) {
        // if it's a double root (root1 == root2), this is fine as well
        std::cout << "The roots are: " << root1 << " and " << root2 << std::endl;
    } else {
        std::cout << "No roots found." << std::endl;
    }
}