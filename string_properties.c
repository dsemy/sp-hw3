#include "string_properties.h"

short gematria_val(char c) 
{
     if (isupper(c)) {
          return c - (U_START - 1);
     } else if (islower(c)) {
          return c - (L_START - 1);
     } else {
          return 0;
     }
}

char * gematria_seq(const char text[TEXT + 1], size_t word_val, size_t pos)
{
     if (!isalpha(text[pos])) {
          return NULL;
     }
     
     char * seq = calloc(TEXT + 1, sizeof(char));

     if (seq == NULL) {
          return NULL;
     }

     size_t cur_val = 0, acc_val = 0, i = 0;
     while(text[pos] != '\0') {
          seq[i] = text[pos];
          cur_val = gematria_val(text[pos]);
          acc_val += cur_val;
          
          if (cur_val != 0) {
               if (acc_val == word_val) {
                    seq[i + 1] = '\0';
                    break;
               } else if (acc_val > word_val) {
                    free(seq);
                    return NULL;
               }
          }
          
          pos++;
          i++;
     }

     if (acc_val < word_val) {
          free(seq);
          return NULL;
     }
     
     return seq;
}

char atbash_char(char c) 
{
     if (isupper(c)) {
          c = (U_START + LETTERS) - (c - U_START);
     } else if (islower(c)) {
          c = (L_START + LETTERS) - (c - L_START);
     }

     return c;
}

char * atbash_seq(const char text[TEXT + 1], const char word[WORD + 1], size_t pos)
{
     if (isblank(text[pos])) {
          return NULL;
     }
     
     char * seq = calloc(TEXT + 1, sizeof(char));

     if (seq == NULL) {
          return NULL;
     }

     size_t word_pos = 0, i = 0;
     while (word[word_pos] != '\0') {
          if (text[pos] == '\0') {
               free(seq);
               return NULL;
          }
          
          if (isblank(text[pos])) {
               seq[i] = text[pos];
               pos++;
               i++;
          } else if (atbash_char(word[word_pos]) == text[pos]) {
               seq[i] = text[pos];
               pos++;
               word_pos++;
               i++;
          } else {
               free(seq);
               return NULL;
          }
     }
     
     return seq;
}

short word_contains(char word[WORD + 1], char c) 
{
     for (size_t i = 0; i < WORD; i++) {
          if (word[i] == c) {
               word[i] = '\0';
               return TRUE;
          }
     }

     return FALSE;
}

char * anagram_seq(const char text[TEXT + 1], const char word[WORD + 1], size_t pos)
{
     if (isblank(text[pos])) {
          return NULL;
     }
     
     char * seq = calloc(TEXT + 1, sizeof(char));

     if (seq == NULL) {
          return seq;
     }

     char cur_word[WORD + 1] = {'\0'};
     strcpy(cur_word, word);
     
     size_t count = 0, i = 0;
     while (text[pos] != '\0' && word[count] != '\0') {
          if (isblank(text[pos])) {
               seq[i] = text[pos];
               pos++;
               i++;
          } else if (word_contains(cur_word, text[pos])) {
               seq[i] = text[pos];
               pos++;
               count++;
               i++;
          } else {
               free(seq);
               return NULL;
          }
     }

     if (word[count] != '\0') {
          free(seq);
          return NULL;
     }
     
     return seq;
}
