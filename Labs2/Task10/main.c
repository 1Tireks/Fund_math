#include "main.h"

int main() {
    double *result = NULL;

    ERROR error = calculate_polynomial(3.0, &result, 4, -2.0, 1.0, -3.0, 0.0, 1.0);

    if (error == INVALID_MEMORY) {
        printf("INVALID_MEMORY\n");
        return INVALID_MEMORY;
    } else if (error == INVALID_INPUT) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    for (int i = 0; i <= 4; ++i) {
        printf("%lf ", result[i]);
    }

    printf("\n");

    free(result);
    return OK;
}