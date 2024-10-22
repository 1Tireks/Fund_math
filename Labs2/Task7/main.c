#include "main.h"

int main() {
    double a1 = 0, b1 = 2.11111, epsilon1 = 0.000001;
    double root1; 

    if (bisection(&root1, a1, b1, epsilon1, function1) != OK) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    printf("Корень функции %f\n", root1);

    double a2 = 0, b2 = 1, epsilon2 = 0.01;
    double root2;

    if (bisection(&root2, a2, b2, epsilon2, function2) != OK) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    printf("Корень функции %f\n", root2);

    return 0;
}