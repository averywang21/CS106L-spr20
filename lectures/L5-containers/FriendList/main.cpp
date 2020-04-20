#include <iostream>     // for cout, cin
#include <utility>      // for pair
#include <tuple>        // for tuple
#include <array>        // for array
#include <vector>       // for vector
#include <fstream>      // for ifstream
#include <sstream>      // for istringstream
#include <iomanip>      // for setprecision
#include <map>          // for map
#include <set>          // for set

/*
    Write a function named friendList that takes in a file name and reads friend relationships 
    from a file and writes them to a Map. friendList should return the populated Map. 
    Friendships are bi-directional, so if Abby is friends with Barney, Barney is friends 
    with Abby. The file contains one friend relationship per line, with names separated 
    by a single space. You do not have to worry about malformed entries.

    Then the call of friendList("buddies.txt") should return a resulting map that looks like this:
    {"Abby":{"Barney", "Clyde"}, "Barney":{"Abby"}, "Clyde":{"Abby"}}

    Here is the function prototype you should implement:
    Map<string, Vector<string> > friendList(String filename)
*/
std::map<std::string, std::set<std::string> > friendList(const std::string& filename) {
    // solution from CS 106B using Stanford libraries, 
    // except we won't check the return value of openFile
    // cause the solution doesn't handle the case when it fails anyways
    // we also use a set as the value of the map instead of a vector
    // since what if the same line appears twice in the file?

    // ifstream in;
    // Vector<string> lines;
    // openFile(in, filepath)
    // readEntireFile(in, lines);

    // Map<string, Set<string> > friends;
    // for (string line: lines) {
    //     Vector<string> people = stringSplit(line, " ");
    //     string s1 = people[0];
    //     string s2 = people[1];
    //     friends[s1] += s2;
    //     friends[s2] += s1;
    // }
    // return friends;  

    return {}; // just here so starter code compiles
}

/*
    Your homework assignment: can you make friendList even cleaner?
    My solution is 9 lines long.
    Hints:
        1. There's a way to declare an ifstream and open it at the same time. 
            Search the documentation for the constructor of the ifstream class. It turns out that
            this is better than creating then separately opening, due to a principle called RAII we'll cover in L15.
        2, Do you need an intermediate vector to read everything into?
        3. Splitting the string is kinda tedious. Instead of reading line by line, try reading token
            by token using >> (Anna briefly covered it in L4, but you might want to read more)
 */
std::map<std::string, std::set<std::string> > betterFriendList(const std::string& filename) {

    
    return {}; // just here so starter code compiles
}

/* This is a test harness, do not worry about it until lecture 6 */
int main() {
    auto answer = friendList("buddies.txt");

    // for each loop over a map, we'll talk about this lecture 6
    for (const auto& [name, friends] : answer) {
        std::cout << name << ": {";
        auto last = --friends.end();
        for (auto iter = friends.begin(); iter != friends.end(); ++iter) {
            std::cout << *iter << ", ";
        }
        std::cout << *last << "}" << '\n';
    }
}
