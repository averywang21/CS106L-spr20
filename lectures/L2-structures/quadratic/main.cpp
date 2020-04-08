#include <iostream>
#include <utility>
#include <math.h>

// std::pair<bool, double, double> solve_quadratic(int a, int b, int c) {

// }

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
    int a, b, c;
    std::cout << "Enter a: ";
    std::cin >> a;
    std::cout << "Enter b: ";
    std::cin >> b;
    std::cout << "Enter c: ";
    std::cin >> c;
    double root1, root2;
    if (solve_quadratic(a, b, c, root1, root2)) {
        std::cout << "The roots are: " << root1 << " and " << root2 << std::endl;
    } else {
        std::cout << "No roots found." << std::endl;
    }
}