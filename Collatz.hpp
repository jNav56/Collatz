// ---------
// Collatz.h
// ---------

#ifndef Collatz_h
#define Collatz_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <iterator> // istream_iterator
#include <tuple>    // tuple
#include <utility>  // pair

using namespace std;

// ------------
// collatz_read
// ------------

/**
 * read two ints
 * @param a string
 * @return a pair of ints
 */
pair<int, int> collatz_read (const string&);

// ------------
// collatz_eval
// ------------

/**
 * @param a pair of ints
 * @return a tuple of three ints
 */
tuple<int, int, int> collatz_eval (const pair<int, int>&);

// -------------
// collatz_print
// -------------

/**
 * print three ints
 * @param an ostream
 * @param a tuple of three ints
 */
void collatz_print (ostream&, const tuple<int, int, int>&);

// -------------
// collatz_solve
// -------------

/**
 * @param an istream
 * @param an ostream
 */
void collatz_solve (istream&, ostream&);

// -------------
// get_modified_range
// -------------

/**
 * @param an int
 * @param an int
 */
tuple<int, int, int, int> get_modified_range(int, int);

// -------------
// collatz_and_cache
// -------------

/**
 * @param an int
 * @param an int
 */
int collatz_and_cache(int, int);

// -------------
// get_max_cache
// -------------

/**
 * @param an int
 * @param an int
 */
int get_max_cache(int, int);

// -------------
// get_max_range
// -------------

/**
 * @param an int
 * @param an int
 */
int get_max_range(int, int);

#endif // Collatz_h
