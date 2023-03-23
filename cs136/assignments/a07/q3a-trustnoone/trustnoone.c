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
#include <stdbool.h>
#include "cs136-trace.h"

// is_valid_password(s) checks if a string is a valid password
// requires: s be non-NULL
// time: O(n) where n is the length of the string
bool is_valid_password(const char *s){
  assert(s);

  int len = 0;
  bool upper = false;
  bool lower = false;
  bool digit = false;
  bool special = false;

  int pos = 0;
  while( *(s+pos) != 0){
    char temp = *(s+pos);
    if('A'<= temp && temp <= 'Z'){
      upper = true;
    }else if('a'<= temp && temp <= 'z'){
      lower = true;
    }else if('0'<= temp && temp <= '9'){
      digit = true;
    }else if(temp <= ' '){
      return false;
    }else{
      special = true;
    }
    pos++;
    len += 1;
  }

  return upper && lower && digit && special && len>=8;
}

int main(void){
  assert(is_valid_password("Tru$tNo1"));
  assert(!is_valid_password("trustno1"));
  // add tests!
  trace_msg("ALL ASSERTIONS PASSED!")
}