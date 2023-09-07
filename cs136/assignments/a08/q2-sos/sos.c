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

// This is the implementation of the sequence of strings (sos) ADT

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cs136-trace.h"
#include "string-io.h"
#include "sos.h"

//////////////////////////////////////////////////////////////////////////////
// DO NOT MODIFY THE FOLLOWING DEFINITIONS

struct sos {
  int len;
  int maxlen;
  char **data;
};

// we have provided sos_read() for you :)
// also, there is no need for you to test sos_read()

// see sos.h
struct sos *sos_read(void) {
  struct sos *seq = sos_create();
  while (1) {
    char *line = read_line();
    if (line == NULL) {
      break;
    }
    sos_insert_end(seq, line);
    free(line);
  }
  return seq;
}

//////////////////////////////////////////////////////////////////////////////

// The following are the functions you must implement

// We recommend that you complete them in the order below, as that may help
// facilitate your testing

// For example, we recommend you write the first few functions
// (create,destroy,length,insert_end,print)
// and then create your own simple tests (.in files) that sufficiently test
// those functions

// Once those functions are tested and debugged, write just one function
// at a time and test it before moving on to the next funciton

// Attempting to write all of the functions before you do any debugging or
// testing is an unwise strategy

//////////////////////////////////////////////////////////////////////////////

struct sos *sos_create(void) {
  struct sos *create = malloc(sizeof(struct sos));
  create->len = 0;
  create->maxlen = 1;
  create->data = malloc(sizeof(char*));
  return create;
}


void sos_destroy(struct sos *seq) {
  assert(seq);

  for(int i = 0; i < seq->len; i++){
    free(seq->data[i]);
  }

  free(seq->data);
  free(seq);
}


int sos_length(const struct sos *seq) {
  assert(seq);
  return seq->len;
}


void sos_insert_end(struct sos *seq, const char *s) {
  assert(seq);
  assert(s);

  // printf("%d\n%d\n", seq->len, seq->maxlen);
  char *dest = malloc((strlen(s)+1)*sizeof(char));
  // printf("hello\n");

  strcpy(dest, s);
  if(seq->len == seq->maxlen){
    seq->maxlen = 2 * seq->maxlen;
    seq->data = realloc(seq->data, seq->maxlen*sizeof(char *));
  }

  // printf("hello %d %d\n", seq->len, seq->maxlen);
  seq->data[seq->len] = dest;

  seq->len ++;

}


void sos_print(const struct sos *seq) {
  assert(seq);

  for(int i = 0; i < seq->len; i++){
    printf("%s\n", seq->data[i]);
  }

}


const char *sos_item_at(const struct sos *seq, int pos) {
  assert(seq);
  assert(0 <= pos && pos < seq->len);

  

  return seq->data[pos];
}


void sos_remove_end(struct sos *seq) {
  assert(seq);
  assert(seq->len > 0);

  free(seq->data[seq->len - 1]);
  seq->len -= 1;


}


void sos_insert_at(struct sos *seq, int pos, const char *s) {
  assert(seq);
  assert(s);
  assert(0 <= pos && pos <= seq->len);

  // char *dest = malloc((strlen(s)+1)*sizeof(char));
  sos_insert_end(seq, s);
  // printf("%d\n", seq->len);
  for(int i = seq->len - 1; i > pos; i--){
    // printf("%d\n", i);
    char *temp = seq->data[i];
    seq->data[i] = seq->data[i - 1];
    seq->data[i - 1] = temp;
  } 

}


void sos_remove_at(struct sos *seq, int pos){
  assert(seq);
  assert(0 <= pos && pos < seq->len);

  for(int i = pos; i < seq->len - 1; i++){
    char *temp = seq->data[i];
    seq->data[i] = seq->data[i+1];
    seq->data[i+1] = temp;
  }

  sos_remove_end(seq);

}


void sos_replace_at(struct sos *seq, int pos, const char *s) {
  assert(seq);
  assert(s);
  assert(0 <= pos && pos < seq->len);

  char *temp = malloc((strlen(seq->data[pos])+1)*sizeof(char));
  strcpy(temp, s);

  free(seq->data[pos]);
  seq->data[pos] = temp;
}


void sos_swap(struct sos *seq, int pos1, int pos2) {
  assert(seq);
  assert(0 <= pos1 && pos1 < seq->len);
  assert(0 <= pos2 && pos2 < seq->len);

  char *temp = seq->data[pos1];
  seq->data[pos1] = seq->data[pos2];
  seq->data[pos2] = temp;

}


struct sos *sos_dup(const struct sos *seq) {
  assert(seq);
  struct sos *temp = sos_create();
  // temp->maxlen = seq->maxlen;
  // temp->len = seq->len;
  // temp->data = realloc(temp->data, temp->maxlen*sizeof(char*));

  for(int i = 0; i < seq->len; i++){
    sos_insert_end(temp, seq->data[i]);
    // temp->data[i] = seq->data[i];
    
  }

  return temp;
}
