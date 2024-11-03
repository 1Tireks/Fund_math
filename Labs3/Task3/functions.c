#include "main.h"

ERROR valid_name(char* name, int* resultPtr) {

    if (name == NULL || name[0] == '\0' || resultPtr == NULL) {
        return INVALID_INPUT;
    }

    int i = 0;
    char c;

    *resultPtr = 0;

    while ((c = name[i]) != '\0') {

        if (i == 0 && (c < 'A' || c > 'Z')) {
            *resultPtr = 1;
        } else if (i != 0 && (c < 'a' || c > 'z')) {
            *resultPtr = 1;
        }

        i++;
    }

    return OK;
}

ERROR read_info_from_file(FILE* file, Employer** result, int* size_result, int capasity) {

    if (file == NULL || size_result == NULL) {
        return INVALID_INPUT;
    }

    *size_result = 0;
    *result = (Employer*)malloc(capasity * sizeof(Employer));

    if (*result == NULL) {
        return INVALID_MEMORY;
    }

    int count;
    ERROR error = OK;

    while((count = fscanf(file, "%u %20s %50s %lf", 
                  &(*result)[*size_result].id, 
                  (*result)[*size_result].FirstName, 
                  (*result)[*size_result].SecondName, 
                  &(*result)[*size_result].salary)) == 4) {

        int status;

        error = valid_name((*result)[*size_result].FirstName, &status);

        if (error != OK) {
            return error;
        }

        if (status) {
            return INVALID_INPUT;
        }

        error = valid_name((*result)[*size_result].SecondName, &status);

        if (error != OK) {
            return error;
        }

        if (status) {
            return INVALID_INPUT;
        }

        if ((*result)[*size_result].salary < 0) {
            return INVALID_INPUT;
        } else if (((*result)[*size_result].salary) * KOPEYKA - (floor((*result)[*size_result].salary * KOPEYKA)) > 0) {
            return INVALID_INPUT;
        }

        (*size_result)++;

        if (*size_result == capasity) {

            capasity *= 2;
            Employer* for_realloc = (Employer*)realloc(*result, sizeof(Employer) * capasity);

            if (for_realloc == NULL) {
                return INVALID_MEMORY;
            }

            *result = for_realloc;
        }

    }

    if (*size_result == 0) {
        return INVALID_INPUT;
    }

    if (count != 4 && count != -1) {
        return INVALID_INPUT;
    }

    return OK;

}

 
int compare_Employer(const void* a, const void* b) {

    Employer* empA = (Employer*)a;
    Employer* empB = (Employer*)b;

    if ((*empA).salary == (*empB).salary) {

        int SecondName_compare = strcmp((*empA).SecondName, (*empB).SecondName);
        
        if (SecondName_compare != 0) {

            return SecondName_compare;

        } else if (SecondName_compare == 0) {

            int FirstName_compare = strcmp((*empA).FirstName, (*empB).FirstName);

            if (FirstName_compare != 0) {

                return FirstName_compare;

            } else if (FirstName_compare == 0) {

                return ((*empA).id > (*empB).id) ? 1 : -1;
                
            }

        }
    }

    return ((*empA).salary > (*empB).salary) ? 1 : -1;

}

ERROR save_employees(FILE* file, Employer** result, int size_result) {

    if (file == NULL) {
        return INVALID_INPUT;
    }

    if (result == NULL || *result == NULL) {
        return INVALID_INPUT;
    }

    for (int i = 0; i < size_result; i++) {
        
        fprintf(file, "%d %s %s %.2f\n", (*result)[i].id, (*result)[i].FirstName, (*result)[i].SecondName, (*result)[i].salary);
    }

    return OK;

}

ERROR remove_Emploeer(Employer** resultPtr) {

    if (resultPtr == NULL || *resultPtr == NULL) {
        return INVALID_INPUT;
    }

    free(*resultPtr);
    *resultPtr = NULL;
    resultPtr = NULL;

    return OK;
}