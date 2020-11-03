// Test settings - use this file to change which tests are RUN_TEST_1A

// Use this to run on the test harness
// 0 = run student_main, 1 = run test harness
#define RUN_TEST_HARNESS 0

// Change the 0 to a 1 to run that test
// Note that milestone 2 and 3 tests won't compile until their respective functions
// have a header in the .h, and implementations in the .cpp
// 1A - erase
// 1B - rehash
// 2A - indexing operator[]
// 2B - stream insertion operator<<
// 2C - equality operators (== and !=)
// 2D - const correctness (compiler errors indicate your functions aren't const correct)
// 3A - copy constructor and assignment
// 3B - move constructor and assignment (only tests correctness, will pass if you only implemented copy)
// 3C - move constructor + assignment   (tests efficiency, will not pass if you only implemented copy)

// Milestone 1 is optional
#define RUN_TEST_1A 0
#define RUN_TEST_1B 0

// Milestone 2 and 3 are required
#define RUN_TEST_2A 0
#define RUN_TEST_2B 0
#define RUN_TEST_2C 0
#define RUN_TEST_2D 0
#define RUN_TEST_3A 0
#define RUN_TEST_3B 0
#define RUN_TEST_3C 0

// These are optional tests, won't compile unless implemented
// iterators are tricky to get compiling - reach out if you have questions
// 5A - initializer_list constructor for HashMap
// 5B - range constructor for HashMap
// 6A-D - complete HashMapIterator class, as well as correct changes in HashMap class
// 6E-F - const correct HashMapIterator class
#define RUN_TEST_5A 0
#define RUN_TEST_5B 0
#define RUN_TEST_6A 0
#define RUN_TEST_6B 0
#define RUN_TEST_6C 0
#define RUN_TEST_6D 0
#define RUN_TEST_6E 0
#define RUN_TEST_6F 0
