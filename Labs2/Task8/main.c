#include "main.h"

int main() {
    char* result;
    ERROR error;

    printf("\ttest 1\n1 + 99 (notation 10)\nexpected result: 100\n");
    error = sum_in_base(&result, 10, 2, "1", "99");
    if(error == OK) {
        printf("\t\t result: %s\n", result);
    } else {
        printf("error\n");
    }
    free(result);

    printf("\n\ttest 2\n123 + 456 (notation 10)\nexpected result: 579\n");
    error = sum_in_base(&result, 10, 2, "123", "00000000456");
    if(error == OK) {
        printf("\t\t result: %s\n", result);
    } else {
        printf("error\n");
    }
    free(result);

    printf("\n\ttest 3\nA + B + C (notation 16)\nexpected result: 21\n");
    error = sum_in_base(&result, 16, 3, "A", "B", "C");
    if(error == OK) {
        printf("\t\t result: %s\n", result);
    } else {
        printf("error\n");
    }
    free(result);

    return OK;

}
