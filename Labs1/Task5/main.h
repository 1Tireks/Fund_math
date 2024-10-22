#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <float.h>

typedef enum
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    DATA_TYPE_OVERFLOW,
} ERROR;

ERROR convert_str_to_double(const char *str, double *result);
ERROR first_summ(double x, double epsilon, double *summ);
ERROR second_summ(double x, double epsilon, double *summ);
ERROR third_summ(double x, double epsilon, double *summ);
ERROR fourth_summ(double x, double epsilon, double *summ);

#endif