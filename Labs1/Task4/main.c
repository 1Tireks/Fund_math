#include "main.h"

int main(int argc, char** argv) {

    if (argc < 3 || argc > 4) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    } else if (!(argv[1][0] == '-' || argv[1][0] == '/')) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }
    



    char* file_name;
    ERROR error = OK;

    if (argv[1][1] == 'n') {

        if (!(argv[1][3] == '\0')) {
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        }

        if (argc == 4) {
            char* path1 = strrchr(argv[2], '/');
            char* path2 = strrchr(argv[3], '/');
            if (!strcmp(path1 + 1, path2 + 1)) {
                printf("INVALID_INPUT\n");
                return INVALID_INPUT;
            }
            file_name = argv[3];
        } else {
            printf("INVALID_INPUT");
            return INVALID_INPUT;
        }
    } else {

        if (!(argv[1][2] == '\0')) {
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        }

        if (argc == 3) {
            file_name = (char*)malloc((strlen(argv[2]) + 5) * sizeof(char));
            if (file_name == NULL){
                printf("INVALID_MEMORY\n");
                return INVALID_MEMORY;
            }
            snprintf(file_name, strlen(argv[2]) + 5, "out_%s", argv[2]);
        } else {
            printf("INVALID_INPUT");
            return INVALID_INPUT;
        }
    }

    switch ((argv[1][1] == 'n') ? argv[1][2] : argv[1][1])
    {
        case ('d'): {
            error = without_digits(argv[2], file_name);
            if (error == INVALID_INPUT) {
                printf("INVALID_INPUT\n");
                return INVALID_INPUT;
            } else if (error == FILE_READING_ERROR) {
                printf("FILE_READING_ERROR\n");
                return FILE_READING_ERROR;
            }

            break;
        }

        case ('i'): {

            FILE* input = fopen(argv[2], "r");
            if (input == NULL) {
                printf("FILE_READING_ERROR\n");
                return FILE_READING_ERROR;
            }

            FILE* output = fopen(file_name, "w");
            if (output == NULL) {
                fclose(input);
                printf("FILE_READING_ERROR\n");
                return FILE_READING_ERROR;
            }


            int count;

            char buffer[1024];

            while (fgets(buffer, sizeof(buffer), input) != NULL) {
                char* token = strtok(buffer, "\n");
                while (token != NULL) {

                    error = count_alpha(token, &count);
                    if (error == INVALID_INPUT) {
                        printf("INVALID_INPUT\n");
                        return INVALID_INPUT;
                    }

                    if (*token == '\0') {
                        token = strtok(NULL, "\n");
                        continue;
                    }

                    fprintf(output, "%s %d\n", token, count);

                    token = strtok(NULL, "\n");
                }
                count = 0;

            }

            fclose(input);
            fclose(output);

            break;
        }

        case ('s'): {

            FILE* input = fopen(argv[2], "r");
            if (input == NULL) {
                printf("FILE_READING_ERROR\n");
                return FILE_READING_ERROR;
            }

            FILE* output = fopen(file_name, "w");
            if (output == NULL) {
                fclose(input);
                printf("FILE_READING_ERROR\n");
                return FILE_READING_ERROR;
            }


            int count;

            char buffer[1024];

            while (fgets(buffer, sizeof(buffer), input) != NULL) {
                char* token = strtok(buffer, "\n");
                while (token != NULL) {

                    error = count_not_alpha_digit_space(token, &count);
                    if (error == INVALID_INPUT) {
                        printf("INVALID_INPUT\n");
                        return INVALID_INPUT;
                    }

                    if (*token == '\0') {
                        token = strtok(NULL, "\n");
                        continue;
                    }

                    fprintf(output, "%s %d\n", token, count);

                    token = strtok(NULL, "\n");
                }
                count = 0;

            }

            fclose(input);
            fclose(output);



            break;
        }

        case ('a'): {

            error = replace_non_digits(argv[2], file_name);
            if (error == INVALID_INPUT) {
                printf("INVALID_INPUT\n");
                return INVALID_INPUT;
            } else if (error == FILE_READING_ERROR) {
                printf("FILE_READING_ERROR\n");
                return FILE_READING_ERROR;
            }


            break;
        }
        
        default:

        printf("Ошибка: такого флага нет в доступных флагах: %s\n", argv[1]);

        break;
    }
    






}