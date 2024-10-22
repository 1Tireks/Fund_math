#include "main.h"

int main() {
    int base;
    
    printf("Введи основание системы счисления\n");
    
    if (scanf("%d", &base) != 1) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    if (base < 2 || base > 36) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    while (getchar() != '\n') {}

    long long int maxNum = 0;
    long long int num;
    char input[100];
    char *pch;

    printf("Введи числа\n");

    while (1) {
        fgets(input, 100, stdin);
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "Stop") == 0) {
            break;
        }

        pch = strtok(input, " \t\n");

        while (pch != NULL) {
            if (convert_str_to_ll_int(pch, &num, base) != OK) {
                printf("INVALID_INPUT\n");
                return INVALID_INPUT;
            }
            if (llabs(maxNum) < llabs(num)) {
                maxNum = num;
            }

            pch = strtok(NULL, " \t\n");
        }
    }

    printf("Максимальное число: %lld\n", maxNum);

    char result[100];
    int bases[] = {9, 18, 27, 36};

    for (int i = 0; i < 4; i++) {
        if (convert_to_base(maxNum, result, bases[i]) != OK) {
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        }
        printf("%d: %s\n", bases[i], result);
    }

    return 0;
}