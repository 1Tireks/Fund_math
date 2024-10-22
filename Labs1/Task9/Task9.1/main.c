#include "main.h"

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    long int a, b;

    if (convert_str_to_int(argv[1], &a, 10) != OK ||
        convert_str_to_int(argv[2], &b, 10) != OK ||
        a > b)
    {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    long int* res_arr = NULL;

    if (filling_array(&res_arr, ARRAY_SIZE, a, b) != OK) {
        printf("INVALID_MEMORY");
        return INVALID_MEMORY;
    }

    printf("Array: \n");
    for(int i = 0; i < ARRAY_SIZE; ++i) {
        printf("%li ", res_arr[i]);
    }
    printf("\n");

    if (swap(&res_arr, ARRAY_SIZE) != OK){
        printf("INVALID_INPUT");
        return INVALID_INPUT;
    }

    printf("Result array: \n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        printf("%li ", res_arr[i]);
    }
    printf("\n");

    free(res_arr);
    res_arr = NULL;

    return 0;
}