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

// This is the implementation of the counting Bloom filter ADT.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "countingbloomfilter.h"

// -----------------------------------------------------------------------
// DO NOT CHANGE THESE
// See countingbloomfilter.h for documentation
const int CBF_SUCCESS = 0;
const int CBF_FAILURE = 1;
// -----------------------------------------------------------------------

// See countingbloomfilter.h for documentation
struct countingbloomfilter {
  int *tables;
  int hash_len;
  int table_len;
  int nof_tables;
  int (*hash_funcs[5])(const char *, int);
  // Your fields go here.
};

// two_power(exp) returns the value of 2^exp
// requires: exp >= 0
// time: O(1)
static int two_power(int exp){
  assert(exp > 0);

  if(exp == 0){
    return 1;
  }
  int val = 2;
  return val << (exp - 1);

  // return val
  

}


// See countingbloomfilter.h for documentation
struct countingbloomfilter *cbf_create(int (**hash_funcs)(const char *, int),
                                       int hash_len, int nof_tables) { 
  // Your implementation goes here.

  assert(hash_funcs);
  assert(hash_len > 0);
  assert(nof_tables > 0);

  struct countingbloomfilter * result = malloc(sizeof(struct countingbloomfilter));
  result->hash_len = hash_len;
  result->nof_tables = nof_tables;
  result->table_len = two_power(hash_len);
  for(int i = 0; i<nof_tables; i++){
    result->hash_funcs[i] = hash_funcs[i];
  }
  // result->hash_funcs = hash_funcs;
  // printf("%d %d\n", result->table_len, nof_tables);
  result->tables = malloc((result->table_len * nof_tables)*sizeof(int));

  for(int t_idx = 0; t_idx < nof_tables; t_idx++){
    for(int i = 0; i < result->table_len; i++){
      result->tables[t_idx*result->table_len + i] = 0;
    }
  }
  

  return result;
}

// See countingbloomfilter.h for documentation
void cbf_destroy(struct countingbloomfilter *cbf) {
  // Your implementation goes here.

  assert(cbf);

  free(cbf->tables);
  free(cbf);

}

// See countingbloomfilter.h for documentation
void cbf_insert(struct countingbloomfilter *cbf, const char *key) {
  // Your implementation goes here.
  assert(cbf);
  assert(key);

  for(int t_idx = 0; t_idx < cbf->nof_tables; t_idx++){
    int temp_idx = cbf->hash_funcs[t_idx](key, cbf->hash_len);
    cbf->tables[t_idx * cbf->table_len + temp_idx] +=1;
  }



}

// See countingbloomfilter.h for documentation
bool cbf_lookup(const struct countingbloomfilter *cbf, const char *key) {
  // Your implementation goes here.
  assert(cbf);
  assert(key);

  for(int t_idx = 0; t_idx < cbf->nof_tables; t_idx++){
    int temp_idx = cbf->hash_funcs[t_idx](key, cbf->hash_len);
    if(cbf->tables[t_idx * cbf->table_len + temp_idx] == 0){
      return false;
    }
  }
  return true;
}

// See countingbloomfilter.h for documentation
int cbf_remove(struct countingbloomfilter *cbf, const char *key) {
  // Your implementation goes here.
  assert(cbf);
  assert(key);

  bool in = true;

  for(int t_idx = 0; t_idx < cbf->nof_tables; t_idx++){
    int temp_idx = cbf->hash_funcs[t_idx](key, cbf->hash_len);
    if(cbf->tables[t_idx * cbf->table_len + temp_idx] == 0){
      in = false;
    }
  }

  if(!in){
    return CBF_FAILURE;
  }

  for(int t_idx = 0; t_idx < cbf->nof_tables; t_idx++){
    int temp_idx = cbf->hash_funcs[t_idx](key, cbf->hash_len);
    cbf->tables[t_idx * cbf->table_len + temp_idx] -=1;
  }


  return CBF_SUCCESS;
}

// See countingbloomfilter.h for documentation
void cbf_print(const struct countingbloomfilter *cbf) {
  // Your implementation goes here.
  assert(cbf);
  // Use printf("%3d\n", foo); for printing counter foo.
  for(int t_idx = 0; t_idx < cbf->nof_tables; t_idx++){
    printf("table %d:\n", t_idx);
    for(int i = 0; i < cbf->table_len; i++){
      printf("%3d\n", cbf->tables[t_idx * cbf->table_len + i]);
    }
    
  }
}