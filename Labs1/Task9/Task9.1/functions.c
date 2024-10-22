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

ERROR filling_array(long int** res_arr, int size_arr, long int a, long int b) {

    (*res_arr) = (long int *) malloc(size_arr * sizeof(long int));

    if ((*res_arr) == NULL) {
        return INVALID_MEMORY;
    }

    srand(time(NULL));

    for(int i = 0; i < size_arr; ++i) {
        (*res_arr)[i] = rand() % labs(b + 1 - a) + a;
    }
    return OK;
}

ERROR swap(long int** arr, int size) {
    if (arr == NULL || (*arr) == NULL || size <= 1) {
        return INVALID_INPUT;
    }

    int minIdx = 0;
    int maxIdx = 0;

    for (int i = 1; i < size; i++) {
        if ((*arr)[i] < (*arr)[minIdx]) {
            minIdx = i;
        } else if ((*arr)[i] > (*arr)[maxIdx]) {
            maxIdx = i;
        }
    }

    long int temp = (*arr)[minIdx];
    (*arr)[minIdx] = (*arr)[maxIdx];
    (*arr)[maxIdx] = temp;
    return OK;
}

