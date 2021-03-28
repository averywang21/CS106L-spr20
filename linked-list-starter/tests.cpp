#include "list.h"
#include <sstream>
#include <iomanip>
#include <set>

#define NUGGET_1 0
#define NUGGET_2 0
#define NUGGET_3 0
#define NUGGET_4 0
#define NUGGET_5 0
#define NUGGET_6 0
#define NUGGET_7 0
#define NUGGET_8 0
#define NUGGET_9 0
#define NUGGET_10 0

// Runtime assertion check
// Equivalent to CHECK_TRUE

struct CheckTrueAssertionFailure {
    int line;
};

void CHECK_TRUE(bool condition, int line) {
    if (!condition) {
        throw CheckTrueAssertionFailure{line};
    }
}

void starter_front_back_simple() {
    List<int> list;
    CHECK_TRUE(list.is_same({}), __LINE__);
    list.push_front(1);
    CHECK_TRUE(list.is_same({1}), __LINE__);
    list.push_back(2);
    CHECK_TRUE(list.is_same({1, 2}), __LINE__);
    list.push_front(3);
    CHECK_TRUE(list.is_same({3, 1, 2}), __LINE__);
    list.pop_back();
    CHECK_TRUE(list.is_same({3, 1}), __LINE__);
    CHECK_TRUE(list.front() == 3, __LINE__);
    CHECK_TRUE(list.back() == 1, __LINE__);
    list.front() = 4;
    list.back() = 5;
    CHECK_TRUE(list.is_same({4, 5}), __LINE__);
    CHECK_TRUE(list.front() == 4, __LINE__);
    CHECK_TRUE(list.back() == 5, __LINE__);
    list.pop_front();
    CHECK_TRUE(list.is_same({5}), __LINE__);
    list.pop_back();
    CHECK_TRUE(list.is_same({}), __LINE__);
}

void starter_clear_simple() {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.clear();
    CHECK_TRUE(list.is_same({}), __LINE__);
    list.push_back(3);
    CHECK_TRUE(list.is_same({3}), __LINE__);
    list.clear();
    CHECK_TRUE(list.is_same({}), __LINE__);
}

void iter_foreach_simple() {
    List<int> list;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);
    int count = 0;
    for (const auto& val : list) {
        CHECK_TRUE(count++ == val, __LINE__);
    }
    CHECK_TRUE(count == 3, __LINE__);
}

void iter_forward_simple() {
    List<int> list;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);
    auto iter = list.begin();
    auto iter_copy = iter;
    CHECK_TRUE(iter == iter_copy, __LINE__);
    CHECK_TRUE(iter == iter_copy++, __LINE__);
    CHECK_TRUE(iter != iter_copy--, __LINE__);
    CHECK_TRUE(iter == iter_copy, __LINE__);
}

void iter_bidirectional_simple() {
    List<int> list;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);
    auto iter = list.end();
    --iter;
    CHECK_TRUE(*iter == 2, __LINE__);
    --iter;
    CHECK_TRUE(*iter == 1, __LINE__);
    --iter;
    CHECK_TRUE(*iter == 0, __LINE__);
    CHECK_TRUE(iter == list.begin(), __LINE__);
}

void iter_algorithm_reverse() {
    List<int> list;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);
    std::reverse(list.begin(), list.end());
    CHECK_TRUE(list.is_same({2, 1, 0}), __LINE__);
}

#if NUGGET_1
void erase_simple() {
    List<int> list;
    list.push_back(1); // list = {1}
    list.push_back(2); // list = {1, 2}
    list.push_back(3); // list = {1, 2, 3}
    list.push_back(4); // list = {1, 2, 3, 4}
    list.push_back(5); // list = {1, 2, 3, 4, 5}
    CHECK_TRUE(list.is_same({1, 2, 3, 4, 5}), __LINE__);
    auto iter1 = list.begin(); // points to 1
    auto iter3 = ++++list.begin(); // points to 3
    auto iter5 = --list.end(); // points to 5
    list.erase(iter1); // list = {2, 3, 4, 5}
    CHECK_TRUE(list.is_same({2, 3, 4, 5}), __LINE__);
    list.erase(iter3); // list = {2, 4, 5}
    CHECK_TRUE(list.is_same({2, 4, 5}), __LINE__);
    list.erase(iter5); // list = {2, 4}
    CHECK_TRUE(list.is_same({2, 4}), __LINE__);
}
#endif

#if NUGGET_2
void remove_if_simple() {
    List<int> list;
    list.push_back(7); // list = {7}
    list.push_back(3); // list = {7, 3}
    list.push_back(10); // list = {7, 3, 10}
    list.push_back(-1); // list = {7, 3, 10, -1}
    list.push_back(6); // list = {7, 3, 10, -1, 6}

    auto less_than_5 = [](const auto& elem) {
        return elem < 5;
    };
    list.remove_if(less_than_5); // list = {7, 10, 6}
    CHECK_TRUE(list.is_same({7, 10, 6}), __LINE__);
}
#endif

#if NUGGET_3
void equality_simple() {
    List<int> list1;
    list1.push_back(1); // list1 = {1}
    list1.push_back(2); // list1 = {1, 2}
    List<int> list2;
    list2.push_back(1); // list2 = {1}
    list2.push_back(2); // list2 = {1, 2}
    CHECK_TRUE(list1 == list2, __LINE__); // list1 == list2
    list1.pop_front(); // list1 = {1}
    CHECK_TRUE(!(list1 == list2), __LINE__); // list1 != list2
}
#endif 

#if NUGGET_4
void comparison_simple() {
    List<int> list1;
    list1.push_back(1); // list1 = {1}
    List<int> list2;
    list2.push_back(2); // list2 = {2}
    CHECK_TRUE(list1 < list2, __LINE__); // {1} < {2}
    CHECK_TRUE(!(list1 > list2), __LINE__); 
    CHECK_TRUE(list1 != list2, __LINE__);

    list1.push_front(2); // list1 = {2, 1}
    CHECK_TRUE(!(list1 < list2), __LINE__);
    CHECK_TRUE(list1 > list2, __LINE__); // list2 is prefix of list1
    CHECK_TRUE(list1 != list2, __LINE__);
}

void comparison_list_in_set() {
    std::set<List<int>> set_of_lists;
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    set_of_lists.insert(list);
    CHECK_TRUE(set_of_lists.size() == 1, __LINE__);
    CHECK_TRUE(set_of_lists.begin()->size() == 2, __LINE__);
}
#endif

#if NUGGET_4
void stream_insert_simple() {
    List<int> list;
    list.push_back(1); // list1 = {1}
    list.push_back(2); // list2 = {1, 2}
    list.push_back(3); // list3 = {1, 2, 3}
    std::ostringstream oss;
    oss << list;
    CHECK_TRUE(oss.str() == "{1, 2, 3}", __LINE__);
}

void stream_insert_const_correct() {
    // Nugget #6

    // The starter code's header for operator<< is:
    //      std::ostream& operator<<(std::ostream&, List<T>&)
    // The correct header should be:
    //      std::ostream& operator<<(std::ostream&, const List<T>&)

    // TODO: write a test case using List<T> such that
    //      - it compiles correctly when the const is added
    //      - it does not compile when the const is missing
}
#endif

#if NUGGET_5
void indexing_simple() {
    List<int> list;
    std::vector<int> vector;
    for (size_t i = 0; i < 1000; ++i) {
        list.push_back(i);
        vector.push_back(i);
    }
    // A pretty common use of the indexing operator
    // just like the vector!
    // Why might this be a problem?
    int list_sum = 0;
    int vector_sum = 0;
    for (size_t i = 0; i < list.size(); ++i) {
        list_sum += list[i];
        vector_sum += vector[i];
    }
    CHECK_TRUE(list_sum == vector_sum, __LINE__);
}
#endif

#if NUGGET_6
void copy_constructor_simple() {
    List<int> list;
    list.push_back(1); // list = {1}
    list.push_back(2); // list = {1, 2}
    List<int> copy = list; // copy = list = {1, 2}
    CHECK_TRUE(list.is_same({1, 2}), __LINE__);
    CHECK_TRUE(copy.is_same({1, 2}), __LINE__);
    list.push_back(4); // list = {1, 2, 4}, copy = {1, 2}
    CHECK_TRUE(list.is_same({1, 2, 4}), __LINE__);
    CHECK_TRUE(copy.is_same({1, 2}), __LINE__);
}
#endif

#if NUGGET_7
void move_constructor_simple() {
    List<int> list;
    list.push_back(1); // list = {1}
    list.push_back(2); // list = {1, 2}
    List<int> moved = std::move(list); // moved = {1, 2}, list is undefined
    CHECK_TRUE(moved.is_same({1, 2}), __LINE__);
    moved.push_back(4); // moved = {1, 2, 4}
    List<int> new_list = std::move(moved); // new_list = {1, 2, 4}, moved is undefined
    CHECK_TRUE(new_list.is_same({1, 2, 4}), __LINE__);
}
#endif

#if NUGGET_8
void copy_assignment_simple() {
    List<int> list;
    list.push_back(1); // list = {1}
    list.push_back(2); // list = {1, 2}
    List<int> copy;
    copy = list; // copy = list = {1, 2}
    CHECK_TRUE(list.is_same({1, 2}), __LINE__); // 
    CHECK_TRUE(copy.is_same({1, 2}), __LINE__);
    list.push_back(4);
    CHECK_TRUE(list.is_same({1, 2, 4}), __LINE__);
    CHECK_TRUE(copy.is_same({1, 2}), __LINE__);
}

void move_assignment_simple() {
    List<int> list;
    list.push_back(1); // list = {1}
    list.push_back(2); // list = {1, 2}
    List<int> moved;
    moved = std::move(list); // moved = {1, 2}, list is undefined
    CHECK_TRUE(moved.is_same({1, 2}), __LINE__);
    moved.push_back(4); // moved = {1, 2, 4}
    list = std::move(moved); // list = {1, 2, 4}, moved is undefined - check that you can still reassign after moved
    CHECK_TRUE(list.is_same({1, 2, 4}), __LINE__);
}
#endif

void student_test_demo() {
    // Nugget 10
    // TODO: add your own test case
    // Feel free to add your own using the format shown here.
    CHECK_TRUE(false, __LINE__); // remove this line
}

template <typename T>
int run_test(const T& test, const std::string& test_name) {
    try {
        test();
        std::cout << "Test "  << std::setw(30) << std::left << test_name  << std::right << " PASS " << std::endl;
        return 1;
    } catch (const CheckTrueAssertionFailure& e)  {
        std::cout << "Test "  << std::setw(30) << std::left << test_name << std::right
             << " FAIL: VERIFY_TRUE assertion failure at line number " << e.line
             << " in file tests.cpp" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Test "  << std::setw(30) << std::left << test_name << std::right
             << " FAIL: exception thrown - " << e.what() << std::endl;
    } catch (const std::string& e) {
        std::cout << "Test "  << std::setw(30) << std::left << test_name  << std::right
        << " FAIL with string " << e << std::endl;
    } catch (const char *& e) {
        std::cout << "Test "  << std::setw(30) << std::left << test_name  << std::right
        << " FAIL with string " << e << std::endl;
    }
    return 0;
}

void skip_test(const std::string& test_name) {
    std::cout << "Test "  << std::setw(30) << std::left << test_name  << std::right << " SKIP " << std::endl;
}

int run_starter_tests() {
    int pass = 0;
    pass += run_test(starter_front_back_simple, "A_starter_front_back_simple");
    pass += run_test(starter_clear_simple, "B_starter_clear_simple");
    pass += run_test(iter_foreach_simple, "C_iter_foreach_simple");
    pass += run_test(iter_forward_simple, "D_iter_forward_simple");
    pass += run_test(iter_bidirectional_simple, "E_iter_bidirectional_simple");
    pass += run_test(iter_algorithm_reverse, "F_iter_algorithm_reverse");
    return pass;
}

int run_public_tests() {
    int pass = 0;
    #if NUGGET_1
        pass += run_test(erase_simple, "A_erase_simple");
    #else
        skip_test("A_erase_simple");
    #endif
    #if NUGGET_2
        pass += run_test(remove_if_simple, "B_remove_if_simple");
    #else
        skip_test("B_remove_if_simple");
    #endif
    #if NUGGET_3
        pass += run_test(equality_simple, "C_equality_simple");
    #else
        skip_test("C_equality_simple");
    #endif
    #if NUGGET_4
        pass += run_test(comparison_simple, "D_comparison_simple");
        pass += run_test(comparison_list_in_set, "E_comparison_list_in_set");
    #else
        skip_test("D_comparison_simple");
        skip_test("E_comparison_list_in_set");
    #endif
    #if NUGGET_5
        pass += run_test(stream_insert_simple, "F_stream_insert_simple");
        pass += run_test(stream_insert_const_correct, "G_stream_insert_const_correct");
    #else
        skip_test("F_stream_insert_simple");
        skip_test("G_stream_insert_const_correct");
    #endif
    #if NUGGET_6
        pass += run_test(indexing_simple, "H_indexing_simple");
    #else
        skip_test("H_indexing_simple");
    #endif
    #if NUGGET_7
        pass += run_test(copy_constructor_simple, "I_copy_ctor_simple");
    #else
        skip_test("I_copy_ctor_simple");
    #endif
    #if NUGGET_8
        pass += run_test(copy_assignment_simple, "J_copy_assign_simple");
    #else
        skip_test("J_copy_assign_simple");
    #endif
    #if NUGGET_9
        pass += run_test(move_constructor_simple, "K_move_ctor_simple");
        pass += run_test(move_assignment_simple, "L_move_assign_simple");
    #else
        skip_test("K_move_ctor_simple");
        skip_test("L_move_assign_simple");
    #endif
    return pass;
}

int run_student_tests() {
    int pass = 0;
    pass += run_test(student_test_demo, "A_student_test_demo");
    // Nugget 10
    // TODO: call your test case using the same format.
    return pass;
}

int run_hidden_tests() {
    std::cout << "Tests hidden until grading" << std::endl;
    return 0;
}

void run_test_harness() {
    std::cout << std::endl;
    std::cout << "----- CS 106L SIMPLE TEST HARNESS -----" << std::endl;
    std::cout << "Written by Avery Wang (2019-2020 lecturer)" << std::endl << std::endl;
    int required_pass = 0;
    int student_pass = 0;
    std::cout << "----- Starter Tests (Starter) -----" << std::endl;
    required_pass += run_starter_tests();
    std::cout << std::endl;
    std::cout << "----- Public Tests (Starter) -----" << std::endl;
    required_pass += run_public_tests();
    std::cout << std::endl;
    std::cout << "----- Hidden Tests (Starter) -----" << std::endl;
    required_pass += run_hidden_tests();
    std::cout << std::endl;
    std::cout << "----- Student Tests (Starter) -----" << std::endl;
    student_pass += run_student_tests();
    std::cout << std::endl << "----- Test Harness Summary -----" << std::endl;
    std::cout << "Required Tests passed: " << required_pass << "/18" << std::endl;
    std::cout << "Student Tests passed: " << student_pass << std::endl;

    if (required_pass < 9) {
        std::cout << "Some required tests were failed or skipped. " << std::endl;
    } else {
        std::cout << "You passed all required tests! Great job!" << std::endl;
    }

    std::cout << std::endl << "----- End of Test Harness -----" << std::endl;
}

int main() {
    run_test_harness();
}