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

// This is the implementation of the cuckoo filter ADT.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cs136-trace.h"
#include "cuckoofilter.h"
#include "random.h"

// -----------------------------------------------------------------------
// DO NOT CHANGE THESE
// See cuckoofilter.h for documentation
const int CUCKOO_SUCCESS = 0;
const int CUCKOO_FAILURE = 1;
// -----------------------------------------------------------------------

// See cuckoofilter.h for documentation
struct cuckoofilter {
  // Your fields go here.
  int (*hash_func)(const char *, int);
  int hash_len;
  int len;
  int max_num_kicks;
  int fp_len;
  int nof_entries;
  char **data;

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


// See cuckoofilter.h for documentation
struct cuckoofilter *cuckoo_create(int (*hash_func)(const char *, int), 
                                  int hash_len, int nof_entries, int fp_len, 
                                  int max_num_kicks) {
  // Your implementation goes here.
  assert(hash_func);
  assert(hash_len > 0);
  assert(nof_entries > 0);
  assert(fp_len > 0);
  assert(max_num_kicks > 0);

  struct cuckoofilter * result = malloc(sizeof(struct cuckoofilter));
  int len = two_power(hash_len);
  result->hash_len = hash_len;
  result->len = len;
  result->hash_func = hash_func;
  result->nof_entries = nof_entries;
  result->max_num_kicks = max_num_kicks;
  result->data = malloc(len*nof_entries*sizeof(char *));
  result->fp_len = fp_len;
  for(int i = 0; i < len; i++){
    for(int j = 0; j < nof_entries; j++){
      result->data[i * nof_entries + j] = NULL;
    }
  }
  

  return result;
}

// See cuckoofilter.h for documentation
void cuckoo_destroy(struct cuckoofilter *cf) {
  // Your implementation goes here.
  assert(cf);

  for(int i = 0; i < cf->len; i++){
    for(int j = 0; j < cf->nof_entries; j++){
      if(cf->data[i*cf->nof_entries + j] != NULL){
        free(cf->data[i*cf->nof_entries + j]);
        cf->data[i*cf->nof_entries + j] = NULL;
      }else{
        break;
      }
    }
  }

  free(cf->data);
  free(cf);

}


// fingerprint(key, fp_len) returns a new string with the first fp_len characters
// requires: key be non-NULL, fp_len > 0
// effects: allocates memory, must be freed by client
static char * fingerprint(const char *key, int fp_len){

  assert(key);
  assert(fp_len > 0);

  int n = strlen(key); 

  int count = 0;

  // printf("%d\n", fp_len);

  char * result = malloc((fp_len + 1)*sizeof(char));
  for(int i = 0; i < fp_len; i++){
    if(i >= n){
      break;
    }
    result[i] = key[i];
    count +=1;
  }

  result[count] = '\0';

  return result;

}


// See cuckoofilter.h for documentation
int cuckoo_insert(struct cuckoofilter *cf, const char *key) {
  // Your implementation goes here.
  assert(cf);
  assert(key);

  char * f = fingerprint(key, cf->fp_len); // fingerprint

  int i_1 = cf->hash_func(key, cf->hash_len);
  int i_2 = i_1 ^ cf->hash_func(f, cf->hash_len);

  for(int i = 0; i < cf->nof_entries; i++){
    if(cf->data[i_1 * cf->nof_entries + i] == NULL){
      cf->data[i_1 * cf->nof_entries + i] = f;
      return CUCKOO_SUCCESS;
    }
  }

  for(int i = 0; i < cf->nof_entries; i++){
    if(cf->data[i_2 * cf->nof_entries + i] == NULL){
      cf->data[i_2 * cf->nof_entries + i] = f;
      return CUCKOO_SUCCESS;
    }
  }

  int flip = toin_coss();
  int idx = -1;
  if(!flip){
    idx = i_1;
    
  }else{
    idx = i_2;
  }


  for(int i = 0; i < cf->max_num_kicks; i++){
    char **e = random_bucket_entry(&cf->data[idx], cf->nof_entries);
    char *temp = f;
    f = e[0];
    e[0] = temp;

    idx = idx ^ cf->hash_func(f, cf->hash_len);
    for(int j = 0; j < cf->nof_entries; j++){
      if(cf->data[idx * cf->nof_entries + j] == NULL){
        cf->data[idx * cf->nof_entries + j] = f;
        return CUCKOO_SUCCESS;
      }
    }

  }

  return CUCKOO_FAILURE;
}

// See cuckoofilter.h for documentation
bool cuckoo_lookup(const struct cuckoofilter *cf, const char *key) {
  // Your implementation goes here.
  assert(cf);
  assert(key);

  char * temp_f = fingerprint(key, cf->fp_len);
  int i_1 = cf->hash_func(key, cf->hash_len);
  int i_2 = i_1 ^ cf->hash_func(temp_f, cf->hash_len);

  for(int i = 0; i < cf->nof_entries; i++){
    if(cf->data[i_1 * cf->nof_entries + i] == NULL){
      break;
    }
    int compval = strcmp(temp_f, cf->data[i_1 * cf->nof_entries + i]);
    if(compval == 0){

      free(temp_f);
      return true;
    }

  }

  // printf("made it here\n");

  for(int i = 0; i < cf->nof_entries; i++){
    if(cf->data[i_2 * cf->nof_entries + i] == NULL){
      break;
    }
    int compval = strcmp(temp_f, cf->data[i_2 * cf->nof_entries + i]);
    if(compval == 0){
      free(temp_f);
      return true;
    }

  }

  free(temp_f);
  return false;
}

// See cuckoofilter.h for documentation
int cuckoo_remove(struct cuckoofilter *cf, const char *key) {
  // Your implementation goes here.

  assert(cf);
  assert(key);

  char * temp_f = fingerprint(key, cf->fp_len);
  int i_1 = cf->hash_func(key, cf->hash_len);
  int i_2 = i_1 ^ cf->hash_func(temp_f, cf->hash_len);

  bool found = false;

  for(int i = 0; i < cf->nof_entries; i++){
    if(cf->data[i_1 * cf->nof_entries + i] == NULL){
      break;
    }
    if(!found){
      int compval = strcmp(temp_f, cf->data[i_1 * cf->nof_entries + i]);
      if(compval == 0){
        found = true;
        free(temp_f);
        free(cf->data[i_1 * cf->nof_entries + i]);
        cf->data[i_1 * cf->nof_entries + i] = NULL;
        
      }
    }else{
      // char * temp = cf->data[i_1 * cf->nof_entries + i - 1];
      cf->data[i_1 * cf->nof_entries + i - 1] = cf->data[i_1 * cf->nof_entries + i];
      // cf->data[i_1 * cf->nof_entries + i] = temp;
    }
    

  }

  if(found){
    return CUCKOO_SUCCESS;
  }

  for(int i = 0; i < cf->nof_entries; i++){
    if(cf->data[i_2 * cf->nof_entries + i] == NULL){
      break;
    }
    if(!found){
      int compval = strcmp(temp_f, cf->data[i_2 * cf->nof_entries + i]);
      if(compval == 0){
        found = true;
        free(temp_f);
        free(cf->data[i_2 * cf->nof_entries + i]);
        cf->data[i_2 * cf->nof_entries + i] = NULL;
        
      }
    }else{
      // char * temp = cf->data[i_2 * cf->nof_entries + i - 1];
      cf->data[i_2 * cf->nof_entries + i - 1] = cf->data[i_2 * cf->nof_entries + i];
      // cf->data[i_2 * cf->nof_entries + i] = temp;
    }
    

  }

  free(temp_f);

  if(found){
    return CUCKOO_SUCCESS;
  }

  return CUCKOO_FAILURE;
}

// See cuckoofilter.h for documentation
void cuckoo_print(const struct cuckoofilter *cf) {
  // Your implementation goes here.
  // Use printf("%3d: ", foo); for printing labels for the entries.
  assert(cf);
  for(int i = 0; i < cf->len; i++){

    printf("bucket %d:\n", i);

    for(int j = 0; j < cf->nof_entries; j++){
      printf("%3d: ", j);
      if(cf->data[i * cf->nof_entries + j] != NULL){
        printf("%s", cf->data[i * cf->nof_entries + j]);
      }
      printf("\n");
    }


  }

}
