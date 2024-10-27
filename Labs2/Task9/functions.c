#include "main.h"

int gcd(int a, int b) {
    while (a > 0 && b > 0) {
        if (a > b) {
            a = a % b;
        } else {
            b = b % a;
        }
    }

    if (a == 0) {
        return b;
    }

    return a;
}

int is_finite_representation_in_base(double number, int base) {
    int numerator, denominator = 1;

    while (fabs(number - floor(number)) > EPSILON) {
        number *= 10;
        denominator *= 10;
    }

    numerator = (int)number;

    int gcd_param = gcd(numerator, denominator);

    if (gcd_param != 1) {
        denominator /= gcd_param;
    }

    int i = 2;

    if (denominator % i == 0 && base % i != 0) {
        return 0;
    }

    while (denominator % i == 0) {
        denominator /= i;
    }

    for (int i = 3; i*i <= denominator; i+=2) {

        if (denominator % i == 0 && base % i != 0) {
            return 0;
        }

        while (denominator % i == 0) {
            denominator /= i;
        }

    }


    return 1;
}

ERROR check_finite_representation_in_base(double **result, int base, int *index, int count, ...) {

    if (base < 2) {
        return INVALID_INPUT;
    }

    va_list args;
    va_start(args, count);

    *result = (double *)malloc(sizeof(double) * count);

    if (*result == NULL) {
        return INVALID_MEMORY;
    }

    *index = 0;

    for (int i = 0; i < count; ++i) {

        double number = va_arg(args, double);

        if (number > 1 - EPSILON || number < EPSILON) {
            printf("Число %lf инвалид\n", number);
            continue;
        }

        if (is_finite_representation_in_base(number, base) == 1) {
            (*result)[(*index)++] = number;
        }

    }

    if (*index == 0) {
        free(*result);
        *result = NULL;
    }

    va_end(args);
    return OK;

}