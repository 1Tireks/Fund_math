#include "main.h"

int main(int argc, char** argv) {

    ERROR error = OK;

    if (argc < 3) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }
    
    if (!(((argv[1][0] == '-') || (argv[1][0] == '/')) && (argv[1][2] == '\0'))) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    switch (argv[1][1]) 
    {

    case 'l': {

        if (argc != 3) {
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        }

        int len = 0;

        if (my_strlen(argv[2], &len) != OK) {
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        }

        printf("String length: %d\n", len);
        
        break;

    }
    
    case 'r': {

        if (argc != 3) {
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        }

        char* reversed_str = NULL;

        error = my_reverse(argv[2], &reversed_str);

        if (error == INVALID_INPUT) {
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        } else if (error == INVALID_MEMORY) {
            printf("INVALID_MEMORY\n");
            return INVALID_MEMORY;
        }

        printf("String reversed: %s\n", reversed_str);

        free(reversed_str);

        break;

    }

    case 'u': {

        if (argc != 3) {
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        }

        char* capitalized_str = NULL;

        error = my_capitalize(argv[2], &capitalized_str);

        if (error == INVALID_INPUT) {
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        } else if (error == INVALID_MEMORY) {
            printf("INVALID_MEMORY\n");
            return INVALID_MEMORY;
        }

        printf("String capitalized: %s\n", capitalized_str);

        free(capitalized_str);

        break;

    }

    case 'n': {

        if (argc != 3) {
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        }

        char* sorted_str = NULL;

        error = my_sort(argv[2], &sorted_str);

        if (error == INVALID_INPUT) {
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        } else if (error == INVALID_MEMORY) {
            printf("INVALID_MEMORY\n");
            return INVALID_MEMORY;
        }

        printf("String sorted: %s\n", sorted_str);

        free(sorted_str);
        
        break;

    }

    case 'c': {

        int count_str = argc - 3;

        long long int seed;

        if (convert_str_to_int(argv[2], &seed, 10) != OK) {
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        }

        char* concatenationed_str = NULL;

        error = concatenation((argv + 3), &concatenationed_str, count_str, seed);

        if (error == INVALID_INPUT) {
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        } else if (error == INVALID_MEMORY) {
            printf("INVALID_MEMORY\n");
            return INVALID_MEMORY;
        }

        printf("Strings concatenationed: %s\n", concatenationed_str);
        
        break;

    }

    default:

        printf("Ошибка: такого флага нет в доступных флагах: %s\n", argv[1]);

        break;

    }

    return OK;

}