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

// This is the implementation of the generic hash table ADT with binary search 
//   trees.

#include <stdlib.h>
#include "hashtable.h"
#include "cs136-trace.h"
#include <assert.h>
#include <stdbool.h>
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
  int hash_len;
  struct bst **data;

  void *(*key_clone)(const void *);
  int (*hash_func)(const void *, int);
  int (*key_compare)(const void *, const void *);
  void (*key_destroy)(void *);
  void (*key_print)(const void *);


};

struct bstnode {
  void * item;
  struct bstnode *left;
  struct bstnode *right;
  // int count;
};

struct bst {
  struct bstnode *root;
};

// bst_create() creates a new BST
// effects: allocates memory: call bst_destroy
// time: O(1)
static struct bst *bst_create(void) {
  struct bst *t = malloc(sizeof(struct bst));
  t->root = NULL;
  return t;
}


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

// See hashtable.h for documentation
struct hashtable *ht_create(void *(*key_clone)(const void *),
                            int (*hash_func)(const void *, int), 
                            int hash_length,
                            int (*key_compare)(const void *, const void *),
                            void (*key_destroy)(void *),
                            void (*key_print)(const void *)) {
  // Your implementation goes here.
  
  struct hashtable * result = malloc(sizeof(struct hashtable));

  int len = two_power(hash_length);
  result->hash_len = hash_length;
  result->len = len;
  result->hash_func = hash_func;
  result->data = malloc(len * sizeof(struct bst));
  result->key_compare = key_compare;
  result->key_destroy = key_destroy;
  result->key_print = key_print;
  result->key_clone = key_clone;
  
  for(int i = 0; i < len; i++){
    result->data[i] = bst_create();
  }

  return result;

  return NULL;

}

// bstnode_destroy(node, key_destroy) deallocates all dynamically allocated memory
//   within the entire bst
// requires: key_destroy be non-NULL
// effects : the memory at node is invalid (freed)
// time : O(n) where n is number of nodes in the bst
static void bstnode_destroy(struct bstnode *node, void (*key_destroy)(void *)) {
  // assert(node);
  assert(key_destroy);

  if (node) {
    bstnode_destroy(node->left, key_destroy);
    bstnode_destroy(node->right, key_destroy);
    key_destroy(node->item);
    free(node);
  }
}

// bst_destroy(node, key_destroy) deallocates all dynamically allocated memory
//   within the entire bst
// effects : the memory at node is invalid (freed)
// time : O(n) where n is number of nodes in the bst
static void bst_destroy(struct bst *t, void (*key_destroy)(void *)) {
  assert(t);
  bstnode_destroy(t->root, key_destroy);
  free(t);
}



// See hashtable.h for documentation
void ht_destroy(struct hashtable *ht) {
  // Your implementation goes here.
  for(int i = 0; i < ht->len; i++){
    bst_destroy(ht->data[i], ht->key_destroy);
  }

  free(ht->data);
  free(ht);

}

// new_leaf(item) creates a new bstnode
// requires: item be non-NULL
// effects: allocates memory, must be freed by client
// time: O(1)
static struct bstnode *new_leaf(void * item) {
  assert(item);

  struct bstnode *leaf = malloc(sizeof(struct bstnode)); 
  leaf->item = item;
  leaf->left = NULL;
  leaf->right = NULL;
  return leaf;
}


// insert_bstnode(item, node, key_compare) adds item to the bst, return HT_ALREADY_STORED if it already exists in the bst
// requires item, node, key_compare be non-NULL
// effects: allocates memory, must be freed by client
// time: O(n)
static int insert_bstnode(void * item, struct bstnode *node, int (*key_compare)(const void *, const void *)) {
  assert(item);
  assert(node);
  assert(key_compare);

  if(key_compare(item, node->item) < 0){
    if(node->left){
      return insert_bstnode(item, node->left, key_compare);
    }else{
      node->left = new_leaf(item);
      return HT_SUCCESS;
    }
  }else if(key_compare(item, node->item) > 0){
    if(node->right){
      return insert_bstnode(item, node->right, key_compare);
    }else{
      node->right = new_leaf(item);
      return HT_SUCCESS;
    }
  }

  return HT_ALREADY_STORED;
}
    

// bst_insert(item, t, key_compare) adds item to the bst, return HT_ALREADY_STORED if it already exists in the bst
// requires item, t, key_compare be non-NULL
// effects: allocates memory, must be freed by client
// time: O(n)
static int bst_insert(void * item, struct bst *t, int (*key_compare)(const void *, const void *)) {
  assert(item);
  assert(t);
  assert(key_compare);

  if (t->root) {
    return insert_bstnode(item, t->root, key_compare);
  } else {
    t->root = new_leaf(item);
    return HT_SUCCESS;
  }
}


// See hashtable.h for documentation
int ht_insert(struct hashtable *ht, const void *key) {
  // Your implementation goes here.
  assert(ht);
  assert(key);


  void * temp = ht->key_clone(key);

  int hash_idx = ht->hash_func(key, ht->hash_len);

  return bst_insert(temp, ht->data[hash_idx], ht->key_compare); 



}


// bst_remove(item, t, key_compare, key_destroy) removes item from the bst t, returning HT_NOT_STORED if the item is not in the irem
// requires: item, t, key_compare, key_destroy be non-NULL
// effects: frees memory associated with the item stored in the tree
// time: O(n) 
static int bst_remove(const void * item, struct bst *t, int (*key_compare)(const void *, const void *), void (*key_destroy)(void *) ){

  assert(item);
  assert(t);
  assert(key_compare);
  assert(key_destroy);


  struct bstnode * target = t->root;
  struct bstnode * parent = NULL;

  while(target){
    int comp_val = key_compare(target->item, item);
    if(comp_val == 0){
      break;
    }
    parent = target;
    if(comp_val < 0){
      target = target->left;
    }else{
      target = target->right;
    }

  }

  if(target == NULL){
    return HT_NOT_STORED;
  }


  struct bstnode * replacement = NULL;
   if (target->left == NULL) {
    replacement = target->right;
  } else if (target->right == NULL) {
    replacement = target->left;
  } else {
    // neither child is NULL:
    // find the replacement node and its parent
    replacement = target->right;
    struct bstnode *replacement_parent = target;
    while (replacement->left) {
      replacement_parent = replacement;
      replacement = replacement->left;
    }
    // update the child links for the replacement and its parent
    replacement->left = target->left;
    if (replacement_parent != target) {
      replacement_parent->left = replacement->right;
      replacement->right = target->right;
    }
  }

  bstnode_destroy(target, key_destroy);
  if (parent == NULL) {
    t->root = replacement;
    
  } else if( key_compare(item, parent->item) > 0) {
    parent->right = replacement;
  } else {
    parent->left = replacement;
  }

  return HT_SUCCESS; 

}


// See hashtable.h for documentation
int ht_remove(struct hashtable *ht, const void *key) {
  // Your implementation goes here.
  assert(ht);
  assert(key);

  int hash_idx = ht->hash_func(key, ht->hash_len);
  return bst_remove(key, ht->data[hash_idx], ht->key_compare, ht->key_destroy);



  return -1;
}


// bstnode_print(node, first) Print the current node. Proceed by a comma
//   if it is not *first, otherwise makes other nodes not *first.
// requires : node, first, and key_print are not NULL
// effects : prints output, may mutate *first
// time : O(1)
static void bstnode_print(struct bstnode *node, bool *first, void (*key_print)(const void *), int level) {
  assert(node);
  assert(first);
  assert(key_print);

  if (*first) {
    *first = false;
  } else {
    printf(",");
  }
  printf("%d-", level);
  key_print(node->item);
  // printf("%d", node->item);
}

// bstnodes_print(node, first) Print the sub-tree rooted at node in
//   in order from smallest to largest. Procced by a comma if not *first, 
//   otherwise updates *first.
// requires : first, key_print is not NULL, level >= 0
// effects : prints output, may mutate first
// time : O(n)
static void bstnodes_print(struct bstnode *node, bool *first, void (*key_print)(const void *), int level) { 
  assert(first);
  assert(level >= 0);
  assert(key_print);
  if (node) {
    bstnodes_print(node->left, first, key_print, level+1);
    bstnode_print(node, first, key_print, level);
    bstnodes_print(node->right, first, key_print, level+1);
  }
}

// bst_print(t, key_print) prints the bst t from left to right
// requires: t, key_print be non-NULL
// effects: prints output
// time: O(n)
void bst_print(struct bst *t, void (*key_print)(const void *)) {
  assert(t);
  assert(key_print);

  bool first = true;
  printf("[");
  bstnodes_print(t->root, &first, key_print,0);
  printf("]\n");
}



// See hashtable.h for documentation
void ht_print(const struct hashtable *ht) {
  assert(ht);
  // Your implementation goes here.
  // See string_public.expect and fancyline_public.expect for examples.
  for(int i = 0; i < ht->len; i++){
    printf("%d: ", i);
    bst_print(ht->data[i], ht->key_print);
  }

}