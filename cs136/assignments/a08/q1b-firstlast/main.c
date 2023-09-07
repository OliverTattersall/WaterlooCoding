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

// This program is an introduction to using dynamic memory

// A "word" is a sequence of printable non-whitespace charcters (see modules/string-io.h)

// all words in the input are read in and then two words are printed out,
// each on a separate line:
// * the lexicographically "first" word, and then
// * the lexicographially "last" word

// (comparing public.in and public.expect will help illustrate)

// If no words appear in the input then "INVALID INPUT\n" is printed
// If only one word appears, it is both the first and the last word and so it
// is printed twice

// Words should be compared lexicographically using strcmp()
// (you do not have to worry about about upper case, lower case, etc... just use strcmp)

// All input should be read using read_word() (see modules/string-io.h)
// All output should be printed as printf("%s\n", ...)

// Remember, this is an exercise in using dynamic memory, so endeavour to
// use malloc and free appropriately, and don't forget that the strings
// returned by read_word() must eventually be freed

//////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "cs136-trace.h"
#include "string-io.h"

// io_driver() reads words from inputs and outputs the the lexicographically "first" word, and then
//             the lexicographially "last" word
// effects: reads input, produces output
// time: O(n+m) where n is number of inputs and m is length of largest word
void io_driver(void){
  
  char *temp_word = read_word();
  if(temp_word == NULL){
    printf("INVALID INPUT\n");
    return ;
  }
  int len = strlen(temp_word);


  char *first_name = temp_word;
  char *last_name = malloc((len+1)*sizeof(char));
  strcpy(last_name, temp_word);

  temp_word = NULL;
  bool change = false;
  int comp_val_first = 0;
  int comp_val_last = 0;
  

  while(1){
    change = false;

    temp_word = read_word();
    if(temp_word == NULL){
      break;
    }
    comp_val_first = strcmp(first_name, temp_word);


    if(comp_val_first > 0){
      free(first_name);
      first_name = temp_word;
      change = true;
      
      
    }

    comp_val_last = strcmp(last_name, temp_word);

    if(comp_val_last < 0){
      free(last_name);
      last_name = temp_word;
      change = true;
    }

    if(!change){
      free(temp_word);
    }
  }

  printf("%s\n", first_name);
  printf("%s\n", last_name);  

  free(first_name);
  free(last_name);
  // free(temp_word);

}


int main(void) {
  // some code snipits to get you started:
  // char *your_var_name = read_word();
  // printf("%s\n", ...);
  // printf("INVALID INPUT\n");
  io_driver();

}
