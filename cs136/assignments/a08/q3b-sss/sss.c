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

// Implementation of a triple_s (SSS) ADT

// This is a "wrapper" ADT that provides a triple_s ADT interface, but all of the data
// is actually stored inside of an SOS ADT

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "cs136-trace.h"
#include "sos.h"
#include "sss.h"

//////////////////////////////////////////////////////////////////////////////
// DO NOT MODIFY THE FOLLOWING DEFINITION

struct triple_s {
  struct sos *seq;
};

//////////////////////////////////////////////////////////////////////////////


struct triple_s *sss_create(void){
  struct triple_s *temp = malloc(sizeof(struct triple_s));
  temp->seq = sos_create();
  return temp;
}

void sss_destroy(struct triple_s *sss){
  assert(sss);
  sos_destroy(sss->seq);
  free(sss);
}

int sss_count(const struct triple_s *sss){
  assert(sss);

  return sos_length(sss->seq);
}


int sss_search(const struct triple_s *sss, const char *s){

  int first = 0;
  int end = sss_count(sss) - 1;
  int med = 0;
  while(first <= end){
    med = (end + first) / 2;
    const char *temp = sos_item_at(sss->seq, med);
    int comp_val = strcmp(temp, s);
    if(comp_val == 0){
      return med;
    }
    if(comp_val < 0){
      first = med + 1;
    }else{
      end = med - 1;
    }
  }


  return -1;
}

const char *sss_get(const struct triple_s *sss, int idx){
  return sos_item_at(sss->seq, idx);
}





void sss_add(struct triple_s *sss, const char *s){
  int find_idx = sss_search(sss, s);

  if(find_idx != -1){
    return;
  }

  int first = 0;
  int end = sss_count(sss) - 1;
  int med = 0;
  while(first <= end){
    med = (end + first) / 2;
    const char *temp = sos_item_at(sss->seq, med);
    int comp_val = strcmp(temp, s);
    if(comp_val < 0){
      first = med + 1;
    }else{
      end = med - 1;
    }
  }

  sos_insert_at(sss->seq, first, s);

}


void sss_add_follows(struct triple_s *sss, const char *s){
  assert(sss);
  assert(s);


  assert( strcmp(sss_get(sss, sss_count(sss) - 1), s) < 0);

  sos_insert_end(sss->seq, s);

}



void sss_remove(struct triple_s *sss, const char *s){
  assert(sss);
  assert(s);

  int find_idx = sss_search(sss, s);
  if(find_idx == -1){
    return;
  }

  sos_remove_at(sss->seq,find_idx);

}