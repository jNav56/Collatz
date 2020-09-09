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
// get_collatz_cycle
// ------------

// Determine the cycle length of the given parameter
// Pre condition: 0 < n < 1,000,000
int get_collatz_cycle(int n) {
    int cycle = 0;

    while(n != 1) {
        if(n % 2 == 1) { // n & 1 for first optimization
            n = (3 * n + 1) >> 1;
            cycle++;
        } else {
            // Use a bit shift to the right instead of division
            n = n >> 1;
        }
        cycle++;
    }
    cycle++;
    return cycle;
}

// ------------
// collatz_eval
// ------------

// Determine the max cycle length of the range of the given parameters
// Pre condition: 0 < i, j < 1,000,000
// Post condition: 0 < number of pairs < 1,000
tuple<int, int, int> collatz_eval (const pair<int, int>& p) {
    int i;
    int j;
    int max, temp, start;
    max = -1;
    tie(i, j) = p;
    // <your code>

    // In reference to Quiz#04 > Question 5 on Canvas
    // If {m = (j / 2) + 1} > i, then we can just find the cycle length of
    // [m, j] because anything else will be mapped to a number in [m, j] 
    start = ((j / 2) + 1) > i ? (j / 2) + 1 : i;

    for(; start <= j; start++) {
        temp = get_collatz_cycle(start);
        max = temp > max ? temp: max;
    }
    return make_tuple(i, j, max);}

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