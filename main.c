#include <stdio.h>

#include "string_properties.h"

short print_seq(char *, short);
void reverse_word(const char[WORD + 1], char[WORD + 1]);

int main() 
{
     char text[TEXT + 1] = {'\0'}, word[WORD + 1] = {'\0'};
     size_t i;
     
     /* Read the word. */
     for (i = 0; i < WORD; i++) {
          word[i] = getchar();

          if (isspace(word[i])) {
               word[i] = '\0';
               break;
          }
     }

     /* Read the text. */
     for (i = 0; i < TEXT; i++) {
          text[i] = getchar();

          if (text[i] == '~') {
               text[i] = '\0';
               break;
          }
     }
     i = 0;

     char * seq;
     short printed = FALSE;
     
     printf("Gematria Sequences: ");

     size_t word_val = 0;
     while (word[i] != '\0') {
          word_val += gematria_val(word[i]);
          i++;
     }
     i = 0;

     while (text[i] != '\0') {
          seq = gematria_seq(text, word_val, i);
          printed = print_seq(seq, printed);
          i++;
     }
     i = 0;
     printed = FALSE;

     printf("\nAtbash Sequences: ");
     while (text[i] != '\0') {
          seq = atbash_seq(text, word, i);

          if (seq == NULL) {
               char rev[WORD + 1] = {'\0'};

               reverse_word(word, rev);
               seq = atbash_seq(text, rev, i);
          }
          
          printed = print_seq(seq, printed);
          
          i++;
     }
     i = 0;
     printed = FALSE;

     printf("\nAnagram Sequences: ");
     
     while (text[i] != '\0') {
          seq = anagram_seq(text, word, i);
          printed = print_seq(seq, printed);
          i++;
     }

     return 0;
}

short print_seq(char * seq, short tilde) 
{
     if (seq != NULL) {
          if (tilde == FALSE) {
               tilde = TRUE;
          } else {
               putchar('~');
          }
                                   
          printf("%s", seq);
          free(seq);
     }

     return tilde;
}

void reverse_word(const char word[WORD + 1], char rev[WORD + 1]) 
{
     size_t w_pos, r_pos = 0;
     for (w_pos = WORD; w_pos >= 1; w_pos--) {
          if (word[w_pos - 1] != '\0') {
               rev[r_pos] = word[w_pos - 1];
               r_pos++;
          }
     }
}
