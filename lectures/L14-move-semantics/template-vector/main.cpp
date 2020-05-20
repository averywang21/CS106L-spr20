#include "vector.h"
#include <iostream>
#include <deque>
#include <algorithm>
using namespace mycollection;

using std::cout;
using std::endl;
using std::string;

vector<string> findAllWords(size_t size);

int main() {
    vector<string> words1 = findAllWords(54321234);
    vector<string> words2;
    words2 = findAllWords(54321234);
    cout << "done!" << endl;
}

vector<string> findAllWords(size_t size) {
    // do some file reading
    vector<string> words(size, "Ito");
    return words;
}
