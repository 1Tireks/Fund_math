#include "main.h"

ERROR print_tree(FILE* input, FILE *output) {

    if (input == NULL || output == NULL) {
        return INVALID_INPUT;
    }

    char c = fgetc(input);

    if (c == '\n' && c == EOF) {
        fprintf(output, "\n");
    }

    int count = 0;
    while (c != '\n' && c != EOF) {

        if (c == '(') {
            count++;
        } else if (c == ')') {
            count--;
        } else if (c == ' ' || c == ',') {
            c = fgetc(input);
            continue;
        } else {
            for (int i = 0; i < count * 3; ++i) {
                fprintf(output, " ");
            }
            fprintf(output, "%c\n", c); // printf("%c\n", c) - вывод в консоль Bruh -_-
        }
        c = fgetc(input);
    }

    return OK;
}