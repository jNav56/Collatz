// ---------------
// TestCollatz.c++
// ---------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iterator> // istream_iterator
#include <sstream>  // istringtstream, ostringstream
#include <tuple>    // make_tuple, tie, tuple
#include <utility>  // make_pair, pair

#include "gtest/gtest.h"

#include "Collatz.hpp"

using namespace std;

// ----
// read
// ----

// TEST(CollatzFixture, read) {
//     string s("1 10\n");
//     const pair<int, int> p = collatz_read(s);
//     ASSERT_EQ(p.first,   1);
//     ASSERT_EQ(p.second, 10);}

// ----
// eval
// ----

TEST(CollatzFixture, eval0) {
    ASSERT_EQ(collatz_eval(make_pair(1, 10)), make_tuple(1, 10, 20));}

TEST(CollatzFixture, eval1) {
    ASSERT_EQ(collatz_eval(make_pair(100, 200)), make_tuple(100, 200, 125));}

TEST(CollatzFixture, eval2) {
    ASSERT_EQ(collatz_eval(make_pair(201, 210)), make_tuple(201, 210, 89));}

TEST(CollatzFixture, eval3) {
    ASSERT_EQ(collatz_eval(make_pair(900, 1000)), make_tuple(900, 1000, 174));}

// TEST(CollatzFixture, cache1) {
//     ASSERT_EQ(27, get_cache_value(200));
//     int* cache = get_cache();

//     for(int i = 101; i <= 200; i++) {
//         cout << "cache[" << i << "] = " << cache[i] << endl;
//     }
// }

// -----
// My own unit tests
// -----

TEST(CollatzFixture, eval4) {
    ASSERT_EQ(collatz_eval(make_pair(1000, 5000)), make_tuple(1000, 5000, 238));}

TEST(CollatzFixture, eval5) {
    ASSERT_EQ(collatz_eval(make_pair(10000, 50000)), make_tuple(10000, 50000, 324));}

TEST(CollatzFixture, eval6) {
    ASSERT_EQ(collatz_eval(make_pair(499000, 500000)), make_tuple(499000, 500000, 395));}

TEST(CollatzFixture, eval7) {
    ASSERT_EQ(collatz_eval(make_pair(1000, 100000)), make_tuple(1000, 100000, 351));}

// -----
// print
// -----

// TEST(CollatzFixture, print) {
//     ostringstream oss;
//     collatz_print(oss, make_tuple(1, 10, 20));
//     ASSERT_EQ(oss.str(), "1 10 20\n");}

// -----
// solve
// -----

// TEST(CollatzFixture, solve) {
//     istringstream iss("1 10\n100 200\n201 210\n900 1000\n");
//     ostringstream oss;
//     collatz_solve(iss, oss);
//     ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", oss.str());}
