#include "main.h"

ERROR find_min_base(const char* number, int* result) {

    int min_base = 1;
    int i = 0;
    char c;
    int digit;

    if (number == NULL || result == NULL) {
        return INVALID_INPUT;
    }

    if (*number == '\0') {
        return INVALID_INPUT;
    }

    if (number[i] == '-') i++;

    while(number[i] != '\0') {
        c = tolower(number[i]);

        if (isdigit(c)) {
            digit = c - '0';
        } else if (isalpha(c)) {
            digit = c - 'a' + 10;
        } else {
            return INVALID_INPUT;
        }

        if (digit > min_base) {
            min_base = digit;
        }

        i++;
    }

    if (min_base > 36) {
        return INVALID_INPUT;
    }

    *result = min_base + 1;

    return OK;
}

ERROR convert_to_decimal(const char* number, int base, long long int* result) {


    int i = 0;
    char c;
    int digit;
    int sign = 1;

    if (number[i] == '-') {
        sign = -1;
        ++i;
    }
    
    if (number == NULL || result == NULL) {
        return INVALID_INPUT;
    }

    if (*number == '\0') {
        return INVALID_INPUT;
    }

    while (number[i] != '\0') {
        c = tolower(number[i]);

        if (isdigit(c)) {
            digit = c - '0';
        } else if (isalpha(c)) {
            digit = c - 'a' + 10;
        } else {
            return INVALID_INPUT;
        }

        if (*result > (LLONG_MAX - digit) / base) { 
            return OVERFLOW;
        }

        *result = (*result) * base + digit;



        i++;
    }

    *result *= sign;

    return OK;
}