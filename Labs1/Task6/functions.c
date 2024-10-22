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

double integral_a(double x) {
    return log(1 + x) / x;
}

double integral_b(double x) {
    return exp(-x*x/2);
}

double integral_c(double x) {
    return log(1/(1 - x));
}

double integral_d(double x) {
    return pow(x, x);
}

double rectangle_integr(double a, double b, int n, double eps, double (*f)(double)) {
    double interval = (b - a)/n;
    double summ = 0.0;
    double x;

    for (double i = eps; i < n - eps; i++) {
        x = a + interval * i;
        summ += f(x);
    }
    return summ * interval;
}

double integral(double eps, double (*f)(double)) {
    double a = 0.0, b = 1.0;
    double prev_res = 0.0, res = 0.0;
    int n = 1;


    do {
        prev_res = res;
        res = rectangle_integr(a, b, n, eps, f);
        n *= 2;
    } while (fabs(res - prev_res) > eps);

    return res;
}

// a: 0.823066
// b: 0.856391
// c: 0.999339
// d: 0.783573