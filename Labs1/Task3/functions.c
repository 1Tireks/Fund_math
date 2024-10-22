#include "main.h"

ERROR convert_str_to_double(const char *str, double *result) {

    if (str == NULL || result == NULL) {
        return INVALID_INPUT;
    } 
    
    if (*str == '\0') {
        return INVALID_INPUT;
    }
    
    char *endptr;
    *result = strtod(str, &endptr);

    if (*endptr != '\0') {
        return INVALID_INPUT;
    }

    if (*result == HUGE_VAL || *result == -HUGE_VAL) {
        return INVALID_INPUT;
    }
    
    return OK;
}

ERROR convert_str_to_int(const char *str, long int *result, int base) {

    if (str == NULL || result == NULL) {
        return INVALID_INPUT;
    } 
    
    if (*str == '\0') {
        return INVALID_INPUT;
    }
    
    char *endptr;
    *result = strtol(str, &endptr, base);

    if (*endptr != '\0') {
        return INVALID_INPUT;
    }

    if (*result == LONG_MAX || *result == LONG_MIN) {
        return INVALID_INPUT;
    }
    
    return OK;
}

int can_form_triangle(double eps, double a, double b, double c) {
    return (a*a + b*b - c*c <= eps || a*a + c*c - b*b <= eps || b*b + c*c - a*a <= eps);
}

int is_multiple(int num1, int num2) {
    return (num1 % num2 == 0);
}

void solve_quadratic(double a, double b, double c, double eps) {
    double D = b * b - 4 * a * c;
    if (fabs(D) <= eps) {
        printf("Решение: x = %f\n", -b / (2 * a));
    } else if (D > 0) {
        printf("Решения: x1 = %f, x2 = %f\n", 
               (-b + sqrt(D)) / (2 * a), 
               (-b - sqrt(D)) / (2 * a));
    }
}

void generate_permutations(double num1, double num2, double num3, double eps) {
    solve_quadratic(num1, num2, num3, eps);
    solve_quadratic(num1, num3, num2, eps);
    solve_quadratic(num2, num1, num3, eps);
    solve_quadratic(num2, num3, num1, eps);
    solve_quadratic(num3, num1, num2, eps);
    solve_quadratic(num3, num2, num1, eps);
}
