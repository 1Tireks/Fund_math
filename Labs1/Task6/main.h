#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <math.h>
//#include <string.h>
#include <stdlib.h>
//#include <ctype.h>
//#include <limits.h>

typedef enum {
    OK,
    INVALID_INPUT
} ERROR;

ERROR convert_str_to_double(const char *str, double *result);
double integral_a(double x);
double integral_b(double x);
double integral_c(double x);
double integral_d(double x);
double rectangle_integr(double a, double b, int n, double eps, double (*f)(double));
double integral(double eps, double (*f)(double));

#endif