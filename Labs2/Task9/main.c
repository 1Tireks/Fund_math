#include "main.h"

int main() {
    double *result = NULL;
    int count = 0;

    ERROR error = check_finite_representation_in_base(&result, 25, &count, 5, 0.04, 0.0400, 0.35, 0.08, 0.12);

    if (error == INVALID_MEMORY) {
        printf("INVALID_MEMORY\n");
        return INVALID_MEMORY;
    } else if (error == INVALID_INPUT) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    if (count == 0) {
        printf("Нет чисел имеющие конечное представление\n");
    } else {

        for (int i = 0; i < count; i++) {
            printf("%lf имеет конечное представление\n", result[i]);
        }

        free(result);

    }

    return OK;
}