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

#include <assert.h>
#include "arrayfun_improved.h"

int divides_followers(const int a[], int n) {
  assert(n > 0);
  assert(a);
  int count = 0;
  int sum = 0;

  for(int i = n - 1; i>-1; i--){
    sum+=a[i];
    if(a[i]!=0 && sum % a[i] == 0){
      count+=1;
    }
  }

  return count;
}	


// binary_search(b, m, val) checks if val is in b
// requires: b be sorted [not asserted]
//           b be non-NULL, m > 0
// time: O(log(m))
static bool binary_search(const int b[], int m, int val){
  assert(b);
  assert(m > 0);
  int low = 0;
  int high = m - 1;
  int med = 0;
  while(low <= high){
    med = (low + high) / 2;
    int temp = b[med];
    if(val < temp){
      high = med - 1;
    }else if(val > temp){
      low = med + 1;
    }else{
      return true;
    }
  }

  return false;
}

bool consec_sum(const int a[], int n, const int b[], int m) {
  assert(a);
  assert(b);
  assert(n > 1);
  assert(m > 1);
  for(int i = 0; i < n - 1; i++){
    int pair = a[i] + a[i+1];
    if(binary_search(b, m, pair)){
      return true;
    }
  }
  return false;
}

void even_first(int a[], int n) {
  assert(a);
  assert(n > 1);
  int oddpos = 0;

  for(int i = 0; i < n; i++){

    if(a[i] % 2 == 0){
      if(oddpos != i){
        int temp = a[i];
        a[i] = a[oddpos];
        a[oddpos] = temp;
      }
      oddpos+=1;
    }else{
      

    }
  }

}
