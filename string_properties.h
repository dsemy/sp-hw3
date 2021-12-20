#pragma once

#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define TEXT 1024
#define WORD 30
#define LETTERS 25
#define L_START 97
#define U_START 65

short gematria_val(char);
char atbash_char(char);
short word_contains(char[WORD + 1], char);

char * gematria_seq(const char[TEXT + 1], size_t, size_t);
char * atbash_seq(const char[TEXT + 1], const char[WORD + 1], size_t);
char * anagram_seq(const char[TEXT + 1], const char[WORD + 1], size_t);
