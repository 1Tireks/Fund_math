#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>

typedef enum
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
} ERROR;

ERROR my_strlen(const char* str, int* result);
ERROR my_reverse(const char* str, char** result);
ERROR my_capitalize(const char* str, char** result);
ERROR my_sort(const char* str, char** result);
ERROR convert_str_to_int(const char *str, long long int *result, int base);
ERROR concatenation(char** str, char** result, int count_str, long long int seed);

#endif