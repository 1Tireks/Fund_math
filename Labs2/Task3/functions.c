#include "main.h"

long long int hash(const char* str, int len, int begin) {

    long long int hash = 0;
    for (int i = 0; i < len; i++) {
        hash = (hash * BASE + str[(begin + i) % len]) % HASH_MODULE;
    }

    return hash;

}

ERROR count_str_in_file(int *result, const char *filename, long long int str_hash, int str_len) {

    if (result == NULL || filename == NULL) {
        return INVALID_INPUT;
    }

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        return FILE_READING_ERROR;
    }

    char buffer[str_len];
    int buffer_index = 0, c;
    long long int current_hash;

    while ((c = fgetc(file)) != EOF) {
        buffer[buffer_index] = c;
        buffer_index = (buffer_index + 1) % str_len;
        current_hash = hash(buffer, str_len, buffer_index);

        if (current_hash == str_hash) {
            *result += 1;
        }

    }

    fclose(file);

    return OK;

}

ERROR search_str_in_file(int** result, int* current_elem, const char *filename, long long int str_hash, int str_len) {

    if (filename == NULL || result == NULL || current_elem == NULL) {
        return INVALID_INPUT;
    } 

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        return FILE_READING_ERROR;
    }

    char buffer[str_len];
    int buffer_index = 0, c;
    long long int current_hash;
    int line = 1, symbol = 0, is_filling_biffer = 0;

    while ((c = fgetc(file)) != EOF) {

        if (is_filling_biffer + 1 < str_len) {
            is_filling_biffer++;
        } else if (buffer[buffer_index] == '\n') {
            line++;
            symbol = 0;
        } else {
            symbol++;
        }

        buffer[buffer_index] = c;
        buffer_index = (buffer_index + 1) % str_len;
        current_hash = hash(buffer, str_len, buffer_index);

        if (current_hash == str_hash) {
            (*result)[*current_elem] = line;
            (*current_elem)++;
            (*result)[*current_elem] = symbol;
            (*current_elem)++;
        }
        
    }

    fclose(file);

    return OK;

}

ERROR find_word(int** result, int* current_elem, const char* str, const int count, ...) {

    if (count <= 0 || result == NULL || str == NULL) {
        return INVALID_INPUT;
    }

    long long int str_hash = hash(str, strlen(str), 0);

    va_list args;
    va_start(args, count);

    int count_word = 0;

    ERROR error; 

    for (int i = 0; i < count; i++) {
        const char *filename = va_arg(args, const char *);
        error = count_str_in_file(&count_word, filename, str_hash, strlen(str));

        if (error != OK) {
            return error;
        }
    }

    (*result) = (int*)malloc(count_word * 2 * sizeof(int));
    if (*result == NULL) {
        return INVALID_MEMORY;
    }

    *current_elem = 0;

    va_end(args);
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        const char *filename = va_arg(args, const char *);
        error = search_str_in_file(result, current_elem, filename, str_hash, strlen(str));  
        if (error != OK){
            free(*result);
            return error;
        }
    }

    va_end(args);

    return OK;
}
