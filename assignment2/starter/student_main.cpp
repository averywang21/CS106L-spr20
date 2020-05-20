/*
 * Student Main Function
 * 
 * DO NOT SUBMIT THIS FILE (unless you wrote a cool extension using main)
 */
#include "hashmap.h"
// add necessary includes here

using namespace std;

/*
 * This main function will be run if the autograder is turned off inside "student_main.cpp".
 * You can treat this as if you had written your own main function.
 */
int student_main() {
    HashMap<string, int> map;
    cout << "Hello from your lecturers!" << endl;
    map.insert({"Anna", 2});
    map.insert({"Avery", 3});
    map.debug();
    return 0;
}