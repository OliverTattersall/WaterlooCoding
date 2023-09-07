/////////////////////////////////////////////////////////////////////////////////////////
// INTEGRITY STATEMENT (v4)
//
// By signing your name and ID below you are stating that you have agreed
// to the online academic integrity statement posted on edX:
// (Course > Assignments > Assignment Information & Policies > Academic Integrity Policy)
/////////////////////////////////////////////////////////////////////////////////////////
// I received help from and/or collaborated with:

// None
//
// Name: Oliver Tattersall
// login ID: omtatter
//////////////////////////////////////////////////////////////////////////////////////////

// This program implements a simplified version of the linux "sort" utility

// It reads in all input line by line and then prints all the lines sorted

// note: sos_qsort must mimic the behaviour of the integer quicksort algorithm
//       presented in the notes [see below]

//////////////////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cs136-trace.h"
#include "sos.h"
#include "string-io.h"




// sos_qsort_helper(seq, first, last) sorts the seq using a quicksort algorithm
// requires: seq is a valid seq (not NULL)
// effects: modifies seq
// time: O(m*n*logn) [average] and O(m*n^2) [worst case]
//       where m is the longest string in seq
//       and n is the number of srings in seq
void sos_qsort_helper(struct sos *seq, int first, int last){
  assert(seq);
  
  if(last <= first){
    return;
  }
  
  const char *temp = sos_item_at(seq, first); 
  char *pivot = malloc((strlen(temp)+1)*sizeof(char));
  strcpy(pivot, temp);
  int pos = last;

  for(int i = last; i > first; i--){
    if(strcmp( sos_item_at(seq, i), pivot ) > 0){
      sos_swap(seq, i, pos);
      pos--; 
    }
  }

  free(pivot);
  sos_swap(seq, first, pos);
  sos_qsort_helper(seq, first, pos - 1);
  sos_qsort_helper(seq, pos + 1, last);


}


// sos_qsort(seq) sorts the seq using a quicksort algorithm
// requires: seq is a valid seq (not NULL)
// effects: modifies seq
// time: O(m*n*logn) [average] and O(m*n^2) [worst case]
//       where m is the longest string in seq
//       and n is the number of srings in seq
void sos_qsort(struct sos *seq) {
  assert(seq);
  sos_qsort_helper(seq, 0, sos_length(seq) - 1);


}


// you should not need to modify main()

int main(void) {
  struct sos *seq = sos_read();
  sos_qsort(seq);
  sos_print(seq);
  sos_destroy(seq);
}

/*

FOR YOUR CONVENIENCE, WE HAVE PROVIDED THE INTEGER VERSION OF QUICK SORT FROM THE NOTES:

// quick_sort_range(a, first, last) sorts the elements of
//   a in the range a[first]..a[last] (inclusive)
//   in ascending order
// requires: a is a valid array in the range first..last [not asserted]
// effects: modifies a
void quick_sort_range(int a[], int first, int last) {
  assert(a);
  if (last <= first) return;  // length is <= 1
  
  int pivot = a[first];       // first element is the pivot
  int pos = last;             // where to put next larger
  
  for (int i = last; i > first; --i) {
    if (a[i] > pivot) {
      swap(&a[pos], &a[i]);
      --pos;
    }
  }
  swap(&a[first], &a[pos]);   // put pivot in correct place
  quick_sort_range(a, first, pos - 1);
  quick_sort_range(a, pos + 1, last);
}

// quick_sort(a, len) sorts the elements of a in ascending order
// requires: len > 0
// effects: modifies a
void quick_sort(int a[], int len) {
  assert(a);
  assert(len > 0);  
  quick_sort_range(a, 0, len - 1);
}

*/
