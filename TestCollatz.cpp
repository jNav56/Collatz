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

TEST(CollatzFixture, read) {
    string s("1 10\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ(p.first,   1);
    ASSERT_EQ(p.second, 10);}

// ----
// eval
// ----

TEST(CollatzFixture, eval0) {
    tuple<int, int, int> t = collatz_eval(make_pair(1, 10));
    int i;
    int j;
    int v;
    tie(i, j, v) = t;
    ASSERT_EQ(i,  1);
    ASSERT_EQ(j, 10);
    ASSERT_EQ(v, 20);}

TEST(CollatzFixture, eval1) {
    tuple<int, int, int> t = collatz_eval(make_pair(100, 200));
    int i;
    int j;
    int v;
    tie(i, j, v) = t;
    ASSERT_EQ(i, 100);
    ASSERT_EQ(j, 200);
    ASSERT_EQ(v, 125);}

TEST(CollatzFixture, eval2) {
    tuple<int, int, int> t = collatz_eval(make_pair(201, 210));
    int i;
    int j;
    int v;
    tie(i, j, v) = t;
    ASSERT_EQ(i, 201);
    ASSERT_EQ(j, 210);
    ASSERT_EQ(v, 89);}

TEST(CollatzFixture, eval3) {
    tuple<int, int, int> t = collatz_eval(make_pair(900, 1000));
    int i;
    int j;
    int v;
    tie(i, j, v) = t;
    ASSERT_EQ(i,  900);
    ASSERT_EQ(j, 1000);
    ASSERT_EQ(v, 174);}

// -----
// print
// -----

TEST(CollatzFixture, print) {
    ostringstream oss;
    collatz_print(oss, make_tuple(1, 10, 20));
    ASSERT_EQ(oss.str(), "1 10 20\n");}

// -----
// solve
// -----

TEST(CollatzFixture, solve) {
    istringstream iss("1 10\n100 200\n201 210\n900 1000\n");
    ostringstream oss;
    collatz_solve(iss, oss);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", oss.str());}
