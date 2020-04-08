#include <iostream>
#include <utility>
#include <vector>
#include <math.h>

std::pair<int, int> minmax(std::vector<int>& vec) {
    int min = vec[0];
    int max = vec[0];
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i] < min) min = vec[i];
        if (vec[i] > max) max = vec[i];
    }
    return {min, max};
}

int main() {
    std::vector<int> vec{3, 1, 4, 1, 5};
    auto [min, max] = minmax(vec);
    std::cout << min << std::endl;
    std::cout << max << std::endl;
}