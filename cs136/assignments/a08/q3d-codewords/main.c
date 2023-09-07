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

// This program uses a "codebook" to convert from characters into words (or "codewords")

// The first line must be one of: CODEBOOK=MORSE CODEBOOK=NATO or CODEBOOK=CUSTOM
// which identifies the codebook to use (from modules/morse.c, modules/nato.c and custom.c respectively)

// To motivate this question, it might help to understand the NATO codebook (alphabet)

// The NATO alphabet is especially useful when speaking over noisy channels or in
// noisy environments, where it is often important to ensure there is no miscommunication.

// For example, when communicating your postal code, an 'E' might sound like a 'G'.
// Instead, you can use the NATO phonetic alphabet to say "Echo" or "Golf" instead.
// Phonetic alphabets are designed with words that are less likely to be misunderstood.
// "Golf" is a unique enough word that it doesn't sound like any other words.
// Instead of saying "GG" you'd say "Golf Golf".

// The codebook is stored in an SOS, where each entry in the SOS corresponds to the code
// to be used for the corresponding character, indexed by ASCII values.
// The ASCII value 'G' is 71, so the string "Golf" is stored at position 71 in the
// NATO codebook.

// If the codebook entry for an ASCII value is the empty string ("") 
// then the character is ignored (e.g., most punctuation is ignored in the NATO codebook)

// The codebook might have string at position zero, corresponding to the character '\0',
// in which case that string must be put at the end of every codestring generated.

// A space is placed in-between every codeword.

// As a final example, the string "GG! GG!" would produce the string:
// "Golf Golf Space Golf Golf Stop."
// Where the '!'s are ignored because their entry in the codebook is "" and the
// string "Stop." is at position zero in the codebook.
// Note that there is a space in-between the words but not at the end.
// (this is a common mistake and hard to "see" when testing your code)

//////////////////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cs136-trace.h"
#include "sos.h"
#include "string-io.h"
#include "nato.h"
#include "morse.h"
#include "custom.h"

// codestring(codebook, str) generates and returns a new string, where the characters in str
//   are converted to the corresponding codewords in seq (see description above)
// note: codestring always returns a valid string, but it may be empty ("")
// requires: seq is a valid sos (not NULL)
//           str is a valid string (not NULL and zero-terminated)
// effects: allocates memory (caller must free)
// time: O(n + m) where n is the length of str, and m is the length of the produced string
char *codestring(const struct sos *codebook, const char *str) {
  assert(codebook);
  assert(str);

  // char *test = "Mike Oscar November Kilo Echo Yankee Stop.";
  // printf("%lu\n", strlen(test));

  int len = strlen(str);
  if(len == 0){
    char *spaces = malloc(sizeof(char));
    spaces[0] = '\0';
    return spaces;
  }
  int letter_count = 0;
  for(int i = 0; i < len + 1; i++){
    char temp = str[i];
    const char *temp_str = sos_item_at(codebook, temp);
    int temp_count = strlen(temp_str);
    letter_count += temp_count;
    
    // if(temp_count == 0){
    //   space_count -=1;
    // }

  }

  if(letter_count == 0){
    char *spaces = malloc(sizeof(char));
    spaces[0] = '\0';
    return spaces;
  }
  // printf("%d\n", letter_count);
  int final_len = len + letter_count + 1;
  // printf("%d\n", final_len);
  char *final_str = malloc((final_len) * sizeof(char));
  int pos = 0;
  for(int i = 0; i < len + 1; i++){
    char temp = str[i];
    const char *temp_str = sos_item_at(codebook, temp);
    strcpy((final_str+pos), temp_str);
    // printf("%s\n", temp_str);
    int temp_count = strlen(temp_str);
    if(temp_count == 0){
      continue;
    }
    pos += temp_count;
    
    final_str[pos] = ' ';
    pos += 1;
    
    
    
  }
  // if(pos > (final_len - 1)){
  //   printf("oh no\n");
  // }
  // printf("%d %d\n", pos, final_len - 1);
  final_str[pos - 1] = '\0';
  // final_str[final_len - 1] = '\0';


  return final_str;
}


// you should not need to modify main()

int main(void) {
  struct sos *codebook = NULL;
  char *codebook_name = read_line();
  if (codebook_name == NULL) {
    return 0;
  }
  if (!strcmp(codebook_name, "CODEBOOK=NATO")) {
    codebook = build_nato_codebook();
  } else if (!strcmp(codebook_name, "CODEBOOK=MORSE")) {
    codebook = build_morse_codebook();
  } else if (!strcmp(codebook_name, "CODEBOOK=CUSTOM")) {
    codebook = build_custom_codebook();
  }
  free(codebook_name);
  if (codebook == NULL) {
    return 0;
  }
  while (1) {
    char *line = read_line();
    if (line == NULL) {
      break;
    }
    char *encoded = codestring(codebook, line);
    printf("%s\n", encoded);
    free(encoded);
    free(line);
  }
  sos_destroy(codebook);
}
