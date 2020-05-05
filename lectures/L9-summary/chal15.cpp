/*
 * Challenge questions and program design by Anna Zeng, Winter 2020.
 */

#include <iostream>
#include <fstream>
#include <algorithm>

using std::cout;    using std::endl;
using std::string;  using std::ifstream;

string fileToString(ifstream& file) {
    /*
    * CHALLENGE #1:
    * Read in all lines from the file and return the lines concatenated together
    * into a single string ret.
    *
    * Where there used to be a line break, instead insert a space (" ").
    */

    string ret = "";
	string line;
	while (getline(file, line)) {
		/* For Challenge 5: */
		auto exclToQues = [](char c) { 
			return c == '!' ? '?' : c; 
		};
		std::transform(line.begin(), line.end(), line.begin(), exclToQues);
		
		ret += line + " ";
	}
    return ret;
}

/*
 * CHALLENGE #5:
 * Modify fileToString above to turn every exclamation point in the file
 * into a question mark. In other words, if the file contains the line
 * "Also, test your might, Mortal Kombat!", you should turn that line into
 * "Also, test your might, Mortal Kombat?".
 *
 * To do this, add the following line of code before you append the
 * line from the file to the ret string:
 * std::transform(line.begin(), line.end(), line.begin(), func);
 *
 * The std::transform function takes each character in line, and transforms
 * it using the function passed in as the last parameter. Your task is to
 * write that function as a lambda function!
 *
 * Specifically, your lambda should take in a character, and if that
 * character c equals '!', then you should return '?'. Otherwise, you should
 * return the original character.
 *
 * // DO STUFF ABOVE
 *
 */



/**********************************
 ***** DO NOT EDIT BELOW HERE *****
 **********************************/

const string CORRECT_CHAL1 = "Thisisashortinputfilecomposedofspacesandofletters.Itisalsoafilewithendoflinecharacterstohelpyoutotestyourcodeandhelpyougetstarted.Isn'tthisthebestassignmentforyoutosolve?Also,testyourmight,MortalKombat!I'mnotsosure.";
const string CORRECT_CHAL5 = "Thisisashortinputfilecomposedofspacesandofletters.Itisalsoafilewithendoflinecharacterstohelpyoutotestyourcodeandhelpyougetstarted.Isn'tthisthebestassignmentforyoutosolve?Also,testyourmight,MortalKombat?I'mnotsosure.";

void removeSpaces(string& s) {
    s.erase(remove_if(s.begin(), s.end(), isspace), s.end()); 
}

int main() {
    // Test for challenges 1 and 5
    ifstream f("res/short.txt");
    string student_str = fileToString(f);
    removeSpaces(student_str);

    if (student_str == CORRECT_CHAL1)
        cout << "Matched Challenge 1!" << endl;
    else if (student_str == CORRECT_CHAL5)
        cout << "Matched Challenge 5!" << endl;
    else 
        cout << "Try again!" << endl;
    
    return 0;
}
