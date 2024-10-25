#include "main.h"

double evaluate_polynomial_of_power(double argument, double *coefs, int max_power) {
    double result = 0;
    double current_power = 1;

    for (int i = 0; i <= max_power; i++) {
        result += current_power * coefs[i];
        current_power *= argument;
    }

    return result;

}

ERROR calculate_polynomial(double a, double **coefficients, int degree, ...) {
    if (degree < 0) {
        return INVALID_INPUT;
    }

    *coefficients = (double *)malloc((degree + 1) * sizeof(double));

    if (*coefficients == NULL) {
        return INVALID_MEMORY;
    }

    int n = degree;
    double *start_coefficients = (double *)malloc(sizeof(double) * (degree + 1));

    if (start_coefficients == NULL) {
        free(*coefficients);
        return INVALID_MEMORY;
    }

    va_list args;
    va_start(args, degree);

    for (int i = 0; i <= degree; i++) {
        double coefficient = va_arg(args, double);
        start_coefficients[i] = coefficient;
    }

    va_end(args);

    double multiply = 1.0;
    int current_power = degree;

    for (int i = 0; i <= n; i++) {

        (*coefficients)[i] = evaluate_polynomial_of_power(a, start_coefficients, current_power);

        if (i > 1) {
            multiply *= i;
            (*coefficients)[i] /= multiply;
        }

        current_power--;

        for (int j = 0; j <= current_power; ++j) {
            double b = start_coefficients[j + 1];
            start_coefficients[j] = b * (j + 1);
        }

    }

    free(start_coefficients);
    return OK;

}