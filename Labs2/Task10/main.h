#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

typedef enum {
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
} ERROR;

ERROR calculate_polynomial(double a, double epsilon, double **coefficients, int degree, ...);

#endif