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

// This is the implementation of the suggest module.

#include "suggest.h"
#include "triple-s.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

///////////////////////////////////////////////////////////////////////////// 
// do not modify this constant:
const int SUGGEST_MAX_STRLEN = 63;
/////////////////////////////////////////////////////////////////////////////
// add_replace_single(result, word, len, delete, cbf) creates all suggestions for word based on deleting one letter at a time and adds it result
// requires: result, word, delete, cbf be non-NULL
// effects: mutates result, mutates delete
// time: O(n)
static void add_delete_suggests(struct triple_s * result, const char *word, int len, char * delete, const struct countingbloomfilter *cbf){

  assert(result);
  assert(word);
  assert(delete);
  assert(cbf);
  // assert(len > 0);
  // char * delete = 
  strcpy(delete, word+1);
  delete[len - 1] = '\0';
  delete[len] = word[0];

  int index = 0;

  for(int i = 0; i < len; i++){
    bool valid = cbf_lookup(cbf, delete);
    if(valid){
      // char * temp_str = malloc(len*sizeof(char));
      // strcpy(temp_str, delete);
      // temp_str[len - 1] = '\0';
      sss_add(result, delete);
    }

    char temp = delete[index];
    delete[index] = delete[len];
    delete[len] = temp;
    index+=1;

  }

}

// add_replace_single(result, word, len, insert, cbf) creates all suggestions for word based on inserting one letter at a time and adds it result
// requires: result, word, insert, cbf be non-NULL
// effects: mutates result, mutates insert
// time: O(n)
static void add_single_inserts(struct triple_s * result, const char *word, int len, char * insert, const struct countingbloomfilter *cbf){

  assert(result);
  assert(word);
  assert(insert);
  assert(cbf);
  // assert(len > 0);

  strcpy(insert+1, word);
  // printf("good?\n");
  // insert[0] = 'a';

  for(int i = 0; i < len + 1; i++){
    if(i!=0){
      insert[i - 1] = word[i - 1];
    }

    // printf("check %d\n", i);
    // printf("%s\n", insert);
    for(char c = 'a'; c <= 'z'; c++){
      insert[i] = c;
      
      bool valid = cbf_lookup(cbf, insert);
      if(valid){
        // char * temp = malloc((len+2)*sizeof(char));
        // strcpy(temp, insert);
        
        // temp[len+1] = '\0';
        // printf("%s\n", temp);
        sss_add(result, insert);
      }
      
    }
    
  }

}


// add_replace_single(result, word, len, replace, cbf) creates all suggestions for word based on replacing one letter at a time and adds it result
// requires: result, word, replace, cbf be non-NULL
// effects: mutates result, mutates replace
// time: O(n)
static void add_replace_single(struct triple_s * result, const char *word, int len, char * replace, const struct countingbloomfilter *cbf){
  
  assert(result);
  assert(word);
  assert(replace);
  assert(cbf);
  // assert(len > 0);
  
  strcpy(replace, word);
  replace[len] = '\0';

  for(int i = 0; i < len; i++){
    
    replace[i] = word[i];
    for(char c = 'a'; c <= 'z'; c++){
      replace[i] = c;
      bool valid = cbf_lookup(cbf, replace);
      if(valid){
        // char * temp = malloc((len+1)*sizeof(char));
        // strcpy(temp, replace);
        // temp[len] = '\0';
        // // printf("%s\n", temp);
        sss_add(result, replace);
      }
    }

    replace[i] = word[i];

  }

}

// add_swaps(result, word, len, swap, cbf) creates all suggestions for word based on swapping adjacent letters and adds it result
// requires: result, word, swap, cbf be non-NULL
// effects: mutates result, mutates swap
// time: O(n)
static void add_swaps(struct triple_s * result, const char *word, int len, char * swap, const struct countingbloomfilter *cbf){

  assert(result);
  assert(word);
  assert(swap);
  assert(cbf);
  // assert(len > 0);

  strcpy(swap, word);
  swap[len] = '\0';

  for(int i = 0; i < len - 1; i++){
    char temp_c = swap[i];
    swap[i] = swap[i+1];
    swap[i+1] = temp_c;

    bool valid = cbf_lookup(cbf, swap);
    if(valid){
        // char * temp = malloc((len+1)*sizeof(char));
        // strcpy(temp, swap);
        // temp[len] = '\0';
        // // printf("%s\n", temp);
        sss_add(result, swap);
    }

    swap[i] = swap[i+1];
    swap[i+1] = temp_c;
    



  }

}

// time: O(n) where n is length of word. Justification O(n + 26 * (n+1) + 26 * n + (n-1)) = O(n)
struct triple_s *suggest(const struct countingbloomfilter *dict, 
                         const char *word) {
  // this is dummy code: replace it
  assert(dict);
  assert(word);
  assert(strlen(word) <= SUGGEST_MAX_STRLEN);

  struct triple_s *result = sss_create();

  int len = strlen(word);
  char * dummy_word = malloc((len+2)*sizeof(char));

  add_delete_suggests(result, word, len, dummy_word, dict);

  add_single_inserts(result, word, len, dummy_word, dict);

  add_replace_single(result, word, len, dummy_word, dict);

  add_swaps(result, word, len, dummy_word, dict);


  free(dummy_word);
  


  


  return result;
}
