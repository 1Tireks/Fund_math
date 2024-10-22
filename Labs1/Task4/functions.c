#include "main.h"

ERROR without_digits(const char* input_file_name, const char* output_file_name) {

    if (input_file_name == NULL || output_file_name == NULL) {
        return INVALID_INPUT;
    }
    
    FILE* input = fopen(input_file_name, "r");
    if (input == NULL) {
        return FILE_READING_ERROR;
    }

    FILE* output = fopen(output_file_name, "w");
    if (output == NULL) {
        fclose(input);
        return FILE_READING_ERROR;
    }

    char c;
    while ((c = fgetc(input)) != EOF) {
        if (!isdigit(c)) {
            fputc(c, output);
        }
    }

    fclose(input);
    fclose(output);

    return OK;

}

ERROR count_alpha(const char* input_file_name, int* result) {

    if (input_file_name == NULL) {
        return INVALID_INPUT;
    }

    char c;
    int count = 0;
    int i = 0;
    while ((c = input_file_name[i]) != '\0') {
        if (isalpha(c)) {
            count++;
        }
        i++;
    }

    *result = count;

    return OK;

}

ERROR count_not_alpha_digit_space(const char* input_file_name, int* result) {

    if (input_file_name == NULL) {
        return INVALID_INPUT;
    }

    char c;
    int count = 0;
    int i = 0;
    while ((c = input_file_name[i]) != '\0') {
        if (!isalpha(c) && !isdigit(c) && !isspace(c)) {
            count++;
        }
        i++;
    }

    *result = count;

    return OK;

}

ERROR replace_non_digits(const char* input_file_name, const char* output_file_name) {

    if (input_file_name == NULL || output_file_name == NULL) {
        return INVALID_INPUT;
    }
    
    FILE* input = fopen(input_file_name, "r");
    if (input == NULL) {
        return FILE_READING_ERROR;
    }

    FILE* output = fopen(output_file_name, "w");
    if (output == NULL) {
        fclose(input);
        return FILE_READING_ERROR;
    }

    char c;
    while ((c = fgetc(input)) != EOF) {
        if (!isdigit(c)) {
            fprintf(output, "%02X", (unsigned char)c);
        } else {
            fputc(c, output);
        }
    }

    fclose(input);
    fclose(output);

    return OK;

}