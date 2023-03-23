// arrayfun.c [IMPLEMENTATION]

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arrayfun.h"

// see arrayfun.h for documentation
int divides_followers(const int a[], int n) {
  assert(a);
  assert(n > 1);

  int count = 0;	
  for (int i = 0; i < n; ++i) {
    int total = 0;
    for (int j = i; j < n; ++j) {
      total += a[j];
    }
    if ((a[i] != 0) && (total % a[i] == 0)) {
      ++count;
    }
  }
  return count;
}

// see arrayfun.h for documentation
bool consec_sum(const int a[], int n, const int b[], int m) {
  assert(a);
  assert(n > 1);
  assert(b);
  assert(m > 1);

  for (int j = 0; j < m; ++j) {
    for (int i = 0; i < n - 1; ++i) {
      if (b[j] == a[i] + a[i + 1]) {
        return true;
      }
    }
  }
  return false;
}

// see arrayfun.h for documentation
void even_first(int a[], int n) {
  assert(a);
  assert(n > 0);
  
  int temp = 0;
  for (int i = 0; i < n; ++i) {
    if (a[i] % 2 == 0) {
      temp = a[i];
      for (int j = i; j > 0; --j) {
        a[j] = a[j - 1];
      }
      a[0] = temp;
    }
  }
}
// [1,3,4,7]