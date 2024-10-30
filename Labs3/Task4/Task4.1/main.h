#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

typedef enum {
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
} ERROR;

typedef struct {
    char* StringPtr;
    int String_len;
} String;

ERROR create_String(char* str, String** resultPtr);
ERROR delete_String_data(String** resultPtr);
ERROR String_cmp(String** str1, String** str2, int* result);
ERROR String_equivalence(String** str1, String** str2, int* result);
ERROR copy_in_exist_String(String** str1, String** str2);
ERROR copy_in_new_String(String** str1, String** str2);
ERROR concatenation_Strings(String** str1, String** str2);
ERROR destroy_String(String** str);

#endif