// -----------
// Collatz.c++
// -----------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <tuple>    // make_tuple, tie, tuple
#include <utility>  // make_pair, pair

#include "Collatz.hpp"

using namespace std;

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

// ------------
// collatz_eval
// ------------

tuple<int, int, int> collatz_eval (const pair<int, int>& p) {
    int i;
    int j;
    tie(i, j) = p;
    // <your code>
    return make_tuple(i, j, i + j);}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& sout, const tuple<int, int, int>& t) {
    int i;
    int j;
    int v;
    tie(i, j, v) = t;
    sout << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& sin, ostream& sout) {
    string s;
    while (getline(sin, s))
         collatz_print(sout, collatz_eval(collatz_read(s)));}
