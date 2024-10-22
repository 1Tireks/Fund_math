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
    INVALID_MEMORY,
    FILE_READING_ERROR,
} ERROR;

ERROR without_digits(const char* input_file_name, const char* output_file_name);
ERROR count_alpha(const char* input_file_name, int* result);
ERROR count_not_alpha_digit_space(const char* input_file_name, int* result);
ERROR replace_non_digits(const char* input_file_name, const char* output_file_name);

#endif