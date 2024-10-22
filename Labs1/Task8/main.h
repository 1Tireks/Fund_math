#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

typedef enum {
    OK,
    INVALID_INPUT,
    FILE_READING_ERROR,
    OVERFLOW,
} ERROR;

ERROR find_min_base(const char* number, int* result);
ERROR convert_to_decimal(const char* number, int base, long long int* result);

#endif