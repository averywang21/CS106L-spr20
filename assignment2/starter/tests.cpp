/*
 * STL HashMap Test Harness
 * Created by Avery Wang (lecturer for 2019-2020 - awvry952@stanford.edu)
 * 
 * DO NOT SUBMIT THIS FILE (unless you added extra tests for us)
 */
#include "hashmap.h"
#include "test_settings.cpp"

using namespace std;

#include <map>
#include <vector>
#include <utility>
#include <algorithm>
#include <sstream>
#include <set>
#include <iomanip>

// ----------------------------------------------------------------------------------------------
// Global Constants and Type Alises (DO NOT EDIT)
using clock_type = std::chrono::high_resolution_clock;
using ms = std::chrono::nanoseconds;
const std::vector<std::pair<std::string, int> > vec {
    {"A", 3}, {"B", 2}, {"C", 1}, {"A", -5}, {"B", 3}, {"A", 5}, {"C", 1}
};

const std::vector<std::string> keys {"A", "B", "C", "Not found"};
template <typename Map1, typename Map2> bool check_map_equal(Map1& map, Map2& answer) {
    if (answer.empty() != map.empty() || answer.size() != map.size()) return false;

    for (const auto& [key, mapped] : answer) {
        if(map.contains(key) == false || map.at(key) != mapped) return false;
    }
    return true;
}

// Runtime assertion check
// Equivalent to CHECK_TRUE 

struct VerifyTrueAssertionFailure {
    int line;
};

void VERIFY_TRUE(bool condition, int line) {
    if (!condition) {
        throw VerifyTrueAssertionFailure{line};
    }
}


// ----------------------------------------------------------------------------------------------
/* Starter Code Test Cases (DO NOT EDIT) */

void A_basic() {
    /*
    * Verifies basic operations by comparing behavior with std::map
    *      - default ctor
    *      - size, empty, bucket_count
    *      - contains, at (used as an r-value)
    *
    * Mainly checking that check_map_equal compiles correctly.
    */
    std::map<std::string, int> answer;
    HashMap<std::string, int> map;
    VERIFY_TRUE(check_map_equal(map, answer), __LINE__);
    VERIFY_TRUE(map.bucket_count() == 10, __LINE__);
}
void B_insert() {
    /*
    * Verifies functionality of insert.
    */
    std::map<std::string, int> answer;
    HashMap<std::string, int> map;
    VERIFY_TRUE(check_map_equal(map, answer), __LINE__);
    VERIFY_TRUE(map.bucket_count() == 10, __LINE__);

    for (const auto& kv_pair : vec) {
        answer.insert(kv_pair);
        map.insert(kv_pair);
        VERIFY_TRUE(check_map_equal(map, answer), __LINE__);
    }

    VERIFY_TRUE(map.bucket_count() == 10, __LINE__);
}

void C_clear() {
    /*
    * Tests clear operations, and ensure map is in valid
    * state after a call to clear.
    */
    std::map<std::string, int> answer;
    HashMap<std::string, int> map;

    for (size_t j = 0; j < 3; ++j) {
       for (const auto& kv_pair : vec) {
           answer.insert(kv_pair);
           map.insert(kv_pair);
       }

       answer.clear();
       map.clear();

       VERIFY_TRUE(check_map_equal(map, answer), __LINE__);
    }
}
void D_at() {
    /*
    * Tests whether at correctly returns a reference.
    */
    std::map<std::string, int> answer;
    HashMap<std::string, int> map;
    answer.insert({"A", 42});
    answer.insert({"B", 137});
    answer.insert({"C", -1});

    // at returns a reference, so assigning their return value on the left-hand value should
    // change the contents of the map.
    answer.at("A") = 42;
    answer.at("B") = 137;
    answer.at("A") = -42;
    answer.at("C") = answer.at("A");
    VERIFY_TRUE(answer.at("A") == -42, __LINE__);
    VERIFY_TRUE(answer.at("B") == 137, __LINE__);
    VERIFY_TRUE(answer.at("C") == -42, __LINE__);

    // verify that we can save the reference returned by at.
    auto copy = answer.at("A");
    auto& ref = answer.at("B");
    copy = 0;
    ref = 0;
    VERIFY_TRUE(answer.at("A") == -42, __LINE__);
    VERIFY_TRUE(answer.at("B") == 0, __LINE__);

    // verify that correct exceptions are thrown
    HashMap<std::string, int> map2;
    bool correct_exception = false;
    try {
        map2.at("Exists") = 5;
    } catch (const std::out_of_range& e) {
        correct_exception = true;
    } 
    VERIFY_TRUE(correct_exception, __LINE__);
    map2.insert({"Exists", 4});
    VERIFY_TRUE(map2.contains("Exists"), __LINE__);
    VERIFY_TRUE(!map2.contains("Does not exist"), __LINE__);
    correct_exception = true;
    try {
        map2.at("Does not exist") = 5;
    } catch (const std::out_of_range& e) {
        correct_exception = true;
    } 
    VERIFY_TRUE(correct_exception, __LINE__);
}

void E_custom_bucket_count() {
    /*
    * Tests ctor taking in num_buckets, while hash function
    * still uses the default. Also tests correct function of load_factor.
    */
    HashMap<int, int> many_buckets(10000);
    HashMap<int, int> one_bucket(1);
    std::map<int, int> answer;

    for (int i = 0; i < 100; ++i) {
       many_buckets.insert({i, -i});
       one_bucket.insert({i, -i});
       answer.insert({i, -i});
    }

    VERIFY_TRUE(check_map_equal(many_buckets, answer), __LINE__);
    VERIFY_TRUE(check_map_equal(one_bucket, answer), __LINE__);

    VERIFY_TRUE(many_buckets.bucket_count() == 10000, __LINE__);
    VERIFY_TRUE(one_bucket.bucket_count() == 1, __LINE__);

    float epsilon = 0.001;
    VERIFY_TRUE(many_buckets.load_factor() - 0.01 < epsilon, __LINE__);
    VERIFY_TRUE(one_bucket.load_factor() - 100 < epsilon, __LINE__);
}
void F_custom_hash_function() {
    /*
    * Tests ctor taking in a num_buckets and hash function.
    * We use a hash function that distributes similar inputs
    * more randomly across the buckets.
    */
    using K = int;
    using V = char;
    auto identity_shifted = [](const K& key) {
       return (key * 43037 + 52081) % 79229;
    };

    // hey, didn't you use this from assignment 1?
    // now you know what the priority queue decltype comes from!
    HashMap<K, V, decltype(identity_shifted)> map(75, identity_shifted);
    std::map<K, V> answer;

    for (int i = 0; i < 50; ++i) {
       map.insert({i, 'a' + i});
       answer.insert({i, 'a' + i});
       VERIFY_TRUE(check_map_equal(map, answer), __LINE__);
    }
}

void G_erase() {
    /*
    * Tests erase operation in combination with basic operations.
    */
    std::map<std::string, int> answer;
    HashMap<std::string, int> map;

    for (const auto& kv_pair : vec) {
        answer.insert(kv_pair);
        map.insert(kv_pair);
    }

    // remove one and insert two back at a time
    for (size_t i = 0; i < vec.size(); ++i) {
        auto& [key1, mapped1] = vec[i];
        auto& pair2 = vec[(i+3) % vec.size()];
        answer.erase(key1);
        map.erase(key1);
        VERIFY_TRUE(check_map_equal(map, answer), __LINE__);

        answer.erase("Not a key");
        map.erase("Not a key");
        VERIFY_TRUE(check_map_equal(map, answer), __LINE__);

        answer.insert(pair2);
        map.insert(pair2);
    }

    // remove one at a time, until map is empty
    for (size_t i = 0; i < vec.size(); ++i) {
        auto& [key1, mapped1] = vec[(i+3) % vec.size()];
        answer.erase(key1);
        map.erase(key1);

        VERIFY_TRUE(check_map_equal(map, answer), __LINE__);
    }
}

#if RUN_TEST_1A
void A_rehash_basic() {
    /*
    * Verifies external correctness after call to M1_Review.
    * Note that this does not actually verify if the linked lists are correct,
    * merely verifies that after call to M1_Review, all method calls are still valid,
    * and bucket_count is correct.
    */
    HashMap<int, int> map;
    std::map<int, int> answer;
    std::vector<int> vals;

    VERIFY_TRUE(map.bucket_count() == 10, 28);
    for (size_t M1_Review_count : {10, 20, 20, 15, 1000, 2, 1, 2, 1}) {
       map.rehash(M1_Review_count);
       VERIFY_TRUE(map.bucket_count() == M1_Review_count, __LINE__);

       for (size_t i = 0; i < 18; ++i) {
           VERIFY_TRUE(check_map_equal(map, answer), __LINE__);
           map.erase(i);
           answer.erase(i);
       }

       map.clear();
       answer.clear();
       VERIFY_TRUE(check_map_equal(map, answer), __LINE__);

       for (size_t i = 1; i < 17; ++i) {
           map.insert({i, i});
           answer.insert({i, i});
       }
    }
    bool exception_correct = false;
    try {
        map.rehash(0);
    } catch (const std::out_of_range& e) {
        // Great! You threw the correct exception.
        exception_correct = true;
    } catch (const std::exception& e) {
        // you threw the wrong exception!
    }
    VERIFY_TRUE(exception_correct, __LINE__);
}
#endif

#if RUN_TEST_1B
void B_rehash_correctness_by_time() {
    /*
    * This test tries to check if you hashed elements to the buckets correctly
    * by adding a specific number of elements, and measuring the time it takes
    * to call contains. The idea is that if bucket 0 is supposed to have 10 times
    * the number of elements as bucket 1, calling contains on an element
    * that should be hashed to bucket 0 but is not present should take 10 times
    * longer that calling contains on an element that should be hashed to bucket 1
    * but is not present.
    *
    * Obviously, this is less than perfect, since it's hard to predict how
    * fast your computer is running linked list operations. There are two parameters
    * below. One is called tolerance (let me know if I'm using the term incorrectly)
    * which determines the amount of leeway we give for any differences from the
    * expected time (0.5 means 50% leeway). The second is trials. You can try
    * increasing that to see if you get better results.
    *
    * Play around with this and let me know if you find something interesting,
    * or if you have suggestions to make this test better. There are also
    * cool number theory results, as hashing is inherently an idea from
    * cryptography. Ask Avery if you are curious!
    */
    using K = int;
    using V = int;
    float tolerance = 0.5;      // makes me feel like an engineer, probably using the term wrong
    int trials = 1000;           // increase if necessary, Central Limit Theorem!

    // in case std::hash<K> is different on your compiler.
    auto identity = [](const K& key) { return key; };

    HashMap<K, V, decltype(identity)> map(6, identity);

    // bucket(elements): 0(0), 1(100), 2(1500), 3(500), 4(1500), 5(6000)
    for (int i = 1; i <= 100; ++i) map.insert({6*i+1, i}); // bucket 1
    for (int i = 1; i <= 1500; ++i) map.insert({6*i+2, i}); // bucket 2
    for (int i = 1; i <= 500; ++i) map.insert({6*i+3, i}); // bucket 3
    for (int i = 1; i <= 1500; ++i) map.insert({6*i+4, i}); // bucket 4
    for (int i = 1; i <= 6000; ++i) map.insert({6*i+5, i}); // bucket 5
    std::map<int, float> bucket_times_6;

    for (int i = 0; i < 6; ++i) {
        auto start = clock_type::now();
        for (int j = 0; j < trials; ++j) map.contains(i);
        auto end = clock_type::now();
        auto elapsed = std::chrono::duration_cast<ms>(end - start);
        bucket_times_6.insert({i, elapsed.count()});
    }

    map.rehash(3);
    std::map<int, float> bucket_times_3;
    for (int i = 0; i < 3; ++i) {
        auto start = clock_type::now();
        for (int j = 0; j < trials; ++j) map.contains(i);
        auto end = clock_type::now();
        auto elapsed = std::chrono::duration_cast<ms>(end - start);
        bucket_times_3.insert({i, elapsed.count()});
    }

    map.rehash(2);
    std::map<int, float> bucket_times_2;
    for (int i = 0; i < 2; ++i) {
        auto start = clock_type::now();
        for (int j = 0; j < trials; ++j) map.contains(i);
        auto end = clock_type::now();
        auto elapsed = std::chrono::duration_cast<ms>(end - start);
        bucket_times_2.insert({i, elapsed.count()});
    }

    // Time to pull out the Chinese Remainder Theorem!
    // take the unique bijection Z/6 -> Z/3 x Z/2
    // bucket(elements) mod 6: 0(0), 1(100), 2(1500), 3(500), 4(1500), 5(6000)
    // bucket(elements) mod 3: 0+3(500), 1+4(1600), 2+5(7500)
    // bucket(elements) mod 2: 0+2+4(3000), 1+3+5(7500)

    float ratio6_10 = float(bucket_times_6[1])/(bucket_times_6[0]+1);
    float ratio6_23 = bucket_times_6[2]/bucket_times_6[3]; // expected: 1500/500
    float ratio6_54 = bucket_times_6[5]/bucket_times_6[4]; // expected: 6000/1500
    float ratio3_10 = bucket_times_3[1]/bucket_times_3[0]; // expected: 1600/500
    float ratio3_21 = bucket_times_3[2]/bucket_times_3[1]; // expected: 7500/1600
    float ratio2_10 = bucket_times_2[1]/bucket_times_2[0]; // expected: 7500/3000

    // experiments are noisy, so let's give you some acceptable tolerance
    VERIFY_TRUE(ratio6_10 > 10, __LINE__);
    VERIFY_TRUE(ratio6_23 < (1+tolerance)*1500/500 && ratio6_23 > 1/(1+tolerance)*1500/500, __LINE__);
    VERIFY_TRUE(ratio6_54 < (1+tolerance)*6000/1500 && ratio6_54 > 1/(1+tolerance)*6000/1500, __LINE__);
    VERIFY_TRUE(ratio3_10 < (1+tolerance)*1600/500 && ratio3_10 > 1/(1+tolerance)*1600/500, __LINE__);
    VERIFY_TRUE(ratio3_21 < (1+tolerance)*7500/1600 && ratio3_21 > 1/(1+tolerance)*7500/1600, __LINE__);
    VERIFY_TRUE(ratio2_10 < (1+tolerance)*7500/3000 && ratio2_10 > 1/(1+tolerance)*7500/3000, __LINE__);

    // fun fact: we had to add an -O0 flag because the compiler was optimizing our code
    // a little too well. Turns out that the runtime all of these is the same with optimization (!)
}
#endif

#if RUN_TEST_2A
void A_index_operator() {
    /*
     * Tests the indexing operator to ensure it has the functionality of at(),
     * and also supports auto-insertion.
     */
    std::map<std::string, int> answer;
    HashMap<std::string, int> map;
    VERIFY_TRUE(check_map_equal(map, answer), __LINE__);
    VERIFY_TRUE(answer["Not found"] == map["Not found"], __LINE__);
    for (const auto& [key, value] : vec) {
       answer[key] = value;
       map[key] = value;
       VERIFY_TRUE(check_map_equal(map, answer), __LINE__);
       VERIFY_TRUE(answer["Not found"] == map["Not found"], __LINE__);
    }
    // check for parameter const correctness
    const string c_key = "Not found again";
    VERIFY_TRUE(answer[c_key] == map[c_key], __LINE__);
    VERIFY_TRUE(check_map_equal(map, answer), __LINE__);
}
#endif

#if RUN_TEST_2B
void B_stream_insertion_operator() {
    /*
     * Tries to insert the map into various streams.
     * The format is described on the handout:
     * {Avery:2, Anna:3}
     * {}
     * {Avery:2}
     */
    HashMap<std::string, int> map;

    // Test 1: print empty map
    std::ostringstream oss1;
    oss1 << map;
    VERIFY_TRUE(oss1.str() == "{}", __LINE__);

    // Test 2: print map with a single element
    std::ostringstream oss2;
    map.insert({"Anna", 2});
    oss2 << map;
    VERIFY_TRUE(oss2.str() == "{Anna:2}", __LINE__);

    // Test 3: print map with two elements
    std::ostringstream oss3;
    map.insert({"Avery", 3});
    oss3 << map;
    VERIFY_TRUE(oss3.str() == "{Avery:3, Anna:2}" || oss3.str() == "{Anna:2, Avery:3}", __LINE__);
    auto s = oss3.str();

    // Test 4: print map after a call to erase
    std::ostringstream oss4;
    map.erase("Anna");
    map.at("Avery") = 4;
    oss4 << map;
    VERIFY_TRUE(oss4.str() == "{Avery:4}", __LINE__);

    // Test 5: print map that is key/value pairs reversed
    std::ostringstream oss5;
    HashMap<int, std::string> reverse;
    reverse.insert({3, "Avery"});
    reverse.insert({2, "Anna"});
    oss5 << reverse;
    VERIFY_TRUE(oss5.str() == "{3:Avery, 2:Anna}" || oss5.str() == "{2:Anna, 3:Avery}", __LINE__);

    // Test 6: check ability to chain printing HashMaps to streams.
    std::ostringstream oss;
    oss << "A" << map << 3 << reverse << '\n' << map << map << std::endl;
    VERIFY_TRUE(oss.str() == "A{Avery:4}3{3:Avery, 2:Anna}\n{Avery:4}{Avery:4}\n" ||
                oss.str() == "A{Avery:4}3{2:Anna, 3:Avery}\n{Avery:4}{Avery:4}\n", __LINE__);
}
#endif

#if RUN_TEST_2C
void C_equality_operator() {
    /* Checks functionality of == and != */
    HashMap<int, int> map1(100);
    HashMap<int, int> map2(1);
    VERIFY_TRUE(map1 == map2 && map2 == map1 && map1 == map1 && map2 == map2, __LINE__);

    // at this point we're assuming that all your operations
    // already work, so we're just testing whether == is correct.

    // Insert exact same elements
    for (int i = -1; i < 100; ++i) {
        map1.insert({i, i*i});
        map2.insert({i, i*i});
        VERIFY_TRUE(map1 == map2 && map2 == map1 && map1 == map1 && map2 == map2, __LINE__);
    }

    // Change the two maps' elements in a different order.
    // This means the the maps won't be equal until the very end
    for (int i = 0; i < 99; ++i) {
        map1.at(i) = -i*i;
        map2.at(99-i) = -(99-i)*(99-i);
        map1.rehash(i+1);
        map2.rehash(150+i);
        VERIFY_TRUE(map1 != map2 && map2 != map1 && map1 == map1 && map2 == map2, __LINE__);
    }
    map1.at(99) = -99*99;
    map2.at(0) = 0;
    VERIFY_TRUE(map1 == map2 && map2 == map1 && map1 == map1 && map2 == map2, __LINE__);

    // Try that same thing again, but insert a ton of rehash calls between them.
    for (int i = 0; i < 99; ++i) {
        map1.erase(i);
        map2.erase(99-i);
        map1.rehash(i+150);
        map2.rehash(1+i);
        VERIFY_TRUE(map1 != map2 && map2 != map1 && map1 == map1 && map2 == map2, __LINE__);
    }
    map1.erase(99);
    map2.erase(0);
    map1.rehash(1);
    map2.rehash(1);
    VERIFY_TRUE(map1 == map2 && map2 == map1 && map1 == map1 && map2 == map2, __LINE__);

    // consistency after a call to clear
    map1.clear();
    map2.clear();
    VERIFY_TRUE(map1 == map2 && map2 == map1 && map1 == map1 && map2 == map2, __LINE__);
}
#endif

#if RUN_TEST_2D
void D_const_correctness() {
    /*
     * Checks that your HashMap class is const-correct.
     * The hard part about this test is not getting it to pass.
     * It is to get it to compile!
     */
    std::map<std::string, int> answer;
    HashMap<std::string, int> map1;
    HashMap<std::string, int> map2;
    VERIFY_TRUE(check_map_equal(map1, answer), __LINE__);

    for (const auto& [key, value] : vec) {
       answer[key] = value;
       map1[key] = value;
       map2[key] = value;
       VERIFY_TRUE(check_map_equal(map1, answer), __LINE__);
    }

    // create const references to the maps
    // to see if these const references work correctly
    const auto& c_ref_answer = answer;
    const auto& c_ref_map1 = map1;
    const auto& c_ref_map2 = map2;

    // check that size, empty, load_factor, and bucket_count are const functions
    // already handled in the starter code,
    VERIFY_TRUE(c_ref_map1.size() == c_ref_answer.size(), __LINE__);
    VERIFY_TRUE(c_ref_map1.empty() == c_ref_answer.empty(), __LINE__);
    VERIFY_TRUE(c_ref_map1.load_factor() != 0, __LINE__);
    VERIFY_TRUE(c_ref_map1.bucket_count() != 0, __LINE__);

    // check if we can still check contents of maps as equal
    // even when dealing with const references
    VERIFY_TRUE(check_map_equal(c_ref_map1, c_ref_answer), __LINE__);

    VERIFY_TRUE(answer.empty() == c_ref_map1.empty(), __LINE__);
    VERIFY_TRUE(answer.size() == c_ref_map1.size(), __LINE__);

    for (const auto& [key, mapped] : answer) {
        VERIFY_TRUE(map1.contains(key), __LINE__);
        VERIFY_TRUE(map1.at(key) == mapped, __LINE__);
    }

    // Check const correctness of == and != operator 
    map1.erase("A");
    map2.erase("A");
    map1.rehash(map1.bucket_count() * 2);
    map2.rehash(map2.bucket_count() * 2);
    VERIFY_TRUE(map1 == map2 && map2 == map1 && map1 == map1 && map2 == map2, __LINE__);
    VERIFY_TRUE(c_ref_map1 == map2 && map2 == c_ref_map1 && c_ref_map1 == c_ref_map1, __LINE__);
    VERIFY_TRUE(c_ref_map2 == map1 && map1 == c_ref_map2 && c_ref_map2 == c_ref_map2, __LINE__);
    VERIFY_TRUE(c_ref_map2 == c_ref_map1 && c_ref_map1 == c_ref_map2, __LINE__);

    std::ostringstream oss;
    oss << c_ref_map1;
    auto size = oss.str().size();
    oss << c_ref_map2 << c_ref_map1 << c_ref_map2;
    VERIFY_TRUE(oss.str().size() == 4*size, __LINE__);
}
#endif

#if RUN_TEST_3A
void A_copy_ctor_assignment() {
    /* Checks correctness of copy ctor and copy assignment operator */
    HashMap<std::string, int> map;

    for (const auto& kv_pair : vec) {
        map.insert(kv_pair);
    }

    HashMap<std::string, int> copy_constructed{map};
    HashMap<std::string, int> copy_assigned;
    copy_assigned = map;
    VERIFY_TRUE(map == copy_constructed, __LINE__);
    VERIFY_TRUE(map == copy_assigned, __LINE__);

    map.erase("A");
    // check that map and its copies are independent
    VERIFY_TRUE(map != copy_constructed, __LINE__);
    VERIFY_TRUE(map != copy_assigned, __LINE__);
    VERIFY_TRUE(copy_constructed == copy_assigned, __LINE__);
    
    map.clear();
    VERIFY_TRUE(map != copy_constructed, __LINE__);
    VERIFY_TRUE(map != copy_assigned, __LINE__);
    VERIFY_TRUE(copy_constructed == copy_assigned, __LINE__);

    // make more copies so we can test self-assignment
    auto original_copy_constructed(copy_constructed);
    HashMap<std::string, int> original_copy_assigned;
    original_copy_assigned = copy_assigned;

    // suppress the really annoying warnings
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wself-assign-overloaded" 

    // start doing weird things to the map
    copy_constructed = copy_constructed;
    VERIFY_TRUE(copy_constructed == original_copy_constructed, __LINE__);
    copy_assigned = (copy_assigned = copy_assigned) = copy_assigned;
    VERIFY_TRUE(copy_assigned == original_copy_assigned, __LINE__);
    map = map = map = map;
    copy_assigned = map = map = copy_assigned = map;

    // Both maps should be empty here.
    VERIFY_TRUE(map.empty(), __LINE__);
    VERIFY_TRUE(copy_assigned.empty(), __LINE__);
    #pragma GCC diagnostic pop
    // your code could crash at this line due to memory problems!
}
#endif

#if RUN_TEST_3B
void B_move_ctor_assignment() {
    /* Checks correctness of move ctor and move assignment operator */
    HashMap<std::string, int> map1;
    HashMap<std::string, int> map2;
    HashMap<std::string, int> map_copy;

    for (const auto& kv_pair : vec) {
        map1.insert(kv_pair);
        map2.insert(kv_pair);
        map_copy.insert(kv_pair);
    }
    VERIFY_TRUE(map1 == map_copy, __LINE__);
    VERIFY_TRUE(std::move(map1) == map_copy, __LINE__);
    HashMap<std::string, int> move_constructed{std::move(map1)}; 
    HashMap<std::string, int> move_assigned;

    move_assigned = std::move(map2);
    VERIFY_TRUE(map_copy == move_constructed, __LINE__);
    VERIFY_TRUE(map_copy == move_assigned, __LINE__);
    map1 = move_constructed;                       
    VERIFY_TRUE(map1 == move_constructed, __LINE__);


    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wself-move" // suppress annoying warnings about self-assignment

    // let's start doing weird things to our map
    map1 = std::move(map1);
    (map1 = std::move(map1)) = map1 = std::move(map1 = map1 = std::move(map1));
    VERIFY_TRUE(map1 == move_constructed, __LINE__);

    // edge case with empty map
    HashMap<std::string, int> empty1;
    HashMap<std::string, int> empty2;
    empty1 = std::move(empty1);
    VERIFY_TRUE(empty1 == empty2, __LINE__);
    empty2 = std::move(map1);
    VERIFY_TRUE(empty2 == move_constructed, __LINE__);

    // verify that moved containers can still be reassigned
    map1 = std::move(move_assigned);
    empty1 = std::move(map1);
    VERIFY_TRUE(empty1 == map_copy, __LINE__);
    #pragma GCC diagnostic pop

    }
#endif

#if RUN_TEST_3C
void C_move_time() {
    /* Checks the efficiency of the move operations (must be much faster than copy) */

    struct FunctorZero {
        size_t operator()(const int& v) const {
            (void) v;
            return 0;
        }
    };
    FunctorZero zero;
    HashMap<int, int, decltype(zero)> map1(2, zero);
    HashMap<int, int, decltype(zero)> map2(2, zero);
    HashMap<int, int, decltype(zero)> map_copy(2, zero);
    std::map<int, int> answer;

    for (size_t i = 0; i < 1000; ++i) {
        map1.insert({i, i*i});
        map2.insert({i, i*i});
        answer.insert({i, i*i});
    }
    {
        auto start = clock_type::now();
        HashMap<int, int, decltype(zero)> move_constructed = std::move(map1);
        auto end = clock_type::now();
        auto elapsed = std::chrono::duration_cast<ms>(end - start);
        VERIFY_TRUE(check_map_equal(move_constructed,answer), __LINE__);
        VERIFY_TRUE(elapsed.count() < 10000, __LINE__);
    }

    {
        auto start = clock_type::now();
        HashMap<int, int, decltype(zero)> move_assigned;
        move_assigned = std::move(map2);
        auto end = clock_type::now();
        auto elapsed = std::chrono::duration_cast<ms>(end - start);
        VERIFY_TRUE(check_map_equal(move_assigned,answer), __LINE__);
        VERIFY_TRUE(elapsed.count() < 10000, __LINE__);
    }
}
#endif

#if RUN_TEST_6A
void A_iterator_for_each_basic() {
    /* Tests whether iterators are supported via a simple for-each loop
     * Uses begin() and end() of your HashMap, in addition to
     * the ctor and operators =, !=, and ++ of your iterator.
     */
    std::set<std::pair<int, int> > questions {
        {1, 1}, {2, 2}, {30, 30}, {140, 140}, {21, 21}
    };

    HashMap<int, int> map10;            // can your iterator traverse normal use case?
    for (const auto& pair : questions) {
        map10.insert(pair);
    }
    std::set<std::pair<int, int> > answers10;
    for (const auto& pair : map10) VERIFY_TRUE(answers10.insert(pair).second == true, __LINE__);

    VERIFY_TRUE(questions == answers10, __LINE__);
}
#endif

#if RUN_TEST_6B
void B_iterator_for_each_edge() {
    /* Tests a few edge cases for your iterator, such as checking the bounds */
    std::set<std::pair<int, int> > questions {
        {0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}
    };

    HashMap<int, int> map1(1);      // one bucket with all the elements
    HashMap<int, int> map5(5);      // exactly one per bucket
    HashMap<int, int> map10(100);   // a lot of empty buckets
    HashMap<int, int> empty;        // won't add anything to this one

    for (const auto& pair : questions) {
        map1.insert(pair);
        map5.insert(pair);
        map10.insert(pair);
    }
    std::set<std::pair<int, int> > answers1, answers5, answers10;
    for (const auto& pair : map1) VERIFY_TRUE(answers1.insert(pair).second == true, __LINE__);
    for (const auto& pair : map5) VERIFY_TRUE(answers5.insert(pair).second == true, __LINE__);
    for (const auto& pair : map10) VERIFY_TRUE(answers10.insert(pair).second == true, __LINE__);
    for (const auto& pair __attribute__((unused)) : empty) VERIFY_TRUE(false, __LINE__); // this should not run!

    VERIFY_TRUE(questions == answers1, __LINE__);
    VERIFY_TRUE(questions == answers5, __LINE__);
    VERIFY_TRUE(questions == answers10, __LINE__);
}
#endif

#if RUN_TEST_6C
void C_iterator_operators() {
    /* Tests the more advanced operators, that are required
     * since the iterator can be a forward iterator */
    std::set<std::pair<int, int> > questions {
        {1, 1}, {2, 2}, {3, 3}
    };
    // Note to reader: yes, I spent so much time writing these awesome test cases
    // and then decided to make this part optional. What a great use of my spring break.
    // It's not like I have anything else to do, right?


    HashMap<int, int> map;            // can your iterator traverse normal use case?
    for (const auto& pair : questions) {
        map.insert(pair);
    }

    // note: we make no assumptions about which specifc element is in which order!
    auto iter = map.begin();                    // iter->0th element
    VERIFY_TRUE((*iter).first == (*iter).second, __LINE__);   // behavior of * operator
    VERIFY_TRUE(iter->first == iter->second, __LINE__);       // behavior of -> operator
    VERIFY_TRUE(iter == iter, __LINE__);                      // behavior of == operator
    VERIFY_TRUE(!(iter != iter), __LINE__);                   // behavior of != operator

    (*iter).second = -1;                        // behavior of * operator as an l-value
    VERIFY_TRUE((*iter).second == -1, __LINE__);    // behavior of * operator as an r-value
    iter->second = -2;                          // behavior of -> operator as an l-value
    VERIFY_TRUE(iter->second == -2, __LINE__);      // behavior of -> operator as an r-value

    // verify correct prefix/postfix behavior (this was very tedious)
    HashMap<int, int>::iterator iter0 = iter; // just to prove why type aliases are helpful
    auto iter1 = ++iter;                      // though auto usually works as well
    auto iter2 = ++iter;
    auto iter3 = ++iter;
    VERIFY_TRUE(iter == map.end(), __LINE__);
    iter = iter0;                       // iter->0
    auto& iter_ref = ++iter;            // iter/iter_ref->1
    VERIFY_TRUE(iter_ref == iter1, __LINE__);
    auto iter_ref_copy = ++iter_ref;    // iter_ref_copy->2, iter/iter_ref->2
    VERIFY_TRUE(iter_ref_copy == iter2, __LINE__);
    VERIFY_TRUE(iter_ref == iter2, __LINE__);

    auto iter_post = iter++;            // iter/iter_ref->3, iter_post->2
    VERIFY_TRUE(iter_post == iter2, __LINE__);
    VERIFY_TRUE(iter == iter3, __LINE__);
    iter_ref = map.begin();             // iter/iter_ref->0
    VERIFY_TRUE(iter == iter0, __LINE__);

    // Big LOL - see if you can actually trace the ++++++ operator.
    auto iter_chain_pre = ++++++iter;   // iter_chain_pre->3, iter/iter_ref->3
    VERIFY_TRUE(iter == iter3, __LINE__);
    VERIFY_TRUE(iter_chain_pre == iter3, __LINE__);
    iter_ref = map.begin();             // iter/iter_ref->0
    auto iter_chain_post = iter++++++;  // iter/iter_ref->1, iter_chain_post->0
    VERIFY_TRUE(iter == iter1, __LINE__);
    VERIFY_TRUE(iter_chain_post == iter0, __LINE__);
    // presumably if you pass the above ones, you probably have it working
    // so I'm not gonna think about what ++iter++++ would be
}
#endif 

#if RUN_TEST_6D
void D_iterator_algorithm() {
    /* Fully stresses your iterators by using an STL algorithm on them */
    HashMap<int, int> map;
    std::map<int, int> answer;

    for (int i = -17; i < 10; ++i) {
        map.insert({i, i*i});
    }

    std::copy(map.begin(), map.end(), std::inserter(answer, answer.begin()));
    VERIFY_TRUE(check_map_equal(map, answer), __LINE__);
    answer.clear();

    const auto& c_map = map;
    std::copy(c_map.begin(), c_map.end(), std::inserter(answer, answer.begin()));
    VERIFY_TRUE(check_map_equal(map, answer), __LINE__);
}
#endif

#if RUN_TEST_6E
void E_const_iterator() {
    /* Tests the const-correctness of your iterator class by asking for const_iterators */
    std::set<std::pair<int, int> > questions {
        {1, 1}, {2, 2}, {3, 3}
    };

    /* testing const_iterator (iterator to const std::pair) */
    HashMap<int, int> map;
    for (const auto& pair : questions) map.insert(pair);
    const auto& const_map = map;
    std::set<std::pair<int, int> > answers;
    for (const auto& pair : const_map) VERIFY_TRUE(answers.insert(pair).second == true, __LINE__);
    VERIFY_TRUE(questions == answers, __LINE__);

    HashMap<int, int>::const_iterator iter = const_map.begin();

    VERIFY_TRUE((*iter).first == (*iter).second, __LINE__);   // behavior of * operator
    VERIFY_TRUE(iter->first == iter->second, __LINE__);       // behavior of -> operator
    VERIFY_TRUE(iter == iter, __LINE__);                      // behavior of == operator
    VERIFY_TRUE(!(iter != iter), __LINE__);                   // behavior of != operator

    VERIFY_TRUE(iter->second == (*iter).second, __LINE__);
    auto iter1 = ++iter;
    auto iter2 = ++iter;
    auto iter3 = iter++;
    VERIFY_TRUE(iter == const_map.end(), __LINE__);
    VERIFY_TRUE(iter3 == iter2, __LINE__);
    VERIFY_TRUE(iter1 != iter2, __LINE__);

    /* We could have the entire operator from 1C here, though that feels unnecessary */
}
#endif

#if RUN_TEST_6F
void F_iterator_const_correctness() {
    /* Test the distinction between const iterator and const_iterator */
    std::set<std::pair<int, int> > questions {
        {1, 1}, {2, 2}, {3, 3}
    };

    HashMap<int, int> map;
    for (const auto& pair : questions) map.insert(pair);

    /* test behavior of const iterator */
    HashMap<int, int>::iterator iter = map.begin();
    const HashMap<int, int>::iterator c_iter = map.begin();
    const HashMap<int, int>::iterator& copy = iter;
    const HashMap<int, int>::iterator& copy_next = ++iter;

    VERIFY_TRUE(map.begin() == c_iter, __LINE__);
    VERIFY_TRUE(copy == iter, __LINE__);
    VERIFY_TRUE(copy_next == iter, __LINE__);
    VERIFY_TRUE(c_iter != iter, __LINE__);

    // the iterator is const, but the stuff the iterator points to is not const.
    (*c_iter).second = -1;                                   // behavior of * operator as an l-value
    VERIFY_TRUE((*c_iter).second == -1, __LINE__);              // behavior of * operator as an r-value
    c_iter->second = -2;                                     // behavior of -> operator as an l-value
    VERIFY_TRUE(c_iter->second == -2, __LINE__);                // behavior of -> operator as an r-value

    // these should not compile:
    // *iter = {0, 0};  // *iter is a std::pair<const K, M>, since K is const, = is deleted
    // ++c_iter;        // ++ is non-const

    VERIFY_TRUE(++++iter == map.end(), __LINE__);

    /* test behavior of const const_iterator */
    const auto& const_map = map;
    HashMap<int, int>::const_iterator const_iter = const_map.begin();
    const HashMap<int, int>::const_iterator c_const_iter_next = ++const_map.begin();
    const HashMap<int, int>::const_iterator c_const_iter = const_map.begin();

    // the key here is that these should compile.
    ++const_iter;
    VERIFY_TRUE((*c_const_iter).second == -2, __LINE__);
    VERIFY_TRUE(c_const_iter->second == -2, __LINE__);
    VERIFY_TRUE(const_iter == c_const_iter_next, __LINE__);
    VERIFY_TRUE(c_const_iter == const_map.begin(), __LINE__);

    // these should not compile:
    // ++c_const_iter;
    // c_const_iter->second = 2;
    // const_iter->second = 2;
}
#endif

#if RUN_TEST_5A
void A_initializer_list_ctor() {
    /* Tests initializer_list via a simple example */
    std::map<std::string, int> answer {
        {"A", 3}, {"B", 2}, {"C", 1}, {"A", -5}, {"B", 3}, {"A", 5}, {"C", 1}
    };

    HashMap<std::string, int> map {
        {"A", 3}, {"B", 2}, {"C", 1}, {"A", -5}, {"B", 3}, {"A", 5}, {"C", 1}
    };

    VERIFY_TRUE(check_map_equal(map, answer), __LINE__);

}
#endif

#if RUN_TEST_5B
void B_range_ctor() {
    /* Simple test of the range ctor taking in two iterators to another collection */
    std::vector<std::pair<std::string, int>> values {
        {"Ignore me", 100}, {"A", 3}, {"B", 2}, {"C", 1}, {"A", -5}, {"B", 3}, {"A", 5}, {"C", 1}
    };
    std::map<std::string, int> answer {values.begin()++, values.end()};
    HashMap<std::string, int> map {values.begin()++, values.end()};

    VERIFY_TRUE(check_map_equal(map, answer), __LINE__);
}
#endif


using std::cout;
using std::endl;
int run_starter_code_tests();
int run_milestone1_tests();
int run_milestone2_tests();
int run_milestone3_tests();
int run_milestone5_tests();
int run_milestone6_tests();

template <typename T>
int run_test(const T& test, const string& test_name) {
    try {
        test();
        cout << "Test "  << std::setw(30) << left << test_name  << right << " PASS " << endl;
        return 1;
    } catch (const VerifyTrueAssertionFailure& e)  {
        cout << "Test "  << std::setw(30) << left << test_name << right 
             << " FAIL: VERIFY_TRUE assertion failure at line number " << e.line 
             << " in file tests.cpp" << endl;
    } catch (const std::exception& e) {
        cout << "Test "  << std::setw(30) << left << test_name << right 
             << " FAIL due to thrown exception: " << e.what() << endl;
    } catch (const std::string& e) {
        cout << "Test "  << std::setw(30) << left << test_name  << right 
        << " FAIL with string " << e << endl;
    } catch (const char *& e) {
        cout << "Test "  << std::setw(30) << left << test_name  << right 
        << " FAIL with string " << e << endl;
    } 
    return 0;
}

void skip_test(const string& test_name) {
    cout << "Test "  << std::setw(30) << left << test_name  << right << " SKIP " << endl;
}

void run_test_harness() {
    cout << endl;
    cout << "----- CS 106L SIMPLE TEST HARNESS -----" << endl;
    cout << "Written by Avery Wang (2019-2020 lecturer)" << endl << endl;
    int required_pass = 0;
    int bonus_pass = 0;
    cout << "----- Starter Code Tests (Provided) -----" << endl;
    required_pass += run_starter_code_tests();
    cout << endl << "----- Milestone 1 Tests (Required) -----" << endl;
    required_pass += run_milestone1_tests();
    cout << endl << "----- Milestone 2 Tests (Required) -----" << endl;
    required_pass += run_milestone2_tests();
    cout << endl << "----- Milestone 3 Tests (Required) -----" << endl;
    required_pass += run_milestone3_tests();
    cout << endl << "----- Milestone 4 Tests (Required) -----" << endl;
    cout << "(10 short answers graded manually)" << endl;
    cout << endl << "----- Milestone 5 Tests (Optional) -----" << endl;
    bonus_pass += run_milestone5_tests();
    cout << endl << "----- Milestone 6 Tests (Optional) -----" << endl;
    bonus_pass +=  run_milestone6_tests();
    cout << endl << "----- Test Harness Summary -----" << endl;
    cout << "Required tests: " << required_pass << "/16 (excluding short answers)" << endl;
    cout << "Optional tests: " << bonus_pass << "/8" << endl;
    if (required_pass <= 7) {
        cout << "Still getting started! " << endl;
    } else if (required_pass <= 9) {
        cout << "You are making progress! Keep going! " << endl;
    } else if (required_pass <= 12) {
        cout << "Halfway there! " << endl;
    } else if (required_pass <= 15) {
        cout << "Super close! " << endl;
    } else {
        cout << "You passed all required tests! Great job!" << endl;
    }
    if (required_pass < 16) {
        cout << "Some tests were failed or skipped. " << endl;
        cout << "If stuck, try adding a map.debug() call before a VERIFY_TRUE." << endl;
    }
    if (bonus_pass == 8) {
        cout << "It's students like you who are so interested in C++ that you go way above and beyond " << endl;
        cout << "the assignment that make teaching such a joy. It's our very last quarter teaching, and we " << endl;
        cout << "just want to say in this hidden message, thank you for being awesome." << endl; 
    } else if (bonus_pass >= 4) {
        cout << "You even succeeded in some extensions! That's awesome." << endl;
    } else if (bonus_pass > 0) {
        cout << "Wow! You've clearly invested a lot of time in extensions. You're amazing" << endl;
    }
    cout << endl << "----- End of Test Harness -----" << endl;
}

int run_starter_code_tests() {
    int passed = 0;
    passed += run_test(A_basic, "A_basic");
    passed += run_test(B_insert, "B_insert");
    passed += run_test(C_clear, "C_clear");
    passed += run_test(D_at, "D_at");
    passed += run_test(E_custom_bucket_count, "E_custom_bucket_count");
    passed += run_test(F_custom_hash_function, "F_custom_hash_function");
    passed += run_test(G_erase, "G_erase");
    return passed;
}

int run_milestone1_tests() {
    int passed = 0;
    #if RUN_TEST_1A
    passed += run_test(A_rehash_basic, "A_rehash_basic");
    #else
    skip_test("A_rehash_basic");
    #endif

    #if RUN_TEST_1B
    passed += run_test(B_rehash_correctness_by_time, "B_rehash_correctness_by_time");
    #else
    skip_test("B_rehash_correctness_by_time");
    #endif
    return passed;
}

int run_milestone2_tests() {

    int passed = 0;
    #if RUN_TEST_2A
    passed += run_test(A_index_operator, "A_index_operator");
    #else
    skip_test("A_index_operator");
    #endif

    #if RUN_TEST_2B
    passed += run_test(B_stream_insertion_operator, "B_stream_insertion_operator");
    #else
    skip_test("B_stream_insertion_operator");
    #endif

     #if RUN_TEST_2C
    passed += run_test(C_equality_operator, "C_equality_operator");
    #else
    skip_test("C_equality_operator");
    #endif

     #if RUN_TEST_2D
    passed += run_test(D_const_correctness, "D_const_correctness");
    #else
    skip_test("D_const_correctness");
    #endif
    return passed;
}

int run_milestone3_tests() {
    int passed = 0;
    #if RUN_TEST_3A
    passed += run_test(A_copy_ctor_assignment, "A_copy_ctor_assignment");
    #else
    skip_test("A_copy_ctor_assignment");
    #endif

    #if RUN_TEST_3B
    passed += run_test(B_move_ctor_assignment, "B_move_ctor_assignment");
    #else
    skip_test("B_move_ctor_assignment");
    #endif

    #if RUN_TEST_3C
    passed += run_test(C_move_time, "C_move_time");
    #else
    skip_test("C_move_time");
    #endif
    
    return passed;
}



int run_milestone5_tests() {
    int passed = 0;
    #if RUN_TEST_5A
    passed += run_test(A_initializer_list_ctor, "A_initializer_list_ctor");
    #else
    skip_test("A_initializer_list_ctor");
    #endif

    #if RUN_TEST_5B
    passed += run_test(B_range_ctor, "B_range_ctor");
    #else
    skip_test("B_range_ctor");
    #endif
    
    return passed;
}

int run_milestone6_tests() {
    int passed = 0;
    #if RUN_TEST_6A
    passed += run_test(A_iterator_for_each_basic, "A_iterator_for_each_basic");
    #else
    skip_test("A_iterator_for_each_basic");
    #endif

    #if RUN_TEST_6B
    passed += run_test(B_iterator_for_each_edge, "B_iterator_for_each_edge");
    #else
    skip_test("B_iterator_for_each_edge");
    #endif

    #if RUN_TEST_6C
    passed += run_test(C_iterator_operators, "C_iterator_operators");
    #else
    skip_test("C_iterator_operators");
    #endif

    #if RUN_TEST_6D
    passed += run_test(D_iterator_algorithm, "D_iterator_algorithm");
    #else
    skip_test("D_iterator_algorithm");
    #endif

    #if RUN_TEST_6E
    passed += run_test(E_const_iterator, "E_const_iterator");
    #else
    skip_test("E_const_iterator");
    #endif

    #if RUN_TEST_6F
    passed += run_test(F_iterator_const_correctness, "F_iterator_const_correctness");
    #else
    skip_test("F_iterator_const_correctness");
    #endif
    
    return passed;
}
