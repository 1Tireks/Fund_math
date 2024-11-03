#include "main.h"

int main(int argc, char* argv[]) {

    if (argc != 4) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    if ((argv[2][0] != '-' && argv[2][0] != '/') && argv[2][2] != '\0') {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    char* realpath1 = realpath(argv[1], NULL);
    char* realpath2 = realpath(argv[3], NULL);

    if (realpath1 == NULL || realpath2 == NULL) {
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

    ERROR error = OK;
    Employer* result = NULL;
    int size_result;

    FILE* input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("FILE_READING_ERROR\n");
        return FILE_READING_ERROR;
    }

    error = read_info_from_file(input, &result, &size_result, INITIAL_CAPASITY);

    if (error == INVALID_INPUT) {
        fclose(input);
        remove_Emploeer(&result);
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    } else if (error == INVALID_MEMORY) {
        fclose(input);
        remove_Emploeer(&result);
        printf("INVALID_MEMORY\n");
        return INVALID_MEMORY;
    }

    fclose(input);

    if (argv[2][1] == 'd') {

        qsort(result, size_result, sizeof(Employer), compare_Employer);

        Employer* temp = (Employer*)malloc(sizeof(Employer));

        if (temp == NULL) {
            remove_Emploeer(&result);
            return INVALID_MEMORY;
        }

        for (int i = 0; i < size_result / 2; i++) {
            *temp = result[i];
            result[i] = result[size_result - i - 1];
            result[size_result - i - 1] = *temp;
        }

        free(temp);

    } else if (argv[2][1] == 'a') {

        qsort(result, size_result, sizeof(Employer), compare_Employer);

    }


    FILE* output = fopen(argv[3], "w");

    if (output == NULL) {
        remove_Emploeer(&result);
        return FILE_READING_ERROR;
    }

    error = save_employees(output, &result, size_result);

    if (error == INVALID_INPUT) {
        remove_Emploeer(&result);
        fclose(output);
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    fclose(output);
    remove_Emploeer(&result);

    return OK;

}