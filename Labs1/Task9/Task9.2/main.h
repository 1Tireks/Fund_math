#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <math.h>
//#include <string.h>
#include <stdlib.h>
//#include <ctype.h>
#include <limits.h>
#include <time.h>


typedef enum {
    OK,
    INVALID_INPUT,
    INVALID_MEMORY
} ERROR;

ERROR convert_str_to_int(const char *str, long int *result, int base);
ERROR filling_array(long int** res_arr, int size_arr, long int a, long int b);
ERROR swap(long int** arr, int size);
ERROR find_closest(long int* arr, int size, int target, long int* result);
ERROR new_array(long int * array_a, int size_a, long int * array_b, int size_b, long int ** array_c);
int compare(const void * x1, const void * x2) ;

#endif