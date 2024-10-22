#include "main.h"

ERROR convert_str_to_ll_int(const char *str, long long int *result, int base) {
    if (str == NULL || result == NULL) {
        return INVALID_INPUT;
    }

    if (*str == '\0') {
        return INVALID_INPUT;
    }

    *result = 0;
    int i = 0;
    int sign = 1;

    if (str[i] == '-') {
        sign = -1;
        ++i;
    }

    while (str[i] != '\0') {
        int digit;

        if (isdigit(str[i]) && str[i] - '0' < base) {
            digit = str[i] - '0';
        } else if (isalpha(str[i]) && str[i] - 'A' + 10 < base) {
            digit = str[i] - 'A' + 10;
        } else {
            return INVALID_INPUT;
        }

        if (*result > (LLONG_MAX - digit) / base) { 
            return INVALID_INPUT;
        }

        *result = (*result) * base + digit;
        i++;
    }

    if (i == 0) {
        return INVALID_INPUT;
    }

    *result *= sign;
    return OK;
}

ERROR convert_to_base(const long long int num, char* result, int base) {
    if (result == NULL) {
        return INVALID_INPUT;
    }

    long long int num_abs = llabs(num);
    int i_num = 0;

    do {
        int digit =  num_abs % base;

        if (digit < 10) {
            result[i_num++] = digit +'0';
        } else {
            result[i_num++] = digit - 10 +'A';
        }

        num_abs /= base;

    } while (num_abs > 0);

    if (num < 0) {
        result[i_num] = '-';
        i_num++;
    }

    result[i_num] = '\0';

    for (int i = 0; i < i_num / 2; i++) {
        char temp = result[i];
        result[i] = result[i_num - i - 1];
        result[i_num - i - 1] = temp;
    }

    return OK;
}