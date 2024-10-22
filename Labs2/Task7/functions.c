#include "main.h"

ERROR bisection(double* result, double a, double b, double epsilon, double (*function)(double)) {

    if (function(a) == 0) {
        *result = a;
        return OK;
    } else if (function(b) == 0) {
        *result = b;
        return OK;
    }

    if (epsilon < pow(10, -9)) {
        return INVALID_INPUT;
    }

    if (a >= b) {
        return INVALID_INPUT;
    } else if ((b - a) >= 100) {
        return INVALID_INPUT;
    }
    
    if (function(a) * function(b) >= 0) {
        return INVALID_INPUT;
    }

    double midpoint;
    while ((b - a) >= epsilon) {
        midpoint = (a + b) / 2.0;

        if (function(midpoint) == 0.0) {
            *result = midpoint;
            return OK;
        } else if (function(midpoint) * function(a) < 0) {
            b = midpoint;
        } else {
            a = midpoint;
        }
    }

    *result =  (a + b) / 2.0;

    return OK;
}

double function1(double x) {
    return pow(x - 1, 2) / (x - 1); 
}

double function2(double x) {
    return x * x * x - 3 * x + 2; 
}