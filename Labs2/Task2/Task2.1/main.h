#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>



typedef enum
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
} ERROR;

ERROR geometric_mean(double* result, int count, ...);

#endif