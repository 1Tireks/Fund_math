#include "main.h"

int main() { 

    double result;

    if (geometric_mean(&result, 5, 0.0, 1.8, 65.9, 2.9, 1.44) != OK) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    printf("%f", result);
        
    return OK;
}