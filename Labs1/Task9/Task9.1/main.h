#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
//#include <math.h>
//#include <string.h>
#include <stdlib.h>
//#include <ctype.h>
#include <limits.h>
#include <time.h>

#define ARRAY_SIZE 10

typedef enum {
    OK,
    INVALID_INPUT,
    INVALID_MEMORY
} ERROR;

ERROR convert_str_to_int(const char *str, long int *result, int base);
ERROR filling_array(long int** res_arr, int size_arr, long int a, long int b);
ERROR swap(long int** arr, int size);

#endif