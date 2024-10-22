#include "main.h"

ERROR geometric_mean(double* result, int count, ...) {

    if (count <= 0 || result == NULL) {
        return INVALID_INPUT;
    }

    va_list args;

    va_start(args, count);

    double prod_of_num = 1.0;
    double number;

    for (int i = 0; i < count; ++i) {
        number = va_arg(args, double);

        if (number <= 0.0) {
            va_end(args);
            return INVALID_INPUT;
        }

        prod_of_num *= number;

        if (!isnormal(prod_of_num) || isinf(prod_of_num)) {
            va_end(args);
            return INVALID_INPUT; 
        }

    }

    va_end(args);

    *result = pow(prod_of_num, 1.0 / count);

    return OK;
}