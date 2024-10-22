#include "main.h"

ERROR my_strlen(const char* str, int* result) {

    if (str == NULL || result == NULL) {
        return INVALID_INPUT;
    }

    int count = 0;

    while (str[count] != '\0') {
        count++;

        if (count > pow(10, 5)) {
            return INVALID_INPUT;
        }

    }

    *result = count;

    return OK;

}

ERROR my_reverse(const char* str, char** result) {

    if (str == NULL) {
        return INVALID_INPUT;
    }

    int len = 0;

    if (my_strlen(str, &len) != OK) {
        return INVALID_INPUT;
    }

    *result = (char*)malloc(sizeof(char) * len);

    if (*result == NULL) {
        return INVALID_MEMORY;
    }

    for (int i = 0; i < len; i++) {
        (*result)[i] = str[len - i - 1];
    }
    (*result)[len] = '\0';

    return OK;

}

ERROR my_capitalize(const char* str, char** result) {

    if (str == NULL) {
        return INVALID_INPUT;
    }

    int len = 0;

    if (my_strlen(str, &len) != OK) {
        return INVALID_INPUT;
    }

    *result = (char*)malloc(sizeof(char) * len);

    if (*result == NULL) {
        return INVALID_MEMORY;
    }

    for (int i = 0; i < len; i++) {
        if (i % 2 == 0)
            (*result)[i] = str[i];
        else {
            if ('a' <= str[i] && str[i] <= 'z') {
                (*result)[i] = str[i] - 'a' + 'A';
            } else {
                (*result)[i] = str[i];
            }
        }
    }
    (*result)[len] = '\0';

    return OK;
}

ERROR my_sort(const char* str, char** result) {

    if (str == NULL) {
        return INVALID_INPUT;
    }

    int len = 0;

    if (my_strlen(str, &len) != OK) {
        return INVALID_INPUT;
    }

    *result = (char*)malloc(sizeof(char) * len);

    if (*result == NULL) {
        return INVALID_MEMORY;
    }

    int current = 0;

    for (int i = 0; i < len; i++) {
        if ('0' <= str[i] && str[i] <= '9') {
            (*result)[current] = str[i];
            current++;
        }
    }

    for (int i = 0; i < len; i++) {
        if (('a' <= str[i] && str[i] <= 'z') || ('A' <= str[i] && str[i] <= 'Z')) {
            (*result)[current] = str[i];
            current++;
        }
    }

    for (int i = 0; i < len; i++) {
        if (!('0' <= str[i] && str[i] <= '9')&& !(('a' <= str[i] && str[i] <= 'z') || ('A' <= str[i] && str[i] <= 'Z'))) {
            (*result)[current] = str[i];
            current++;
        }
    }

    (*result)[len] = '\0';

    return OK;
}

ERROR convert_str_to_int(const char *str, long long int *result, int base) {

    if (str == NULL || result == NULL) {
        return INVALID_INPUT;
    } 
    
    if (*str == '\0') {
        return INVALID_INPUT;
    }
    
    char *endptr;
    *result = strtoll(str, &endptr, base);

    if (*endptr != '\0') {
        return INVALID_INPUT;
    }

    if (*result == LLONG_MAX || *result == LLONG_MIN) {
        return INVALID_INPUT;
    }
    
    return OK;
}

ERROR concatenation(char** str, char** result, int count_str, long long int seed) {

    if (str == NULL) {
        return INVALID_INPUT;
    }

    int len = 0, size_str = 0;

    for (int i = 0; i < count_str; i++) {
        if (my_strlen(str[i], &len) != OK)
            return INVALID_INPUT;
        size_str += len;

        if (size_str >= pow(10, 5)) {
            return INVALID_INPUT;
        }
    }

    *result = (char*)malloc(sizeof(char) * size_str);

    if (*result == NULL) {
        return INVALID_MEMORY;
    }

    int* str_used = (int*)calloc(count_str, sizeof(int));

    if (*result == NULL) {
        free(*result);
        return INVALID_MEMORY;
    }

    srand(seed);

    int num_str, main_current = 0, str_surrent;

    int index;

    for (int i = 0; i < count_str; i++) {

        num_str = rand() % count_str;

        int found_unused = 0;
        index = 0;

        while (found_unused <= num_str) {
            if (str_used[index] == 0) {
                if (found_unused == num_str) {
                    break;
                }
                found_unused++;
            }

            index++;
            if (index >= count_str) {
                index = 0;
            }
        }

        str_used[index] = 1;

        str_surrent = 0;

        while (str[index][str_surrent] != '\0') {
            (*result)[main_current] = str[index][str_surrent];
            str_surrent++;
            main_current++;
        }

    }
    (*result)[size_str] = '\0';

    free(str_used);

    return OK;
}