#include "main.h"

ERROR convert_str_to_int(const char* str, long int* result, int base) {

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

    for(int i = 0; i < size_arr; ++i)
    {
        (*res_arr)[i] = rand() % labs(b + 1 - a) + a;
    }
    return OK;
}

ERROR swap(long int** arr, int size) {
    if (arr == NULL || (*arr) == NULL || size <= 1)
        return INVALID_INPUT;

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

int compare(const void * x1, const void * x2)   
{
  return ( *(long int*)x1 - *(long int*)x2 );              
}

ERROR find_closest(long int* arr, int size, int target, long int* result) {

    if (size <= 0 || result == NULL || arr == NULL) {
        return INVALID_INPUT; 
    }


    int low = 0;
    int high = size - 1;
    int min_ind = -1;
    long int min_diff = LONG_MAX;

    while (low <= high) {
        int middle = (low + high) / 2;

        long int diff = labs(target - arr[middle]);

        if (diff < min_diff) {
            min_diff = diff;
            min_ind = middle;
        }

        if (target < arr[middle]) {
            high = middle - 1;
        } else if (target > arr[middle]) {
            low = middle + 1;
        } else {
            *result = arr[middle];
            return OK;
        }
    }

    if (min_ind >= 0) {
        *result = arr[min_ind];
        return OK;
    } else {
        return INVALID_INPUT;
    }

}

ERROR new_array(long int * array_a, int size_a,
                long int * array_b, int size_b,
                long int ** array_c)
{
    if (array_a == NULL|| array_b == NULL) {
        return INVALID_INPUT;
    }

    (*array_c) = (long int*) malloc(sizeof(long int) * size_a);

    if ((*array_c) == NULL) {
        return INVALID_MEMORY;
    }
    
    long int find_num;
    for(int i = 0; i < size_a; ++i)
    {
        if (find_closest(array_b, size_b, array_a[i], &find_num) != OK) {
            free(*array_c);
            return INVALID_INPUT;
        }
        (*array_c)[i] = array_a[i] + find_num;
    }

    return 0;
}