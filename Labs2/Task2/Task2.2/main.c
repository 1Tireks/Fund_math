#include "main.h"

int main() { 

    double result;

    if (fast_power(2, -2, &result) != OK) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    printf("%f", result);
        
    return OK;
}