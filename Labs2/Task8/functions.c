#include "main.h"

int is_valid_number(int base, char** number) {

    if ((*number)[0] == '\0') {
        return 1;
    }

    for (int i = 0; (*number)[i] != '\0'; i++) {
        
        if (isdigit((*number)[i])) {

            if ((*number)[i] - '0' >= base) {

                return 1;

            }

        } else if (isalpha((*number)[i])) {

            (*number)[i] = (char)toupper((*number)[i]);

            if ((*number)[i] - 'A' + 10 >= base) {

                return 1;

            }

        } else {

            return 1;

        }
    }

    return 0;

}

void reverse(char** number, int len) {

    for (int i = 0; i < len / 2; i++) {
        char temp = (*number)[i];
        (*number)[i] = (*number)[len - i - 1];
        (*number)[len - i - 1] = temp;
    }

}

void sum_of_numbers(char** result, char* number, int base, int* len_result, int len_number) {

    int len_sum = (*len_result > len_number) ? (len_number) : (*len_result);
    int remainder = 0, index = 0;

    while (index < len_sum) {

        int digit1 = isdigit((*result)[index]) ? (*result)[index] - '0' : (*result)[index] - 'A' + 10;
        int digit2 = isdigit(number[index]) ? number[index] - '0' : number[index] - 'A' + 10;

        int sum = digit1 + digit2 + remainder;

        (*result)[index] = (sum % base) > 9 ? (sum % base) + 'A' - 10 : (sum % base) + '0';

        remainder = sum / base;

        index++;

    }

    if(*len_result > len_number) {

        while(index < *len_result) {

            int n1 = isdigit((*result)[index]) ? (*result)[index] - '0' : (*result)[index] - 'A' + 10;
            int sum = n1 + remainder;

            (*result)[index] = (sum % base) > 9 ? (sum % base) + 'A' - 10 : (sum % base) + '0';
            remainder = sum / base;

            index++;
        }

    }

    if(len_number > *len_result) {

        while(index < len_number) {
            int n2 = isdigit(number[index]) ? number[index] - '0' : number[index] - 'A' + 10;
            int sum = n2 + remainder;

            (*result)[index] = (sum % base) > 9 ? (sum % base) + 'A' - 10 : (sum % base) + '0';
            remainder = sum / base;

            index++;
        }
    }

    if(remainder != 0) {

        (*result)[index++] = remainder > 9 ? remainder + 'A' - 10 : remainder + '0';

    }

    (*result)[index] = '\0';

    *len_result = index;

}

ERROR sum_in_base(char** result, int base, int count_number, ...) {

    if (count_number <= 0 || base < 2 || base > 36) {

        return INVALID_INPUT;

    }

    va_list args;
    va_start(args, count_number);

    char* number_arg = va_arg(args, char*);
    char* number = strdup(number_arg);

    if (number == NULL) {
        return INVALID_INPUT;
    }
    
    int len_number = strlen(number);

    if (is_valid_number(base, &number)) {

        va_end(args);
        free(number);
        return INVALID_INPUT;

    }

    reverse(&number, len_number);

    int capacity_result = len_number * 2, len_result = len_number;
    *result = (char *)calloc(sizeof(char), capacity_result);

    if(*result == NULL) {

        va_end(args);
        free(number);
        return INVALID_MEMORY;

    }

    strcpy(*result, number);
    free(number);

    for (int i = 0; i < count_number - 1; ++i) {

        number_arg = va_arg(args, char*);
        number = strdup(number_arg);
        len_number = strlen(number);

        if (is_valid_number(base, &number)) {

            va_end(args);
            free(number);
            return INVALID_INPUT;

        }

        reverse(&number, len_number);

        if(len_number + 1 > capacity_result || len_result + 1 > capacity_result) {
            
            int max = len_result > len_number ? len_result : len_number;
            capacity_result = max * 2;
            char * for_realloc = (char *)realloc(*result, capacity_result * sizeof(char));

            if(for_realloc == NULL) {

                va_end(args);
                free(number);
                return INVALID_MEMORY;

            }

            *result = for_realloc;

        }

        sum_of_numbers(result, number, base, &len_result, len_number);
        free(number);

    }

    while(len_result > 1 && (*result)[len_result - 1] == '0') {

        (*result)[--len_result] = '\0';

    }

    reverse(result, len_result);
    va_end(args);

    return OK;

}