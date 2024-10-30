#include "main.h"

ERROR create_String(char* str, String** resultPtr) {

    if (str == NULL || str[0] == '\0') {
        return INVALID_INPUT;
    } else if (*resultPtr != NULL) {
        return INVALID_INPUT;
    }

    *resultPtr = (String *)malloc(sizeof(String));

    if (*resultPtr == NULL) {
        return INVALID_MEMORY;
    }

    (*resultPtr)->String_len = strlen(str);

    (*resultPtr)->StringPtr = (char*)malloc(sizeof(char) * ((*resultPtr)->String_len) + 1);

    if ((*resultPtr)->StringPtr == NULL) {
        return INVALID_MEMORY;
    }

    strcpy((*resultPtr)->StringPtr, str);

    return OK;

}

ERROR delete_String_data(String** resultPtr) {

    if (resultPtr == NULL || *resultPtr == NULL || (*resultPtr)->StringPtr == NULL) {  // Проверка double free(), но только если память 
        return INVALID_INPUT;                                                          // была освобождена а указатель нет, будет плохо
    }

    free((*resultPtr)->StringPtr);
    (*resultPtr)->StringPtr = NULL;
    (*resultPtr)->String_len = 0;

    return OK;

}

ERROR String_cmp(String** str1, String** str2, int* result) {

    if (*str1 == NULL || *str2 == NULL) {
        return INVALID_INPUT;
    } else if ((*str1)->StringPtr == NULL || (*str2)->StringPtr == NULL) {
        return INVALID_INPUT;
    }

    if ((*str1)->String_len == (*str2)->String_len) {

        *result = strcmp((*str1)->StringPtr, (*str2)->StringPtr);

        return OK;

    }

    *result = abs((*str1)->String_len - (*str2)->String_len);

    return OK;

}

ERROR String_equivalence(String** str1, String** str2, int* result) {

    if (*str1 == NULL || *str2 == NULL) {
        return INVALID_INPUT;
    } else if ((*str1)->StringPtr == NULL || (*str2)->StringPtr == NULL) {
        return INVALID_INPUT;
    }

    *result = strcmp((*str1)->StringPtr, (*str2)->StringPtr) ? 1 : 0;

    return OK;

}

ERROR copy_in_exist_String(String** str1, String** str2) { // Из str2 в str1

    if (*str1 == NULL || *str2 == NULL) {
        return INVALID_INPUT;
    } else if ((*str1)->StringPtr == NULL || (*str2)->StringPtr == NULL) {
        return INVALID_INPUT;
    } else if ((*str2)->String_len == 0) {
        return INVALID_INPUT;
    }

    strcpy((*str1)->StringPtr, (*str2)->StringPtr);

    (*str1)->String_len = (*str2)->String_len;

    return OK;

}

ERROR copy_in_new_String(String** str1, String** str2) { // Из str2 в str1

    if (*str2 == NULL) {
        return INVALID_INPUT;
    } else if ((*str2)->StringPtr == NULL) {
        return INVALID_INPUT;
    } else if ((*str2)->String_len == 0) {
        return INVALID_INPUT;
    }

    ERROR error = OK;

    error = create_String((*str2)->StringPtr, str1);

    if (error != OK) {
        return error;
    }

    return OK;

}

ERROR concatenation_Strings(String** str1, String** str2) { // Из str2 в str1

    if (*str1 == NULL || *str2 == NULL) {
        return INVALID_INPUT;
    } else if ((*str1)->StringPtr == NULL || (*str2)->StringPtr == NULL) {
        return INVALID_INPUT;
    }

    char* for_realloc = (char*)realloc((*str1)->StringPtr, (*str1)->String_len + (*str2)->String_len + 1);

    if (for_realloc == NULL) {
        return INVALID_INPUT;
    }

    (*str1)->StringPtr = for_realloc;

    for_realloc = NULL;

    strcat((*str1)->StringPtr, (*str2)->StringPtr);

    (*str1)->String_len += (*str2)->String_len;

    return OK;
}

ERROR destroy_String(String** str) {

    if (str == NULL || *str == NULL || (*str)->StringPtr == NULL) {  // Проверка double free(), но только если память  
        return INVALID_INPUT;                                        // была освобождена а указатель нет, будет плохо
    }

    free((*str)->StringPtr);
    (*str)->StringPtr = NULL;
    free(*str);
    *str = NULL;

    return OK;

}