#include "main.h"

int main() { 
    long int a = -1000, b = 1000, c = 10, d = 10000;

    int ARRAY_SIZE = (rand() % labs(d + 1 - c) + c)/100;

    printf("");

    srand(time(NULL));
    
    long int* result_a = NULL, *result_b = NULL;
    if(filling_array(&result_a, ARRAY_SIZE, a, b) != OK)
    {
        printf("INVALID_MEMORY");
        return INVALID_MEMORY;
    }

    if(filling_array(&result_b, ARRAY_SIZE, a, b) != OK)
    {
        free(result_a);
        printf("INVALID_MEMORY");
        return INVALID_MEMORY;
    }

    printf("Array A: \n");
    for(int i = 0; i < ARRAY_SIZE; ++i) {
        printf("%li ", result_a[i]);
    }
    printf("\n");

    printf("Array B: \n");
    for(int i = 0; i < ARRAY_SIZE; ++i) {
        printf("%li ", result_b[i]);
    }
    printf("\n");

    long int* result_c = NULL;

    qsort(result_b, ARRAY_SIZE, sizeof(long int), compare);

    if(new_array(result_a, ARRAY_SIZE, result_b, ARRAY_SIZE, &result_c) != OK) {
        free(result_a);
        free(result_b)
        printf("INVALID_INPUT");
        return INVALID_INPUT;
    }

    printf("Array C: \n");
    for(int i = 0; i < ARRAY_SIZE; ++i) {
        printf("%li ", result_c[i]);
    }
    printf("\n");

    free(result_a);
    result_a = NULL;  

    free(result_b);
    result_b = NULL;

    free(result_c);
    result_c = NULL;

    return OK;
}