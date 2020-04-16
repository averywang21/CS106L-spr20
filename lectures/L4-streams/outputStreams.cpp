#include <iostream>
#include <fstream>

using std::cout;	using std::endl;

int main() {
   int bestNumber = 42;
   cout << "My favorite number is: " << bestNumber << endl;
   
   std::ofstream outputFile("out.txt");
   outputFile << "My favorite number is: " << bestNumber << endl;
   return 0;
}
