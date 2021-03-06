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
#include <math.h>

#include "Collatz.hpp"

using namespace std;

int lazy_cache[1000000] = {0};

// This is a cache to contains the highest collatz cycle in the sets of a one
// thousand numbers, so a set can be defined as a range of XXX1 - X000
// index[0] the range is 1 to 1000 with the highest collatz cycle being 179
int meta_cache [1000] = {
    179, 182, 217, 238, 215, 236, 262, 252, 247, 260, 268, 250,
    263, 276, 271, 271, 266, 279, 261, 274, 256, 269, 269, 282, 264, 264, 308, 259,
    259, 272, 272, 285, 267, 267, 311, 324, 249, 306, 244, 306, 288, 257, 288, 270,
    270, 314, 283, 314, 296, 296, 278, 309, 340, 322, 260, 260, 322, 304, 273, 304,
    335, 317, 286, 330, 299, 268, 268, 312, 312, 299, 312, 325, 263, 294, 325, 307,
    307, 351, 338, 307, 320, 320, 320, 289, 320, 302, 302, 333, 333, 315, 315, 333,
    315, 284, 315, 328, 297, 297, 284, 328, 341, 310, 310, 248, 310, 341, 354, 292,
    279, 310, 292, 323, 323, 292, 305, 349, 305, 305, 336, 305, 318, 336, 318, 331,
    287, 318, 331, 287, 331, 344, 331, 300, 331, 313, 300, 344, 313, 331, 313, 313,
    344, 326, 375, 282, 326, 295, 357, 295, 326, 326, 370, 295, 308, 308, 352, 308,
    383, 339, 321, 352, 370, 290, 339, 321, 334, 321, 352, 321, 321, 334, 290, 334,
    303, 347, 334, 272, 334, 334, 347, 303, 365, 316, 334, 254, 316, 329, 347, 329,
    316, 360, 329, 329, 347, 329, 342, 360, 298, 285, 329, 329, 342, 311, 342, 311,
    311, 355, 373, 311, 311, 311, 342, 355, 355, 373, 293, 280, 386, 324, 324, 355,
    324, 355, 324, 324, 324, 368, 368, 306, 355, 306, 443, 350, 337, 368, 381, 306,
    337, 350, 306, 350, 368, 275, 319, 337, 275, 319, 332, 350, 288, 350, 332, 319,
    319, 332, 363, 288, 332, 345, 301, 345, 332, 332, 301, 407, 332, 332, 314, 345,
    270, 345, 407, 283, 314, 358, 332, 345, 314, 389, 345, 314, 345, 358, 314, 358,
    358, 376, 314, 327, 389, 345, 327, 327, 340, 358, 296, 358, 327, 327, 371, 327,
    371, 296, 340, 340, 340, 265, 309, 309, 371, 340, 371, 309, 384, 340, 278, 340,
    353, 309, 353, 322, 371, 353, 309, 322, 384, 340, 247, 322, 291, 353, 322, 291,
    353, 335, 322, 322, 366, 366, 335, 366, 304, 335, 353, 335, 304, 441, 348, 322,
    335, 366, 304, 379, 335, 304, 348, 379, 348, 304, 379, 348, 410, 348, 361, 317,
    317, 361, 348, 286, 317, 361, 392, 348, 317, 348, 330, 361, 423, 361, 330, 361,
    379, 374, 361, 330, 330, 348, 330, 299, 330, 436, 361, 330, 299, 361, 405, 312,
    330, 330, 374, 299, 374, 387, 268, 343, 343, 405, 361, 268, 312, 312, 449, 330,
    343, 374, 374, 312, 387, 343, 343, 281, 343, 325, 356, 418, 356, 356, 356, 374,
    294, 281, 312, 343, 387, 343, 356, 281, 325, 387, 400, 356, 325, 294, 356, 338,
    325, 338, 325, 325, 369, 369, 387, 307, 294, 369, 338, 338, 356, 338, 307, 307,
    307, 444, 369, 325, 338, 369, 369, 413, 382, 338, 307, 276, 338, 307, 382, 320,
    307, 382, 351, 351, 413, 382, 351, 307, 320, 338, 382, 382, 382, 351, 320, 320,
    426, 395, 351, 320, 320, 289, 351, 395, 364, 320, 426, 320, 364, 364, 382, 364,
    377, 364, 333, 470, 333, 351, 364, 395, 302, 333, 439, 364, 333, 364, 333, 302,
    364, 408, 408, 377, 377, 333, 346, 346, 377, 377, 346, 302, 333, 377, 346, 346,
    408, 364, 346, 359, 315, 346, 452, 377, 333, 315, 346, 377, 315, 346, 421, 390,
    346, 315, 315, 284, 359, 328, 359, 328, 421, 328, 359, 359, 359, 359, 377, 359,
    372, 359, 328, 346, 390, 390, 346, 359, 266, 328, 328, 434, 372, 359, 359, 328,
    315, 297, 359, 403, 328, 328, 328, 328, 372, 372, 341, 372, 372, 403, 297, 297,
    372, 341, 328, 341, 403, 359, 341, 354, 310, 310, 310, 447, 372, 372, 310, 341,
    372, 372, 310, 354, 385, 354, 509, 341, 279, 279, 341, 310, 385, 354, 310, 416,
    310, 354, 354, 354, 416, 372, 416, 279, 279, 310, 323, 341, 323, 385, 341, 336,
    354, 385, 323, 385, 429, 354, 398, 354, 323, 323, 292, 292, 367, 442, 323, 367,
    323, 336, 323, 323, 367, 336, 367, 385, 336, 336, 380, 367, 336, 336, 305, 380,
    336, 354, 398, 380, 292, 336, 336, 442, 323, 367, 367, 336, 336, 318, 367, 367,
    367, 411, 380, 349, 504, 380, 305, 349, 349, 336, 380, 380, 411, 380, 305, 305,
    380, 349, 336, 349, 411, 367, 411, 349, 362, 305, 349, 318, 362, 318, 380, 336,
    380, 349, 349, 424, 318, 380, 424, 424, 393, 318, 349, 318, 318, 349, 287, 362,
    318, 393, 362, 331, 318, 424, 318, 362, 362, 331, 362, 362, 380, 362, 331, 375,
    362, 331, 331, 468, 331, 393, 349, 344, 393, 362, 331, 437, 331, 393, 437, 362,
    344, 362, 331, 331, 313, 375, 300, 362, 406, 406, 375, 344, 437, 375, 331, 331,
    468, 344, 300, 375, 375, 406, 388, 300, 331, 375, 344, 406, 331, 344, 406, 287,
    362, 375, 313, 357, 344, 344, 450, 357, 450, 375, 344, 375, 326, 344, 313, 419,
    313, 375, 344, 419, 388, 357, 344, 313, 344, 525, 344, 388, 357, 313, 388, 331,
    357, 401, 313, 419, 313, 357, 357, 357, 326, 357, 419, 388, 375, 357, 370, 313,
    357, 326, 326, 344, 326, 388, 326, 344, 357, 388, 326, 432, 326, 326, 388, 432,
    370, 401, 326, 357, 326, 326, 313, 370, 295, 370, 445, 401, 295, 370, 339, 326,
    295, 326, 370, 326, 370, 339, 370, 295, 401, 401, 383, 295, 383, 295, 445, 326,
    370, 326, 476, 383, 401, 357, 370, 339, 339, 383, 339, 432, 339, 339, 445, 308,
    370, 339, 370, 476, 383, 339, 370, 308, 370, 370, 414, 414, 383, 352, 445, 507,
    383, 339, 339, 352, 383, 352, 383, 383, 383, 352, 414, 383, 414, 414, 383, 339,
    352, 352, 321, 352, 414, 352, 383, 414, 352, 321, 365, 308, 321, 352, 458, 352,
    321, 383, 383, 339, 383, 334, 383, 334, 427, 321, 383, 383, 352, 427, 352, 396,
    321, 352, 321, 321, 352, 290, 365, 365, 365, 440, 396, 396
};

// ------------
// get_max_cycle
// ------------

// Side Note about get_max_cycle, I orginally had two methods that get_max_cycle
// would call, but the program passed tests when got rid of the methods and put
// them in get_max_cycle

// Find the max Collatz cycle length of all the numbers from from start to end
// inclusive with Collatz Conjecture and a lazy_cache
// Pre condition: 0 < start, end < 1,000,000
int get_max_cycle(int start, int end) {

    // I would have declared all the local variables in the outside, but I was
    // not passing test 1 and 2 whrn I did that
    int max = 1;

    for(int i = start; i <= end; i++) {
        // Sooooo for some reason when n was an int the program ran slower
        // and I was passing tests with n being a long
        long n = i;
        int cycle = 1;

        // Find the Collatz cycle of n
        while (n > 1) {

            // See if n has its cycle cached
            if (n < 1000000 && lazy_cache[n]) {
                cycle += lazy_cache[n] - 1;
                n = 1;

                // Collatz Conjecture
            } else {
                if (!(n % 2)) {
                    n = n >> 1;
                    cycle++;

                } else {
                    n = n + (n >> 1) + 1;
                    cycle += 2;
                }
            }
        }

        // Determine if cycle is bigger than the current max
        if(cycle > max) {
            max = cycle;
        }

        n = i;
        int count = 0;

        // Go through path of n again and cache the cycles of numbers in path
        while (n > 1) {

            // If we get to a number that is already cached, then
            // we can leave early since numbers after are cached too
            if (n < 1000000 && lazy_cache[n]) {
                n = 1;

                // Add the Collatz cycle into the cache
            } else {

                // We only cache numbers below 1,000,000
                if (n < 1000000 && !lazy_cache[n]) {
                    // Since count keeps track of the numbers we have gone
                    // through we can use that to find the collatz cycle
                    // using the cycle of i
                    lazy_cache[n] = cycle - count;
                }

                // Collatz Conjecture
                if (!(n % 2)) {
                    n = n >> 1;
                    count++;

                } else {
                    n = n + (n >> 1) + 1;
                    count += 2;
                }
            }
        }

    }
    return max;
}

// ------------
// get_max_cache
// ------------

// Search the meta cache and determine what is the biggest collatz cycle
// between all the sets start to end inclusive
// Pre condition: 0 < start, end < 1,000
int get_max_cache(int start, int end) {
    int temp;
    int max = -1;

    for(; start <= end; start++) {
        temp = meta_cache[start];
        max = temp > max ? temp : max;
    }
    return max;
}

// ------------
// get_modified_range
// ------------

// Determine the range to search in the met-cache and the ranges for the
// lower and upper ranges for get_max_cycle to compute
// For example if i = 1234 and  j = 56789, then we would use the meta
// cache for 2001 to 56700 (or index 2 to index 56 in the meta array) and
// we would use get_max_cycle for 1234 to 2000 and 56701 to 56789
tuple<int, int, int, int> get_modified_range(int mod_i, int j) {
    int cache_start, cache_end, left_end, right_start;

    cache_start = (mod_i + 1000 - 1) / 1000;
    cache_end = (j - 1000 - 1) / 1000;
    left_end = mod_i - (mod_i % 1000) + (mod_i % 1000 ? 1000 : 0);
    right_start = j - (j % 1000) + (j % 1000 ? 1 : -999);

    return make_tuple(cache_start, cache_end, left_end, right_start);
}

// ------------
// collatz_and_cache
// ------------

// We use the meta-cache for SETS and get_max_cycle for extra numbers
// that aren't accounted for
int collatz_and_cache(int mod_i, int j) {
    int temp;
    int cache_start, cache_end, left_end, right_start;
    int max = -1;

    // Get proper indexes to search cache
    tie(cache_start, cache_end, left_end, right_start)
        = get_modified_range(mod_i, j);

    // Run get_max_cycle for lower modified range
    max = get_max_cache(cache_start, cache_end);

    // Run get_max_cycle for lower modified range
    temp = get_max_cycle(mod_i, left_end);
    max = temp > max ? temp : max;

    // Run get_max_cycle for upper modified range
    temp = get_max_cycle(right_start, j);
    max = temp > max ? temp : max;

    return max;
}

// ------------
// collatz_eval
// ------------

// Determine the max cycle length of the range of the given parameters
// A SET is defined as 1000 numbers within a certain range, so 523 is
// in the set of 1 - 1000 and 2344 is in the set of 2001 and 3000
// Pre condition: 0 < i, j < 1,000,000
tuple<int, int, int> collatz_eval (const pair<int, int>& p) {
    int i;
    int j;
    int mod_i, max, temp = -1;
    tie(i, j) = p;

    assert(i > 0 && i < 1000000);
    assert(j > 0 && j < 1000000);

    // In case we have to swap
    if(j < i) {
        temp = i;
        i = j;
        j = temp;
    }

    // Adjust range to possibly get rid of half of the numbers to search
    mod_i = ((j / 2) + 1) > i ? (j / 2) + 1 : i;

    // Quickly get max cycle if the range is exactly one SET
    if(((mod_i - 1) / 1000) == ((j - 1) / 1000) && j - mod_i == 999) {
        max = meta_cache[mod_i / 1000];

        // i and j have a full SET in between so use meta-cache and get_max_cycle
    } else if(((mod_i - 1) / 1000) + 1 < (j - 1) / 1000) {
        max = collatz_and_cache(mod_i, j);

        // Cqn't use meta-cache so just use lazy_cache and get_max_cycle
    } else {
        max = get_max_cycle(mod_i, j);
    }

    // If temp != -1, there was a swap, and temp is holding the old i
    if(temp != -1) {
        j = i;
        i = temp;
    }
    return make_tuple(i, j, max);
}

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);
}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& sout, const tuple<int, int, int>& t) {
    int i;
    int j;
    int v;
    tie(i, j, v) = t;
    sout << i << " " << j << " " << v << endl;
}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& sin, ostream& sout) {
    string s;
    while (getline(sin, s))
        collatz_print(sout, collatz_eval(collatz_read(s)));
}