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

ERROR convert_str_to_int(const char *str, long int *result, int base);
ERROR isPrime (long int number, int* result);
ERROR multiple_of_number (long int number, int** result, int* size_arr_result);
ERROR split_number_to_digits(long int number, char** result, int* size_arr_result);
void table_of_degrees(long int number);
ERROR sum_of_numbers (long int number, long long int * result);
ERROR factorial_of_a_number (long int number, unsigned long long int* result);
double fast_power(double base, int exponent);

#endif