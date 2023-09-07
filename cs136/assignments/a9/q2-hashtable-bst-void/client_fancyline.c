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

// This is the implementation of the fancy client module and client.

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cs136-trace.h"
#include "read.h"
#include "hash.h"
#include "hashtable.h"
#include "client_fancyline.h"

// === FANCY LINE MODULE ======================================================

// fancyline represents a fancy line consisting of a printable symbol and a
//   length.
struct fancyline {
  // Your fields go here.
  int len;
  // char * s;
  char sym;
};

// requires: all functions require valid (non-NULL) parameters

// fl_create(sym, len) creates a new fancy line consisting of symbol sym 
//   and of length len.
// requires: sym must be printable and non-whitespace and len must be > 0
// effects: allocate heap memory, client must call destroy
// time: O(1)
static struct fancyline *fl_create(char sym, int len) {
  assert(sym >= 33);
  assert(len > 0);
  // Your implementation goes here.

  struct fancyline * result = malloc(sizeof(struct fancyline));
  result->len = len;
  result->sym = sym;
  // result->s = malloc((len+1)*sizeof(char));
  // for(i)

  return result;
}

// fl_destroy(fl) releases all resources used by fl.
// effects: fl becomes invalid
// time: O(1)
static void fl_destroy(struct fancyline *fl) {
  // Your implementation goes here.
  assert(fl);
  free(fl);
}

// fl_print(fl) prints the fancy line's symbol length times
// effects: creates output
// time: O(n) where n is the length of the fancy line
static void fl_print(const struct fancyline *fl) {
  assert(fl);
  // Your implementation goes here.
  // Look at fancyline_public.expect for examples.
  for(int i = 0; i < fl->len; i++){
    printf("%c", fl->sym);
  }
  // printf("\n");

}

// fl_clone(fl) creates a duplicate of fl.
// effects: allocate heap memory, client must call fl_destroy
// time: O(1)
static struct fancyline* fl_clone(const struct fancyline *fl) {
  assert(fl);
  // Your implementation goes here.
  struct fancyline * result = malloc(sizeof(struct fancyline));
  result->len = fl->len;
  result->sym = fl->sym;

  return result;
}

// fl_hash(fl, hash_len) calculates the hash value of fl with a length
//   of hash_len bits.
// requires: hash_len must be between 2 and 16 (both inclusive)
// time: O(1)
static int fl_hash(const struct fancyline *fl, int hash_len) {
  assert(fl);
  assert(2 <= hash_len && hash_len <= 16);
  // Your implementation goes here.
  // The hash value of a fancy line consisting of symbol sym is 
  //   hash_char(sym, hash_len). hash_char is provided by the hash module.
  return hash_char(fl->sym, hash_len);
}

// fl_compare(fl1, fl2) compares fl1 and fl2 and returns the following
//   values:
//   * < 0: fl1 comes before fl2,
//   * = 0: fl1 and fl2 are equal, and
//   * > 0: fl1 comes after fl2.
// time: O(1)
static int fl_compare(const struct fancyline *fl1, 
  const struct fancyline *fl2) {
  assert(fl1);
  assert(fl2);
  // Your implementation goes here.

  if(fl1->len > fl2->len){
    return 1;
  }else if (fl1->len < fl2->len){
    return -1;
  }else{
    if(fl1->sym > fl2->sym){
    return 1;
    }else if(fl1->sym < fl2->sym){
    return -1;
    }else{
    return 0;
    }
  }

  
  // Look at fancyline_public.expect to figure out the most likely
  // order relationship between fancy lines.
  return 0;
}

// === CONNECTORS =============================================================

// There is no need to add additional documentation to the connectors

// fl_adt_clone(ptr) connects to fl_clone.
static void *fl_adt_clone(const void *ptr) {
  assert(ptr);
  // Your implementation goes here.
  const struct fancyline * result = ptr;
  // void * result = fl_clone(ptr);
  // placeholder invocation of fl_clone to ensure that Marmoset does not 
  // complain about the function not being used, you need to update the
  // invocation
  // fl_clone(NULL);   
  return fl_clone(result);
}

// fl_adt_hash(ptr, hash_len) connects to fl_hash.
static int fl_adt_hash(const void *ptr, int hash_len) {
   // Your implementation goes here.
  assert(ptr);
  assert(2 <= hash_len && hash_len <= 16);

  const struct fancyline * result = ptr;
  // placeholder invocation of fl_clone to ensure that Marmoset does not 
  // complain about the function not being used, you need to update the
  // invocation
  
  return fl_hash(result, hash_len);
}

// fl_adt_compare(ptr1, ptr2) connects to fl_compare.
static int fl_adt_compare(const void *ptr1, const void *ptr2) {
  assert(ptr1);
  assert(ptr2);
  // Your implementation goes here.
  const struct fancyline * result1 = ptr1;
  const struct fancyline * result2 = ptr2;
  // placeholder invocation of fl_clone to ensure that Marmoset does not 
  // complain about the function not being used, you need to update the
  // invocation
  
  return fl_compare(result1, result2);
}

// fl_adt_destory(ptr) connects to fl_destroy.
static void fl_adt_destroy(void *ptr) {
  assert(ptr);
  // Your implementation goes here.
  struct fancyline * result = ptr;
  fl_destroy(result);
}

// fl_adt_print(ptr) connects to fl_print.
static void fl_adt_print(const void *ptr) {
  assert(ptr);
  // Your implementation goes here.
  const struct fancyline * result = ptr;
  fl_print(result);
}

/// === CLIENT FUNCTION =======================================================

// See client_fancyline.h for documentation.
void client_fancyline(void) {

  // Enable the return statement below when you have not implemented the
  // fancy line module but want to test your hash table implementation with the 
  // string client only.
  // return;

  const int CREATE = lookup_symbol("HASHTABLE");
  const int INSERT = lookup_symbol("INSERT");
  const int REMOVE = lookup_symbol("REMOVE");
  const int PRINT = lookup_symbol("PRINT");

  int cmd = read_symbol();
  assert(cmd == CREATE);
  int hash_length = -1;
  assert(scanf("%d", &hash_length) == 1);
  assert(2 <= hash_length && hash_length <= 16);

  struct hashtable *ht = ht_create(fl_adt_clone, 
                                   fl_adt_hash, hash_length, 
                                   fl_adt_compare,
                                   fl_adt_destroy,
                                   fl_adt_print);

  while ((cmd = read_symbol()) != INVALID_SYMBOL) {
    if (cmd == INSERT) {
      char symbol;
      assert(scanf(" %c", &symbol) == 1);
      int length;
      assert(scanf("%d", &length) == 1);
      struct fancyline *fl = fl_create(symbol, length);
      int status = ht_insert(ht, fl);
      if (status == HT_SUCCESS) {
        fl_print(fl);
        printf(" inserted into the hash table.\n");
      } else {
        fl_print(fl);
        printf(" is already stored in the hash table.\n");
      }
      fl_destroy(fl);
    } else if (cmd == REMOVE) {
      char symbol;
      assert(scanf("%c", &symbol) == 1);
      int length;
      assert(scanf("%d", &length) == 1);
      struct fancyline *fl = fl_create(symbol, length);
      int status = ht_remove(ht, fl);
      if (status == HT_SUCCESS) {
        printf("SUCCESS: ");
        fl_print(fl);
        printf(" removed from the hash table.\n");
      } else {
        printf("WARNING: ");
        fl_print(fl);
        printf(" not removed from the hash table.\n");
      }
      free(fl);
    } else if (cmd == PRINT) {
      ht_print(ht);
    } else {
      printf("ERROR: unknown command\n");
      break;
    }
  }

  ht_destroy(ht);
}
