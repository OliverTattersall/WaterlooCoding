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

#include "next_ten_greater.h"
#include <assert.h>
// Assume this is the maximum array length (if you want/need it)
const int MAX_LEN = 10000;



// insert_into(result, len, val) inserts the value val into the array result which has max length 10
// requires: result is non-NULL, 0<=len<11
// effects: modifies result
// time: O(1), it does at most 10 iterations through the loop
static void insert_into(int result[], int len, int val){
  assert(result);
  assert(len>=0);
  assert(len<11);

  if(len==0){
    result[0] = val;
    return;
  }

  int sub = 0;

  if(len==10){
    if(val>result[9]){
      return;
    }else{
      result[9]=val;
      sub = -1;
    }
  }else{
    result[len]=val;
  }
  

  for(int i = len+sub; i > 0; i--){
    // printf("%d\n", result[i]);
    if(result[i]>result[i-1]){
      return;
    }else{
      int temp = result[i];
      result[i] = result[i-1];
      result[i-1] = temp;
    }
  }

}


// time: O(n)
//   justification: the loop runs n times with an O(1) operation, therefore O(n)
int next_ten_greater(const int arr[], int len, int value, int result[]) {
  assert(arr);
  assert(len>0);
  assert(result);
  // CHANGE THIS CODE
  int currentlen = 0;
  // int temp[MAX_LEN] = {0};
  for(int i = 0; i<len;i++){
    if(arr[i]>value){
      insert_into(result, currentlen, arr[i]);
      if(currentlen!=10){
        currentlen+=1;
      }
    }
  }
  return currentlen;
}

