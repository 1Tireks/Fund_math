#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <math.h>

typedef enum {
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    FILE_READING_ERROR,
} ERROR;

#define HASH_MODULE (long long int)pow(10, 8)
#define BASE 128

ERROR find_word(int** result, int* current_elem, const char* str, const int count, ...);

#endif