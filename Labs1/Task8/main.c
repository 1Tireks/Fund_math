#include "main.h"

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }
    char* path1 = strrchr(argv[2], '/');
    char* path2 = strrchr(argv[3], '/');

    if (!strcmp(path1 + 1, path2 + 1)) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w");

    if (input_file == NULL) {
        printf("FILE_READING_ERROR\n");
        return FILE_READING_ERROR;
    }

    if (output_file == NULL) {
        fclose(input_file);
        printf("FILE_READING_ERROR\n");
        return FILE_READING_ERROR;
    }

    char buffer[1024];
    long long int decimal_value = 0;
    int min_base;

    while (fgets(buffer, sizeof(buffer), input_file) != NULL) {
        char* token = strtok(buffer, " \t\n");
        while (token != NULL) {

            while (*token == '0') {
                if (*(token + 1) == '0') {
                    token++;
                } else {
                    token++;
                    break;
                }
            }

            if (*token == '\0') {
                token = strtok(NULL, " \t\n");
                continue;
            }

            if (find_min_base(token, &min_base) != OK) {
                printf("INVALID_INPUT\n");
                return INVALID_INPUT;
            }

            if (convert_to_decimal(token, min_base, &decimal_value) != OK) {
                printf("INVALID_INPUT\n");
                return INVALID_INPUT;
            }

            fprintf(output_file, "%s %d %lld\n", token , min_base, decimal_value);

            token = strtok(NULL, " \t\n");
        }
        min_base = 0;
        decimal_value = 0;
    }




    fclose(input_file);
    fclose(output_file);
    return OK;

}

