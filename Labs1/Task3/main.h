#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>

typedef enum {
    OK,
    INVALID_INPUT
} ERROR;

ERROR convert_str_to_double(const char *str, double *result);
ERROR convert_str_to_int(const char *str, long int *result, int base);
int can_form_triangle(double eps, double a, double b, double c);
int is_multiple(int num1, int num2);
void solve_quadratic(double a, double b, double c, double epsilon);
void generate_permutations(double num1, double num2, double num3, double eps);

#endif