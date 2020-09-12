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
    ASSERT_EQ(collatz_eval(make_pair(1, 10)), make_tuple(1, 10, 20));
}

TEST(CollatzFixture, eval1) {
    ASSERT_EQ(collatz_eval(make_pair(100, 200)), make_tuple(100, 200, 125));
}

TEST(CollatzFixture, eval2) {
    ASSERT_EQ(collatz_eval(make_pair(201, 210)), make_tuple(201, 210, 89));
}

TEST(CollatzFixture, eval3) {
    ASSERT_EQ(collatz_eval(make_pair(900, 1000)), make_tuple(900, 1000, 174));
}

// -----
// My own unit tests
// -----

// 1
TEST(CollatzFixture, eval4) {
    ASSERT_EQ(collatz_eval(make_pair(1000, 5000)), make_tuple(1000, 5000, 238));
}

// 2
TEST(CollatzFixture, eval5) {
    ASSERT_EQ(collatz_eval(make_pair(10000, 50000)), make_tuple(10000, 50000, 324));
}

// 3
TEST(CollatzFixture, eval6) {
    ASSERT_EQ(collatz_eval(make_pair(499000, 500000)), make_tuple(499000, 500000, 395));
}

// 4
TEST(CollatzFixture, eval7) {
    ASSERT_EQ(collatz_eval(make_pair(1000, 999999)), make_tuple(1000, 999999, 525));
}

// 5
TEST(CollatzFixture, meta_cache0) {
    ASSERT_EQ(get_max_cache(1, 6), 262);
}

// 6
TEST(CollatzFixture, meta_cache1) {
    ASSERT_EQ(get_max_cache(0, 999), 525);
}

// 7
TEST(CollatzFixture, meta_cache2) {
    ASSERT_EQ(get_max_cache(500, 500), 364);
}

// 8
TEST(CollatzFixture, modify_range0) {
    ASSERT_EQ(get_modified_range(1, 2001), make_tuple(1, 1, 1000, 2001));
}

// 9
TEST(CollatzFixture, modify_range1) {
    ASSERT_EQ(get_modified_range(1000, 2001), make_tuple(1, 1, 1000, 2001));
}

// 10
TEST(CollatzFixture, modify_range2) {
    ASSERT_EQ(get_modified_range(1000, 3000), make_tuple(1, 1, 1000, 2001));
}

// 11
TEST(CollatzFixture, modify_range3) {
    ASSERT_EQ(get_modified_range(1, 3000), make_tuple(1, 1, 1000, 2001));
}

// 12
TEST(CollatzFixture, modify_range4) {
    ASSERT_EQ(get_modified_range(12424, 325235), make_tuple(13, 324, 13000, 325001));
}

// 13
TEST(CollatzFixture, max_cycle0) {
    ASSERT_EQ(get_max_cycle(359351, 360000), 348);
}

// 14
TEST(CollatzFixture, max_cycle1) {
    ASSERT_EQ(get_max_cycle(586001, 586863), 359);
}

// 15
TEST(CollatzFixture, max_cycle2) {
    ASSERT_EQ(get_max_cycle(999001, 999999), 396);
}


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
