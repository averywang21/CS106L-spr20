/*
 * Challenge questions and program design by Anna Zeng, Winter 2020.
 */

#include <iostream>
#include <vector>
#include <numeric>

using std::cout;    using std::endl;
using std::vector; 

int dotProduct(const vector<int>& v1, const vector<int>& v2) {
    /*
    * CHALLENGE #6:
    * Return the dot product of the two given vectors! We can
    * assume that v1 and v2 are the same length.
    *
    * (For those unfamiliar with the dot product, it multiplies the 
    * pair of values at each index across the two vectors, and then 
    * adds up the result of those multiplications across all indices.)
    *
    * However: You cannot do any explicit math! Instead, take a look
    * at the STL numeric library (an algorithms library specifically for
    * numeric values only) here: http://www.cplusplus.com/reference/numeric/.
    *
    * Your solution should be a single line!
    * If you're stuck, hint: what's another name for the dot product?
    */

    // DO STUFF HERE
	return std::inner_product(v1.begin(), v1.end(), v2.begin(), 0);    
}



/**********************************
 ***** DO NOT EDIT BELOW HERE *****
 **********************************/

const int CORRECT_CHAL6 = 0;

int main() {
    int student_res = dotProduct({1, 0, -1}, {1, 0, 1});
    if (student_res == CORRECT_CHAL6) 
        cout << "Matched challenge 6!" << endl;
    else 
        cout << "Your calculation returned " << student_res << ", but the correct answer is " << CORRECT_CHAL6 << ". Try again!" << endl;
    return 0;
}
