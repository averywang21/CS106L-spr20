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
std::map<std::string, std::set<std::string> > friendList (const std::string& filename) {
    // This is the solution to the friendList problem
    // with one change: instead of a Vector as the key, we use a Set

    std::ifstream in;                                       // ifstream in;
    std::vector<std::string> lines;                         // Vector<string> lines;

    in.open(filename);   
    std::string line;                                       // openFile(in, filename)
    while(std::getline(in, line)) {                         // readEntireFile(in, lines);
        lines.push_back(line);
    }  

    std::map<std::string, std::set<std::string>> friends;   // Map<string, Set<string> > friends;     
    for (const auto& line : lines) {                        // for (string line: lines) {
        std::istringstream iss(line);                       //      Vector<string> people = stringSplit(line, " ");
        std::string s1, s2;                                 //      string s1 = people[0];
        iss >> s1 >> s2;                                    //      string s2 = people[1];

        // alternative if you don't like stringstreams
        // size_t split_index = line.find(" ");
        // std::string s1 = line.substr(0, split_index);
        // std::string s2 = line.substr(split_index+1);

        friends[s1].insert(s2);                             //      friends[s1] += s2;
        friends[s2].insert(s1);                             //      friends[s2] += s1;
    }                                                       // }
    return friends;
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
        for (auto iter = friends.begin(); iter != last; ++iter) {
            std::cout << *iter << ", ";
        }
        std::cout << *last << "}" << '\n';
    }
}
