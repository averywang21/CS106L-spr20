/*
 * STL HashMap Test Harness
 * Created by Avery Wang (lecturer for 2019-2020 - awvry952@stanford.edu)
 */
#include "hashmap.h"
#include "test_settings"

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
template <typename Map1, typename Map2> bool check_equal(Map1& map, Map2& answer) {
    if (answer.empty() != map.empty() || answer.size() != map.size()) return false;

    for (const auto& [key, mapped] : answer) {
       if(map.contains(key) == false || map.at(key) != mapped) return false;
    }
    return true;
}

void CHECK_EQUAL(bool condition, int id) {
    if (!condition) {
        std::ostringstream oss;
        oss << "CHECK_EQUAL assertion incorrect at line number " << id << " in file tests.cpp." << id;
        throw oss.str();
    }
}


// ----------------------------------------------------------------------------------------------
/* Starter Code Test Cases (DO NOT EDIT) */

void A_basic() {
   std::map<std::string, int> answer;
   HashMap<std::string, int> map;
   CHECK_EQUAL(check_equal(map, answer), __LINE__);
   CHECK_EQUAL(map.bucket_count() == 10, __LINE__);
}
void B_insert() {
   std::map<std::string, int> answer;
   HashMap<std::string, int> map;
   CHECK_EQUAL(check_equal(map, answer), __LINE__);
   CHECK_EQUAL(map.bucket_count() == 10, __LINE__);

   for (const auto& kv_pair : vec) {
       answer.insert(kv_pair);
       map.insert(kv_pair);
       CHECK_EQUAL(check_equal(map, answer), __LINE__);
   }

   CHECK_EQUAL(map.bucket_count() == 10, __LINE__);
}

void C_clear() {
    std::map<std::string, int> answer;
    HashMap<std::string, int> map;

    for (size_t j = 0; j < 3; ++j) {
       for (const auto& kv_pair : vec) {
           answer.insert(kv_pair);
           map.insert(kv_pair);
       }

       answer.clear();
       map.clear();

       CHECK_EQUAL(check_equal(map, answer), __LINE__);
    }
}
void D_at_test() {
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
    CHECK_EQUAL(answer.at("A") == -42, __LINE__);
    CHECK_EQUAL(answer.at("B") == 137, __LINE__);
    CHECK_EQUAL(answer.at("C") == -42, __LINE__);

    // verify that we can save the reference returned by at.
    auto copy = answer.at("A");
    auto& ref = answer.at("B");
    copy = 0;
    ref = 0;
    CHECK_EQUAL(answer.at("A") == -42, __LINE__);
    CHECK_EQUAL(answer.at("B") == 0, __LINE__);

    // verify that correct exceptions are thrown
    HashMap<std::string, int> map2;
    bool correct_exception = false;
    try {
        map2.at("Exists") = 5;
    } catch (const std::out_of_range& e) {
        correct_exception = true;
    } 
    CHECK_EQUAL(correct_exception, __LINE__);
    map2.insert({"Exists", 4});
    CHECK_EQUAL(map2.contains("Exists"), __LINE__);
    CHECK_EQUAL(!map2.contains("Does not exist"), __LINE__);
    correct_exception = true;
    try {
        map2.at("Does not exist") = 5;
    } catch (const std::out_of_range& e) {
        correct_exception = true;
    } 
    CHECK_EQUAL(correct_exception, __LINE__);
}



void E_custom_bucket_count() {
    HashMap<int, int> many_buckets(10000);
    HashMap<int, int> one_bucket(1);
    std::map<int, int> answer;

    for (int i = 0; i < 100; ++i) {
       many_buckets.insert({i, -i});
       one_bucket.insert({i, -i});
       answer.insert({i, -i});
    }

    CHECK_EQUAL(check_equal(many_buckets, answer), __LINE__);
    CHECK_EQUAL(check_equal(one_bucket, answer), __LINE__);

    CHECK_EQUAL(many_buckets.bucket_count() == 10000, __LINE__);
    CHECK_EQUAL(one_bucket.bucket_count() == 1, __LINE__);

    float epsilon = 0.001;
    CHECK_EQUAL(many_buckets.load_factor() - 0.01 < epsilon, __LINE__);
    CHECK_EQUAL(one_bucket.load_factor() - 100 < epsilon, __LINE__);
}
void F_custom_hash_function() {
    /*
    * Tests constructor taking in a num_buckets and hash function.
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
       CHECK_EQUAL(check_equal(map, answer), __LINE__);
    }
}
#if RUN_TEST_1A
void A_erase() {
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
       CHECK_EQUAL(check_equal(map, answer), __LINE__);

       answer.erase("Not a key");
       map.erase("Not a key");
       CHECK_EQUAL(check_equal(map, answer), __LINE__);

       answer.insert(pair2);
       map.insert(pair2);
   }

   // remove one at a time, until map is empty
   for (size_t i = 0; i < vec.size(); ++i) {
       auto& [key1, mapped1] = vec[(i+3) % vec.size()];
       answer.erase(key1);
       map.erase(key1);

       CHECK_EQUAL(check_equal(map, answer), __LINE__);
   }
}
#endif

#if RUN_TEST_1B
void B_rehash_basic() {
    HashMap<int, int> map;
    std::map<int, int> answer;
    std::vector<int> vals;

    CHECK_EQUAL(map.bucket_count() == 10, 28);
    for (size_t M1_Review_count : {10, 20, 20, 15, 1000, 2, 1, 2, 1}) {
       map.rehash(M1_Review_count);
       CHECK_EQUAL(map.bucket_count() == M1_Review_count, __LINE__);

       for (size_t i = 0; i < 18; ++i) {
           CHECK_EQUAL(check_equal(map, answer), __LINE__);
           map.erase(i);
           answer.erase(i);
       }

       map.clear();
       answer.clear();
       CHECK_EQUAL(check_equal(map, answer), __LINE__);

       for (size_t i = 1; i < 17; ++i) {
           map.insert({i, i});
           answer.insert({i, i});
       }
    }
    try {
        map.rehash(0);
    } catch (const std::out_of_range& e) {
        // Great! You threw the correct exception.
    } catch (...) {
        // You didn't throw the correct exception here!
        CHECK_EQUAL(false, __LINE__);
    }
}
#endif

#if RUN_TEST_1C
void C_rehash_correctness_by_time() {
   using K = int;
   using V = int;
   float tolerance = 0.5;      // makes me feel like an engineer, probably using the term wrong
   int trials = 10;           // increase if necessary, Central Limit Theorem!

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
   CHECK_EQUAL(ratio6_10 > 10, __LINE__);
   CHECK_EQUAL(ratio6_23 < (1+tolerance)*1500/500 && ratio6_23 > 1/(1+tolerance)*1500/500, __LINE__);
   CHECK_EQUAL(ratio6_54 < (1+tolerance)*6000/1500 && ratio6_54 > 1/(1+tolerance)*6000/1500, __LINE__);
   CHECK_EQUAL(ratio3_10 < (1+tolerance)*1600/500 && ratio3_10 > 1/(1+tolerance)*1600/500, __LINE__);
   CHECK_EQUAL(ratio3_21 < (1+tolerance)*7500/1600 && ratio3_21 > 1/(1+tolerance)*7500/1600, __LINE__);
   CHECK_EQUAL(ratio2_10 < (1+tolerance)*7500/3000 && ratio2_10 > 1/(1+tolerance)*7500/3000, __LINE__);

   // fun fact: we had to add an -O0 flag because the compiler was optimizing our code
   // a little too well. Turns out that the runtime all of these is the same with optimization (!)
}
#endif

#if RUN_TEST_2A
void A_index_operator() {
    std::map<std::string, int> answer;
    HashMap<std::string, int> map;
    CHECK_EQUAL(check_equal(map, answer), 0);
    CHECK_EQUAL(answer["Not found"] == map["Not found"], __LINE__);
    for (const auto& [key, value] : vec) {
       answer[key] = value;
       map[key] = value;
       CHECK_EQUAL(check_equal(map, answer), __LINE__);
    }
    CHECK_EQUAL(answer["Not found"] == map["Not found"], __LINE__);
    CHECK_EQUAL(answer["Not found again"] == map["Not found again"], __LINE__);
}
#endif

#if RUN_TEST_2B
void B_stream_insertion_operator() {
    HashMap<std::string, int> map;

    std::ostringstream oss1;
    oss1 << map;
    CHECK_EQUAL(oss1.str() == "{}", __LINE__);

    std::ostringstream oss2;
    map.insert({"Avery", 2});
    oss2 << map;
    CHECK_EQUAL(oss2.str() == "{Avery:2}", __LINE__);

    std::ostringstream oss3;
    map.insert({"Anna", 3});
    oss3 << map;
    CHECK_EQUAL(oss3.str() == "{Anna:3, Avery:2}" || oss3.str() == "{Avery:2, Anna:3}", __LINE__);
    auto s = oss3.str();

    std::ostringstream oss;
    oss << map << map << map << map;
    CHECK_EQUAL(oss.str().size() == 4*s.size(), __LINE__);
}
#endif

#if RUN_TEST_2C
void C_equality_operator() {
    HashMap<int, int> map1(100);
    HashMap<int, int> map2(1);
    CHECK_EQUAL(map1 == map2 && map2 == map1 && map1 == map1 && map2 == map2, __LINE__);

    // at this point we're assuming that all your operations
    // already work, so we're just testing whether == is correct.
    for (int i = 0; i < 100; ++i) {
        map1.insert({i, i*i});
        map2.insert({i, i*i});
        CHECK_EQUAL(map1 == map2 && map2 == map1 && map1 == map1 && map2 == map2, __LINE__);
    }

    for (int i = 0; i < 99; ++i) {
        map1.at(i) = -i*i;
        map2.at(99-i) = -(99-i)*(99-i);
        map1.rehash(i+1);
        map2.rehash(150+i);
        CHECK_EQUAL(map1 != map2 && map2 != map1 && map1 == map1 && map2 == map2, __LINE__);
    }
    map1.at(99) = -99*99;
    map2.at(0) = 0;
    CHECK_EQUAL(map1 == map2 && map2 == map1 && map1 == map1 && map2 == map2, __LINE__);
    for (int i = 0; i < 99; ++i) {
        map1.erase(i);
        map2.erase(99-i);
        map1.rehash(i+150);
        map2.rehash(1+i);
        CHECK_EQUAL(map1 != map2 && map2 != map1 && map1 == map1 && map2 == map2, __LINE__);
    }
    map1.erase(99);
    map2.erase(0);
    map1.rehash(1);
    map2.rehash(1);
    CHECK_EQUAL(map1 == map2 && map2 == map1 && map1 == map1 && map2 == map2, __LINE__);
}
#endif

#if RUN_TEST_2D
void D_const_correctness() {
    std::map<std::string, int> answer;
    HashMap<std::string, int> map1;
    HashMap<std::string, int> map2;
    CHECK_EQUAL(check_equal(map1, answer), __LINE__);

    for (const auto& [key, value] : vec) {
       answer[key] = value;
       map1[key] = value;
       map2[key] = value;
       CHECK_EQUAL(check_equal(map1, answer), __LINE__);
    }

    const auto& c_ref_answer = answer;
    const auto& c_ref_map1 = map1;
    const auto& c_ref_map2 = map2;

    CHECK_EQUAL(c_ref_map1.size() == c_ref_answer.size(), __LINE__);
    CHECK_EQUAL(c_ref_map1.empty() == c_ref_answer.empty(), __LINE__);
    CHECK_EQUAL(c_ref_map1.load_factor() != 0, __LINE__);
    CHECK_EQUAL(c_ref_map1.bucket_count() != 0, __LINE__);

    CHECK_EQUAL(check_equal(c_ref_map1, c_ref_answer), __LINE__);

    CHECK_EQUAL(answer.empty() == c_ref_map1.empty(), __LINE__);
    CHECK_EQUAL(answer.size() == c_ref_map1.size(), __LINE__);

    for (const auto& [key, mapped] : answer) {
        CHECK_EQUAL(map1.contains(key), __LINE__);
        CHECK_EQUAL(map1.at(key) == mapped, __LINE__);
    }
    CHECK_EQUAL(map1 == map2 && map2 == map1 && map1 == map1 && map2 == map2, __LINE__);
    CHECK_EQUAL(c_ref_map1 == map2 && map2 == c_ref_map1 && c_ref_map1 == c_ref_map1, __LINE__);
    CHECK_EQUAL(c_ref_map2 == map1 && map1 == c_ref_map2 && c_ref_map2 == c_ref_map2, __LINE__);
    CHECK_EQUAL(c_ref_map2 == c_ref_map1 && c_ref_map1 == c_ref_map2, __LINE__);

    std::ostringstream oss;
    oss << c_ref_map1;
    auto size = oss.str().size();
    oss << c_ref_map2 << c_ref_map1 << c_ref_map2;
    CHECK_EQUAL(oss.str().size() == 4*size, __LINE__);
}
#endif

#if RUN_TEST_3A
void A_copy_constructor_assignment() {
   HashMap<std::string, int> map;

   for (const auto& kv_pair : vec) {
       map.insert(kv_pair);
   }

   HashMap<std::string, int> copy_constructed{map};
   HashMap<std::string, int> copy_assigned;
   copy_assigned = map;
   CHECK_EQUAL(map == copy_constructed, __LINE__);
   CHECK_EQUAL(map == copy_assigned, __LINE__);

   map.clear();
   CHECK_EQUAL(map != copy_constructed, __LINE__);
   CHECK_EQUAL(map != copy_assigned, __LINE__);
   CHECK_EQUAL(copy_constructed == copy_assigned, __LINE__);


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wself-assign-overloaded" // suppress the really annoying warnings
    // start doing weird things to the map
   copy_constructed = copy_constructed;
   copy_assigned = (copy_assigned = copy_assigned) = copy_assigned;

   map = map = map = map;
   CHECK_EQUAL(map.empty(), __LINE__);
#pragma GCC diagnostic pop
}
#endif
#if RUN_TEST_3B
void B_move_constructor_assignment() {
   HashMap<std::string, int> map1;
   HashMap<std::string, int> map2;
   HashMap<std::string, int> map_copy;

   for (const auto& kv_pair : vec) {
       map1.insert(kv_pair);
       map2.insert(kv_pair);
       map_copy.insert(kv_pair);
   }
   CHECK_EQUAL(map1 == map_copy, __LINE__);
   CHECK_EQUAL(std::move(map1) == map_copy, __LINE__);
   HashMap<std::string, int> move_constructed{std::move(map1)}; 
   HashMap<std::string, int> move_assigned;

   move_assigned = std::move(map2);
   CHECK_EQUAL(map_copy == move_constructed, __LINE__);
   CHECK_EQUAL(map_copy == move_assigned, __LINE__);
   map1 = move_constructed;                        // SHORT ANSWER QUESTION 2: ensure map1 still in a valid state.
   CHECK_EQUAL(map1 == move_constructed, __LINE__);


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wself-move" // suppress annoying warnings about self-assignment

   // let's start doing weird things to our map
   map1 = std::move(map1);
   (map1 = std::move(map1)) = map1 = std::move(map1 = map1 = std::move(map1));
   CHECK_EQUAL(map1 == move_constructed, __LINE__);

   // edge case with empty map
   HashMap<std::string, int> empty1;
   HashMap<std::string, int> empty2;
   empty1 = std::move(empty1);
   CHECK_EQUAL(empty1 == empty2, __LINE__);
   empty2 = std::move(map1);
   CHECK_EQUAL(empty2 == move_constructed, __LINE__);

#pragma GCC diagnostic pop

}
#endif

#if RUN_TEST_3C
void C_move_time() {
   HashMap<int, int> map1;
   HashMap<int, int> map2;
   HashMap<int, int> map_copy;
   std::map<int, int> answer;

   for (size_t i = 0; i < 10000; ++i) {
       map1.insert({i, i*i});
       map2.insert({i, i*i});
       answer.insert({i, i*i});
   }
   {
       auto start = clock_type::now();
       HashMap<int, int> move_constructed = std::move(map1);
       auto end = clock_type::now();
       auto elapsed = std::chrono::duration_cast<ms>(end - start);
       CHECK_EQUAL(check_equal(move_constructed,answer), __LINE__);
       CHECK_EQUAL(elapsed.count() < 10000, __LINE__);
   }

   {
       auto start = clock_type::now();
       HashMap<int, int> move_assigned;
       move_assigned = std::move(map2);
       auto end = clock_type::now();
       auto elapsed = std::chrono::duration_cast<ms>(end - start);
       CHECK_EQUAL(check_equal(move_assigned,answer), __LINE__);
       CHECK_EQUAL(elapsed.count() < 10000, __LINE__);
   }
}
#endif

#if RUN_TEST_6A
void A_iterator_for_each_basic() {
   std::set<std::pair<int, int> > questions {
       {1, 1}, {2, 2}, {30, 30}, {140, 140}, {21, 21}
   };

   HashMap<int, int> map10;            // can your iterator traverse normal use case?
   for (const auto& pair : questions) {
       map10.insert(pair);
   }
   std::set<std::pair<int, int> > answers10;
   for (const auto& pair : map10) CHECK_EQUAL(answers10.insert(pair).second == true, __LINE__);

   CHECK_EQUAL(questions == answers10, __LINE__);
}
#endif

#if RUN_TEST_6B
void B_iterator_for_each_edge() {
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
   for (const auto& pair : map1) CHECK_EQUAL(answers1.insert(pair).second == true, __LINE__);
   for (const auto& pair : map5) CHECK_EQUAL(answers5.insert(pair).second == true, __LINE__);
   for (const auto& pair : map10) CHECK_EQUAL(answers10.insert(pair).second == true, __LINE__);
   for (const auto& pair __attribute__((unused)) : empty) CHECK_EQUAL(false, __LINE__); // this should not run!

   CHECK_EQUAL(questions == answers1, __LINE__);
   CHECK_EQUAL(questions == answers5, __LINE__);
   CHECK_EQUAL(questions == answers10, __LINE__);
}
#endif

#if RUN_TEST_6C
void C_iterator_operators() {
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
   CHECK_EQUAL((*iter).first == (*iter).second, __LINE__);   // behavior of * operator
   CHECK_EQUAL(iter->first == iter->second, __LINE__);       // behavior of -> operator
   CHECK_EQUAL(iter == iter, __LINE__);                      // behavior of == operator
   CHECK_EQUAL(!(iter != iter), __LINE__);                   // behavior of != operator

   (*iter).second = -1;                        // behavior of * operator as an l-value
   CHECK_EQUAL((*iter).second == -1, __LINE__);    // behavior of * operator as an r-value
   iter->second = -2;                          // behavior of -> operator as an l-value
   CHECK_EQUAL(iter->second == -2, __LINE__);      // behavior of -> operator as an r-value

   // verify correct prefix/postfix behavior (this was very tedious)
   HashMap<int, int>::iterator iter0 = iter; // just to prove why type aliases are helpful
   auto iter1 = ++iter;                      // though auto usually works as well
   auto iter2 = ++iter;
   auto iter3 = ++iter;
   CHECK_EQUAL(iter == map.end(), __LINE__);
   iter = iter0;                       // iter->0
   auto& iter_ref = ++iter;            // iter/iter_ref->1
   CHECK_EQUAL(iter_ref == iter1, __LINE__);
   auto iter_ref_copy = ++iter_ref;    // iter_ref_copy->2, iter/iter_ref->2
   CHECK_EQUAL(iter_ref_copy == iter2, __LINE__);
   CHECK_EQUAL(iter_ref == iter2, __LINE__);

   auto iter_post = iter++;            // iter/iter_ref->3, iter_post->2
   CHECK_EQUAL(iter_post == iter2, __LINE__);
   CHECK_EQUAL(iter == iter3, __LINE__);
   iter_ref = map.begin();             // iter/iter_ref->0
   CHECK_EQUAL(iter == iter0, __LINE__);

   // Big LOL - see if you can actually trace the ++++++ operator.
   auto iter_chain_pre = ++++++iter;   // iter_chain_pre->3, iter/iter_ref->3
   CHECK_EQUAL(iter == iter3, __LINE__);
   CHECK_EQUAL(iter_chain_pre == iter3, __LINE__);
   iter_ref = map.begin();             // iter/iter_ref->0
   auto iter_chain_post = iter++++++;  // iter/iter_ref->1, iter_chain_post->0
   CHECK_EQUAL(iter == iter1, __LINE__);
   CHECK_EQUAL(iter_chain_post == iter0, __LINE__);
   // presumably if you pass the above ones, you probably have it working
   // so I'm not gonna think about what ++iter++++ would be
}
#endif 

#if RUN_TEST_6D
void D_iterator_algorithm() {
   HashMap<int, int> map;
   std::map<int, int> answer;

   for (int i = -17; i < 10; ++i) {
       map.insert({i, i*i});
   }

   std::copy(map.begin(), map.end(), std::inserter(answer, answer.begin()));
   CHECK_EQUAL(check_equal(map, answer), __LINE__);
   answer.clear();

   const auto& c_map = map;
   std::copy(c_map.begin(), c_map.end(), std::inserter(answer, answer.begin()));
   CHECK_EQUAL(check_equal(map, answer), __LINE__);
}
#endif

#if RUN_TEST_6E
void E_const_iterator() {
   std::set<std::pair<int, int> > questions {
       {1, 1}, {2, 2}, {3, 3}
   };

   /* testing const_iterator (iterator to const std::pair) */
   HashMap<int, int> map;
   for (const auto& pair : questions) map.insert(pair);
   const auto& const_map = map;
   std::set<std::pair<int, int> > answers;
   for (const auto& pair : const_map) CHECK_EQUAL(answers.insert(pair).second == true, __LINE__);
   CHECK_EQUAL(questions == answers, __LINE__);

   HashMap<int, int>::const_iterator iter = const_map.begin();

   CHECK_EQUAL((*iter).first == (*iter).second, __LINE__);   // behavior of * operator
   CHECK_EQUAL(iter->first == iter->second, __LINE__);       // behavior of -> operator
   CHECK_EQUAL(iter == iter, __LINE__);                      // behavior of == operator
   CHECK_EQUAL(!(iter != iter), __LINE__);                   // behavior of != operator

   CHECK_EQUAL(iter->second == (*iter).second, __LINE__);
   auto iter1 = ++iter;
   auto iter2 = ++iter;
   auto iter3 = iter++;
   CHECK_EQUAL(iter == const_map.end(), __LINE__);
   CHECK_EQUAL(iter3 == iter2, __LINE__);
   CHECK_EQUAL(iter1 != iter2, __LINE__);

   /* We could have the entire operator from 1C here, though that feels unnecessary */
}
#endif

#if RUN_TEST_6F
void F_iterator_const_correctness() {
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

   CHECK_EQUAL(map.begin() == c_iter, __LINE__);
   CHECK_EQUAL(copy == iter, __LINE__);
   CHECK_EQUAL(copy_next == iter, __LINE__);
   CHECK_EQUAL(c_iter != iter, __LINE__);

   // the iterator is const, but the stuff the iterator points to is not const.
   (*c_iter).second = -1;                                   // behavior of * operator as an l-value
   CHECK_EQUAL((*c_iter).second == -1, __LINE__);              // behavior of * operator as an r-value
   c_iter->second = -2;                                     // behavior of -> operator as an l-value
   CHECK_EQUAL(c_iter->second == -2, __LINE__);                // behavior of -> operator as an r-value

   // these should not compile:
   // *iter = {0, 0};  // *iter is a std::pair<const K, M>, since K is const, = is deleted
   // ++c_iter;        // ++ is non-const

   CHECK_EQUAL(++++iter == map.end(), __LINE__);

   /* test behavior of const const_iterator */
   const auto& const_map = map;
   HashMap<int, int>::const_iterator const_iter = const_map.begin();
   const HashMap<int, int>::const_iterator c_const_iter_next = ++const_map.begin();
   const HashMap<int, int>::const_iterator c_const_iter = const_map.begin();

   // the key here is that these should compile.
   ++const_iter;
   CHECK_EQUAL((*c_const_iter).second == -2, __LINE__);
   CHECK_EQUAL(c_const_iter->second == -2, __LINE__);
   CHECK_EQUAL(const_iter == c_const_iter_next, __LINE__);
   CHECK_EQUAL(c_const_iter == const_map.begin(), __LINE__);

   // these should not compile:
   // ++c_const_iter;
   // c_const_iter->second = 2;
   // const_iter->second = 2;
}
#endif

#if RUN_TEST_5A
void A_initializer_list_constructor() {
   std::map<std::string, int> answer {
       {"A", 3}, {"B", 2}, {"C", 1}, {"A", -5}, {"B", 3}, {"A", 5}, {"C", 1}
   };

   HashMap<std::string, int> map {
       {"A", 3}, {"B", 2}, {"C", 1}, {"A", -5}, {"B", 3}, {"A", 5}, {"C", 1}
   };

   CHECK_EQUAL(check_equal(map, answer), __LINE__);

}
#endif

#if RUN_TEST_5B
void B_range_constructor() {
   std::vector<std::pair<std::string, int>> values {
       {"Ignore me", 100}, {"A", 3}, {"B", 2}, {"C", 1}, {"A", -5}, {"B", 3}, {"A", 5}, {"C", 1}
   };
   std::map<std::string, int> answer {values.begin()++, values.end()};
   HashMap<std::string, int> map {values.begin()++, values.end()};

   CHECK_EQUAL(check_equal(map, answer), __LINE__);
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
    } catch (std::string& e) {
        cout << "Test "  << std::setw(30) << left << test_name  << right << " FAIL: " << e << endl;
        return 0;
    } catch (const std::exception& e) {
        cout << "Test C_move_time unknown exception thrown: " << e.what() << endl;
        return 0;
    }
    return 1;
}

void skip_test(const string& test_name) {
    cout << "Test "  << std::setw(30) << left << test_name  << right << " SKIP " << endl;
}

void run_test_harness() {
    cout << endl;
    cout << "CS 106L SIMPLE TEST HARNESS" << endl;
    cout << "Written by Avery Wang (2019-2020 lecturer)" << endl << endl;
    int required_pass = 0;
    int bonus_pass = 0;
    cout << "-----Starter Code Tests (Provided)-----" << endl;
    required_pass += run_starter_code_tests();
    cout << endl << "-----Milestone 1 Tests (Required)-----" << endl;
    required_pass += run_milestone1_tests();
    cout << endl << "-----Milestone 2 Tests (Required)-----" << endl;
    required_pass += run_milestone2_tests();
    cout << endl << "-----Milestone 3 Tests (Required)-----" << endl;
    required_pass += run_milestone3_tests();
    cout << endl << "-----Milestone 4 Tests (Required)-----" << endl;
    cout << "(10 short answers graded manually)" << endl;
    cout << endl << "-----Milestone 5 Tests (Optional)-----" << endl;
    bonus_pass += run_milestone5_tests();
    cout << endl << "-----Milestone 6 Tests (Optional)-----" << endl;
    bonus_pass +=  run_milestone6_tests();
    cout << endl << "-----Test Harness Summary-----" << endl;
    cout << "Required tests: " << required_pass << "/16 (excluding short answers)" << endl;
    cout << "Optional tests: " << bonus_pass << "/8" << endl;
    if (required_pass <= 6) {
        cout << "Still getting started! ";
    } else if (required_pass <= 9) {
        cout << "You are making progress! Keep going! ";
    } else if (required_pass <= 12) {
        cout << "Halfway there! ";
    } else if (required_pass <= 15) {
        cout << "Super close! ";
    } else {
        cout << "You passed all required tests! Great job!" << endl;
    }
    if (required_pass < 16) {
        cout << "Some tests were failed or skipped. If stuck, try adding a map.debug() call before a CHECK_EQUAL." << endl;
    }
    if (bonus_pass == 8) {
        cout << "It's students like you who are so interested in C++ that you go way above and beyond " << endl;
        cout << "the class that make teaching such a joy. It's our very last quarter teaching, and we " << endl;
        cout << "just want to say in this hidden message, thank you for this amazing quarter." << endl; 
    } else if (bonus_pass >= 4) {
        cout << "You even succeeded in some extensions! That's awesome." << endl;
    } else if (bonus_pass > 0) {
        cout << "Wow! You've clearly invested a lot of time in extensions. You're amazing" << endl;
    }
}

int run_starter_code_tests() {
    int passed = 0;
    passed += run_test(A_basic, "A_basic");
    passed += run_test(B_insert, "B_insert");
    passed += run_test(C_clear, "C_clear");
    passed += run_test(D_at_test, "D_at_test");
    passed += run_test(E_custom_bucket_count, "E_custom_bucket_count");
    passed += run_test(F_custom_hash_function, "F_custom_hash_function");
    return passed;
}

int run_milestone1_tests() {
    int passed = 0;
    #if RUN_TEST_1A
    passed += run_test(A_erase, "A_erase");
    #else
    skip_test("A_erase");
    #endif

    #if RUN_TEST_1B
    passed += run_test(B_rehash_basic, "B_rehash_basic");
    #else
    skip_test("B_rehash_basic");
    #endif

    #if RUN_TEST_1C
    passed += run_test(C_rehash_correctness_by_time, "C_rehash_correctness_by_time");
    #else
    skip_test("C_rehash_correctness_by_time");
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
    passed += run_test(A_copy_constructor_assignment, "A_copy_constructor_assignment");
    #else
    skip_test("A_copy_constructor_assignment");
    #endif

    #if RUN_TEST_3B
    passed += run_test(B_move_constructor_assignment, "B_move_constructor_assignment");
    #else
    skip_test("B_move_constructor_assignment");
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
    passed += run_test(A_initializer_list_constructor, "A_initializer_list_constructor");
    #else
    skip_test("A_initializer_list_constructor");
    #endif

    #if RUN_TEST_5B
    passed += run_test(B_range_constructor, "B_range_constructor");
    #else
    skip_test("B_range_constructor");
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
