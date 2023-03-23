#include <stdbool.h>
#include <assert.h>

// divides_followers(a, n) determines how many items in a are divisors
//   of the sum of the sub-array starting at that item and ending at
//   the final item of the array.
// requires: a is a valid array with given len, n [not asserted]
//           n > 1
// time: O(n), n is len of a
int divides_followers(const int a[], int n);

// consec_sum(a, n, b, m) determines if an element of b is the sum
//   of any two consecutive elements in a.
// requires: a and b are arrays of length n and m, respectively
//           [not asserted]
//           n, m > 1
// 	         b is sorted in increasing order (a may not be sorted)
//           [not asserted]
// time: O(n*logm), n is len of a and m is len of b
bool consec_sum(const int a[], int n, const int b[], int m);

// even_first(a, n) puts all the even numbers before all of the odd numbers
//   in the array a.  The order of the even/odd items may be changed in some
//   unspecified way.
// requires: a is a valid array with given len, n [not asserted]
//           n > 1
// effects: may modify a
// time: O(n), n is len of a
void even_first(int a[], int n);
