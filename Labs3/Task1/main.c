#include "main.h"

void decrement(int *a);

int main() {

    ERROR error = OK;
    long long int number = 0;
    char result[1];

    printf("Enter a number: ");

    scanf("%lld", &number);

    for (int r = 1; r <= 5; ++r) {

        error = binary_conversion(r, number, result);

        if (error == INVALID_INPUT) {
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        }

        printf("r = %d, result = %s\n", r, result);

    }
    
    return OK;
}