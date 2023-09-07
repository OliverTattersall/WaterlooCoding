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
// login ID: None
//////////////////////////////////////////////////////////////////////////////////////////

// This is the implementation of the hash tree ADT with linked lists.

#include <stdlib.h>
#include "hashtable.h"
#include "cs136-trace.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

// -----------------------------------------------------------------------
// DO NOT CHANGE THESE
// See hashtable.h for documentation
const int HT_SUCCESS        = 0;
const int HT_ALREADY_STORED = 1;
const int HT_NOT_STORED     = 2;
// -----------------------------------------------------------------------

// See hashtable.h for documentation
struct hashtable {
  // Your fields go here.
  int len;
  int hash_length;
  struct llist **data;
  int (*hash_func)(const char *, int);
};

struct llnode {
  char * str;
  struct llnode *next;
};

struct llist {
  struct llnode *front;
  int len;
};

// two_power(exp) returns the value of 2^exp
// requires: exp >= 0
// time: O(1)
static int two_power(int exp){
  assert(exp >= 0);

  if(exp == 0){
    return 1;
  }
  int val = 2;
  return val << (exp - 1);

  // return val
  

}

// list_create() creates a new, empty linked list
// effects: allocates memory: call list_destroy
// time: O(1)
static struct llist *list_create(void) {
  struct llist *lst = malloc(sizeof(struct llist));
  lst->front = NULL;
  return lst;
}

// See hashtable.h for documentation
struct hashtable *ht_create(int (*hash_func)(const char *, int),
                            int hash_length) {
  // Your implementation goes here.
  int len = two_power(hash_length);
  struct hashtable * result = malloc(sizeof(struct hashtable));
  result->len = len;
  result->hash_length = hash_length;
  result->hash_func = hash_func;
  result->data = malloc(len*sizeof(struct llist *));

  // printf("here?\n");

  for(int i = 0; i < len; i++){
    result->data[i] = list_create();

  }

  return result;

  // return NULL;
}


// list_destroy(lst) free all allocated memory assiocated with lst
// requires: lst be non-NULL
// effects: frees memory
// time: O(n) where n is the length of the linked lst
static void list_destroy(struct llist *lst) {
  assert(lst);

  struct llnode *curnode = lst->front;
  struct llnode *nextnode = NULL;
  while (curnode) {
    nextnode = curnode->next;
    free(curnode->str);
    free(curnode);
    curnode = nextnode;
  }
  free(lst); 
}


// See hashtable.h for documentation
void ht_destroy(struct hashtable *ht) {
  assert(ht);
  // Your implementation goes here.

  for(int i = 0; i < ht->len; i++){
    list_destroy(ht->data[i]);
  }
  free(ht->data);
  free(ht);

}


// add_front(i, lst) adds i to the front of lst
// requires: str, lst be non-NULL
// effects: modifies lst
// time: O(1)
static void add_front(char *str, struct llist *lst) {
  assert(str);
  assert(lst);

  struct llnode *newnode = malloc(sizeof(struct llnode));
  newnode->str = str;
  newnode->next = lst->front;
  lst->front = newnode;
}


// find_str(str, lst) finds the index of the string str in the linked list lst, returning -1 if it is not in in
// requires: str, lst to be non-NULL;
// time: O(n) where n is the length of the list
static int find_str(const char *str, const struct llist *lst){
  assert(str);
  assert(lst);

  struct llnode* curnode = lst->front;


  int index = 0;

  while(curnode){
    if(strcmp(curnode->str, str) == 0){
      return index;
    }

    index +=1;
    curnode = curnode->next;
  }

  return -1;

}


// See hashtable.h for documentation
int ht_insert(struct hashtable *ht, const char *str) {
  assert(ht);
  assert(str);

  int hash_idx = ht->hash_func(str, ht->hash_length);
  int found = find_str(str, ht->data[hash_idx]);
  if(found != -1){
    return HT_ALREADY_STORED;
  }

  int len = strlen(str);
  char * new_str = malloc((len+1)*sizeof(char));
  strcpy(new_str, str);
  new_str[len] = '\0';

  add_front(new_str, ht->data[hash_idx]);

  return HT_SUCCESS;

}

// See hashtable.h for documentation
int ht_remove(struct hashtable *ht, const char *str) {

  assert(ht);
  assert(str);

  int hash_idx = ht->hash_func(str, ht->hash_length);

  struct llnode * curnode = ht->data[hash_idx]->front;
  struct llnode * prevnode = NULL;

  while(curnode){
    if(strcmp(curnode->str, str) == 0){

      struct llnode * next = curnode->next; 
      free(curnode->str);
      free(curnode);

      if(prevnode == NULL){
        ht->data[hash_idx]->front = next;
        return HT_SUCCESS;
      }

      prevnode->next = next;
      return HT_SUCCESS;


    }

    prevnode = curnode;
    curnode = curnode->next;


  }


  return HT_NOT_STORED;
}


// list_print(lst) prints the linked list lst from front to back
// requires: lst be non-NULL
// effects: produces output
// time: O(n) where n is the length of the linked list
static void list_print(const struct llist *lst) {
  assert(lst);
  struct llnode *curnode = lst->front;
  if (curnode == NULL) {
    printf("\n");
    return;
  }
  while (curnode) {
    printf("%s", curnode->str);
    curnode = curnode->next;
    if (curnode) {
      printf(" -> ");
    }
  }
  printf("\n");
}


// See hashtable.h for documentation
void ht_print(const struct hashtable *ht) {

  assert(ht);
  
  for(int i = 0; i < ht->len; i++){
    printf("%d: ", i);
    list_print(ht->data[i]);


  }

  // Your implementation goes here.
  // See public.expect for an example.
}