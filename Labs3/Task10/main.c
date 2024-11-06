#include "main.h"

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    char* realpath1 = realpath(argv[1], NULL);
    char* realpath2 = realpath(argv[2], NULL);

    if (realpath1 == NULL || realpath2 == NULL) {
        free(realpath1);
        free(realpath2);
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    if (!strcmp(realpath1, realpath2)) {
        free(realpath1);
        free(realpath2);
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    free(realpath1);
    free(realpath2);

    FILE* input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("FILE_READING_ERROR\n");
        return FILE_READING_ERROR;
    }

    FILE* output = fopen(argv[2], "w");

    if (output == NULL) {
        fclose(input);
        printf("FILE_READING_ERROR\n");
        return FILE_READING_ERROR;
    }


    ERROR error = OK;

    while (!feof(input)) {

        error = print_tree(input, output);

        if (error != OK) {
            printf("%d", error);
            fclose(input);
            fclose(output);
            return error;
        }

        fprintf(output, "\n");
    }

    fclose(input);
    fclose(output);
    return 0;
}