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

ERROR fast_power(double base, int exponent, double* result);

#endif