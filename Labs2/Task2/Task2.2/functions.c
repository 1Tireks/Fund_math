#include "main.h"

ERROR fast_power(double base, int exponent, double* result) {

    if (base == 0.0) {
        *result = 0.0;
        return OK;
    }

    if (exponent < 0) {
        return fast_power(1.0 / base,  -1 * exponent, result);
    }

    if (exponent == 0) {
        *result = 1.0;
        return OK;
    }


    double half_power;

    if (fast_power(base, exponent / 2, &half_power) != OK) {
        return INVALID_INPUT;
    }

    double cur_result = half_power * half_power;
    if (!isnormal(cur_result) || isinf(cur_result)) {
        return INVALID_INPUT;
    }

    if (exponent % 2 != 0) {
        cur_result *= base;
        
        if (!isnormal(cur_result) || isinf(cur_result)) {
            return INVALID_INPUT;
        }
    }

    *result = cur_result;
    return OK;
}