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

ERROR bisection(double* result, double a, double b, double epsilon, double (*function)(double));
double function1(double x);
double function2(double x);

#endif