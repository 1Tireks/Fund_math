#include "main.h"

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

ERROR multiple_of_number (long int number, int** result, int* size_arr_result) {

    if (result == NULL || size_arr_result == NULL) {
        return INVALID_INPUT;
    }

    if (number == 0) {
        return INVALID_INPUT;
    }

    int capacity = 4;
    *result = (int*)malloc(capacity * sizeof(int));

    for (int i = 1; i <= 100; ++i) {
        if (i % number == 0) {
            (*result)[(*size_arr_result)++] = i;
            if (capacity == *size_arr_result) {
                capacity *= 2;
                int *for_realloc = realloc(*result, capacity * sizeof(int));
                if (for_realloc == NULL) {
                    return INVALID_MEMORY;
                }
                *result = for_realloc;
            }
        }
    }

    return OK;

}

ERROR isPrime (long int number, int* result) {

    if (result == NULL) {
        return INVALID_INPUT;
    }

    if (number <= 0) {
        return INVALID_INPUT;
    }

    if (number == 1 || number == 2) {
        *result = 0;
        return OK;
    } else if (number % 2 == 0) {
        *result = 1;
        return OK;
    }

    for (int i = 3; i*i <= number; ++i) {
        if (number % i == 0) {
            *result = 1;
            return OK;
        }
    }

    *result = 0;
    return OK;

}

ERROR split_number_to_digits(long int number, char** result, int* size_arr_result) {

    if (result == NULL || size_arr_result == NULL) {
        return INVALID_INPUT;
    }

    (*size_arr_result)++;

    *result = (char*)calloc((*size_arr_result) + 1, sizeof(char));


    if (*result == NULL) {
        return INVALID_MEMORY;
    }

    if (number < 0) {
        (*result)[0] = '-';
        number = labs(number);
    }

    for (int i = *size_arr_result - 1; i >= 0; --i) {
        (*result)[i + 1] = '0' + (number % 16);
        number /= 16;
    }

    (*size_arr_result)++;
    return OK;

}

double fast_power(double base, int exponent) {

    if (exponent == 0) {
        return 1.0;
    }

    double half_power;
    half_power = fast_power(base, exponent / 2);

    double cur_result = half_power * half_power;


    if (exponent % 2 != 0) {
        cur_result *= base;
    }

    return cur_result;
}

void table_of_degrees(long int number) {

    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= number; j++) {
            printf("%11d", (int)fast_power(i, j));
        }
        printf("\n");
    }

}


ERROR sum_of_numbers (long int number, long long int * result) {

    if (result == NULL) {
        return INVALID_INPUT;
    }

    if (number <= 0) {
        *result = 1;
        return OK;
    }

    *result = ((1 + number) * number) / 2;

    return OK;

}

ERROR factorial_of_a_number (long int number, unsigned long long int* result) {

    if (result == NULL) {
        return INVALID_INPUT;
    }

    *result = 1;

    for(long int i = 2; i <= number; ++i) {
        if(*result > ULLONG_MAX / i) {
            return INVALID_MEMORY;
        }
        *result *= i;
    }

    

    return OK;

}

