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

ERROR first_summ(double x, double epsilon, double *summ) {
    int n = 0;
    double term = 1.0;
    while (fabs(term) > epsilon) {
        *summ += term;
        n++;
        term *= x / n;
        if (isinf(*summ) || isnan(term)) {
            return DATA_TYPE_OVERFLOW;
        }
    }
    return OK;
}

ERROR second_summ(double x, double epsilon, double *summ) {
    int n = 0;
    double term = 1.0;
    while (fabs(term) > epsilon) {
        *summ += (n % 2 == 0) ? term : -1.0 * term;
        n++;
        term *= (x * x) / ((n * 2 - 1) * (n * 2));
        if (isinf(*summ) || isnan(term)) {
            return DATA_TYPE_OVERFLOW;
        }
    }
    return OK;
}

ERROR third_summ(double x, double epsilon, double *summ) {
    if (x >= 1 || x <= -1) {
        return DATA_TYPE_OVERFLOW;
    }
    int n = 0;
    double term = 1.0;
    while (fabs(term) > epsilon) {
        *summ += term;
        n++;
        term *= (9 * n * n * x * x) /((3*n - 1)*(3*n-2));
        if (isinf(*summ) || isnan(term)) {
            return DATA_TYPE_OVERFLOW;
        }
    }
    return OK;
}

ERROR fourth_summ(double x, double epsilon, double *summ) {
    if (x >= 1 || x <= -1) {
        return DATA_TYPE_OVERFLOW;
    }
    int n = 0;
    double term = 1.0;
    while (fabs(term) > epsilon) {
        n++;
        term *= (x * x * (2.0 * n - 1)) / (n * 2);
        *summ += (n % 2 == 0) ? term : -1.0 * term;
        if (isinf(*summ) || isnan(term)) {
            return DATA_TYPE_OVERFLOW;
        }
    }
    return OK;
}
