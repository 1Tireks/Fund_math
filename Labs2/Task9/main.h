#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#define EPSILON 1e-10

typedef enum {
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
} ERROR;

ERROR check_finite_representation_in_base(double **res, int base, int *idx, int count, ...);

#endif