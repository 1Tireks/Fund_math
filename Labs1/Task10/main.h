#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

typedef enum {
    OK,
    INVALID_INPUT
} ERROR;

ERROR convert_str_to_ll_int(const char *str, long long int *result, int base);
ERROR convert_to_base(const long long int num, char *result, int base);

#endif