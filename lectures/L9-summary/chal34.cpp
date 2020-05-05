/*
 * Challenge questions and program design by Anna Zeng, Winter 2020.
 */

#include <iostream>
#include <algorithm>

using std::cout;    using std::endl;
using std::search;  using std::string;

template <typename T>
int countOccurrences(const T& text, const T& feature) {
    /*
    * CHALLENGE #3:
    * Return the number of times the feature string appears in the
    * text string! You can assume that all strings are lowercase.
    * For example, if text="thank you next next thank you next next"
    * and feature="next", then countOccurrences should return 4.
    *
    * Remember that to look for a string within another string, you'll
    * need to use the std::search algorithm.
    *
    * Note: std::search only returns the first time a string is found
    * within the given string! To find the second time feature appears within
    * text, therefore, what should you pass in as the "other" string (i.e. 
    * where should you start your "search" from on the second time around)?
    */

    int count = 0;

	auto curr = text.begin();
	auto end = text.end();
	while (curr != end) {
		auto found = std::search(curr, end, feature.begin(), feature.end());
		if (found == end) break;
		
		++count;
		curr = found + 1;
	}

    return count;
}

/*
 * CHALLENGE #4:
 * Modify countOccurrences above to work for any parameter type.
 * Note: text and feature must still match in type.
 *
 * Note that this is slightly different from the numOccurrences
 * that we've seen in lecture -- in lecture, we were counting
 * the number of times an element appeared in a container of those
 * elements. Here, we're counting the number of times a "container"
 * appears in another "container".
 *
 * // DO STUFF ABOVE
 *
 */



/**********************************
 ***** DO NOT EDIT BELOW HERE *****
 **********************************/

const int CORRECT_CHAL34 = 4;
const string HAYSTACK = "thank you next next thank you next next";
const string NEEDLE = "next";
    
int main() {
    int student_count = countOccurrences(HAYSTACK, NEEDLE);
    if (student_count == CORRECT_CHAL34)
        cout << "Matched challenges 3 and 4!" << endl;
    else 
        cout << "Your count was " << student_count << ", but the correct answer is " << CORRECT_CHAL34 << ". Try again!" << endl;
    
    return 0;
}
