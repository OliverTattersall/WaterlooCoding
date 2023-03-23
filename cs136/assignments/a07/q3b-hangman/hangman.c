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

#include <stdio.h>
#include "hangman-io.h"
#include "words.h"
#include <string.h>
#include <assert.h>
#include <stdbool.h>

const int max_word_length = 51;

// convert_to_upper(c) changes the character c to uppercase if it is lowercase, otherwise returns c
// time: O(1)
char convert_to_upper(char c){
    if('a'<=c && c<='z'){
        c = c - 'a' + 'A';
    }

    return c;
}

// is_letter(c) checks if c is a letter
// time: O(1)
bool is_letter(char c){
    if('a'<= c && c <= 'z'){
        return true;
    }else if('A' <= c && c <= 'Z'){
        return true;
    }else{
        return false;
    }
}

// print_string(s, len) prints the string s of length len
// requires: s be a valid pointer, len > 0
// effects: produces output
// time: O(len)
void print_string(const char s[], int len){
    assert(s);
    assert(len > 0);
    for(int i = 0; i < len; i++){
        printf("%c", s[i]);
    }
    printf("\n");
}

// get_guess(letters, strikes, c, string_len) loops until a valid input is taken, a character that has not been guess and is in the alphabet
// requires: letters, c be non-NULL, 0 <= strikes < max_strikes, string_len > 0
// effects: produces output, takes input, modifies letters
// time: O(n) where n is the number of failed inputs the user inputs
char get_guess(bool letters[], int strikes, const char c[], int string_len){
    assert(letters);
    assert(c);
    assert(string_len > 0);
    assert(0 <= strikes && strikes < max_strikes);

    char letter = ' ';
    
    while(1){
        scanf(" %c", &letter);
        if(!is_letter(letter)){
            printf(not_a_letter, letter);
            print_hangman(strikes);
            printf("%s", letter_prompt);

        }else if(letters[convert_to_upper(letter) - 'A']){
            
            printf(already_guessed_letter, convert_to_upper(letter));
            print_hangman(strikes);
            printf("%s", letter_prompt);
        }else{
            letters[convert_to_upper(letter) - 'A'] = true;
            break;
        }
        print_string(c, string_len);
    }

    return letter;
}

// io_driver() is the io driver for the hangman game
// effects: takes input, produces output
// time: O(n) where n is total number of inputs from user
void io_driver(void){
    int strikes = 0;
    bool letters[26] = {};


    printf(enter_game_number, max_words);
    int word_num = 0;
    scanf("%d", &word_num);

    while(!(1 <= word_num && word_num <= max_words)){
        printf("%s",invalid_game_number);
        printf(enter_game_number, max_words);
        scanf("%d", &word_num);
    }

    const char *s = get_word(word_num);
    const int string_len = strlen(s);
    int missing_letters = string_len;

    char c[51] = {};
    for(int i = 0; i < string_len; i++){
        if(s[i]!=' '){
            c[i] = '*';
        }else{
            c[i] = ' ';
            missing_letters-=1;
        }
        
    }
    c[string_len] = '\0';

    print_hangman(strikes);

    
    while(strikes!=max_strikes && missing_letters > 0){
        printf("%s", letter_prompt);
        print_string(c, string_len);
        char guess = get_guess(letters, strikes, c, string_len);
        guess = convert_to_upper(guess);
        // printf("||%c||\n", guess);
        bool change = false;
        for(int i = 0; i < string_len; i++){
            if(s[i]==guess){
                c[i]=guess;
                change = true;
                missing_letters-=1;
            }
        }

        if(!change){
            printf(not_in_word, guess);
            strikes+=1;
            if(max_strikes - strikes != 0){
                printf(not_last_guess, max_strikes-strikes);
            }
            // else{
            //     printf("\n");
            // }
            
        }

        // if(max_strikes - strikes == 0){
        //     print_string(c, string_len);
        // }
        if(missing_letters!=0){
            print_hangman(strikes);
        }
        
    }

    // printf("\n\n");

    // printf("%s", s);

    if(missing_letters == 0){
        printf(congratulations, s);

    }else{
        printf(game_over, s);
    }
    
    printf("%s", play_again);
    char response = ' ';
    scanf(" %c", &response);
    response = convert_to_upper(response);
    while(response!='Y' && response != 'N'){
        printf("%s", invalid_play_again_response);
        printf("%s", play_again);
        scanf(" %c", &response);
        response = convert_to_upper(response);
        
    }

    if(response == 'Y'){
        io_driver();
    }
    


}


int main(void) {

    io_driver();

}
