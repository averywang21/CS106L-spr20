/* 
 * Demonstrates what buffered vs. un-buffered
 * output looks like.
 *
 * Credits to Ali Malik for writing the program.
 */

#include <iostream>
#include <string>

using std::cout;    using std::endl;
using std::cerr;    using std::ostream;
using std::string;

/*
 * A helpful function that halts the program until
 * the user presses enter.
 */
void waitForEnter(const string& msg) {
	cout << msg;
	string l;
	std::getline(std::cin, l);
	cout << endl;
}


/*
 * Tests the buffer without flushing anything.
 *
 * Tries outputting a string to the stream, then does some slow
 * operation and then ouputs another string to the stream. We
 * see nothing is printed for a while then everything is printed at
 * once, suggesting cout is buffered.
 */
void testBuffer(ostream& os) {
	os << "Before loop - ";
	for(int i = 0; i < 2000000000; ++i) {
		// waste time
	}
	os << "After loop" << endl;
}

/*
 * Tests the buffer with flushing.
 *
 * Here we see that the first string is printed
 * to the console, and then there is a delay due to
 * the for loop before the second string is printed.
 */
void testBufferFlush(ostream& os) {
	os << "Before loop - " << std::flush;
	for(int i = 0; i < 2000000000; ++i) {
		// waste time
	}
	os << "After loop" << endl;
}



int main() {
	waitForEnter("Enter to continue: ");
	cout << "Testing cout..." << endl;
	testBuffer(cout);
	cout << endl;

	/* Prints a line of 20 = characters. */
	cout << string(20, '=') << endl;

	waitForEnter("Enter to continue: ");
	cout << "Testing flushed cout..." << endl;
	testBufferFlush(cout);
	cout << endl;
}
