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

ERROR read_Students_from_file(FILE* input, int* count_Students, Student** resultPtr, int capasity) {

    if (input == NULL || count_Students == NULL || resultPtr == NULL) {
        return INVALID_INPUT;
    }

    *count_Students = 0;
    *resultPtr = (Student*)malloc(capasity * sizeof(Student));

    if (*resultPtr == NULL) {
        return INVALID_MEMORY;
    }

    int count;
    ERROR error = OK;

    

    while ((count = fscanf(input, "%d %20s %50s %15s %c %c %c %c %c", 
                  &(*resultPtr)[*count_Students].id, 
                  (*resultPtr)[*count_Students].firstNamePtr, 
                  (*resultPtr)[*count_Students].secondNamePtr, 
                  (*resultPtr)[*count_Students].groupPtr,
                  &(*resultPtr)->gradesPtr[0], &(*resultPtr)->gradesPtr[1], &(*resultPtr)->gradesPtr[2], 
                  &(*resultPtr)->gradesPtr[3], &(*resultPtr)->gradesPtr[4])) == 9 ) {

        int status;

        if ((*resultPtr)[*count_Students].id < 0) {
            return INVALID_INPUT;
        }

        error = valid_name((*resultPtr)[*count_Students].firstNamePtr, &status);

        if (error != OK) {
            return error;
        }

        if (status) {
            return INVALID_INPUT;
        }

        error = valid_name((*resultPtr)[*count_Students].secondNamePtr, &status);

        if (error != OK) {
            return error;
        }

        if (status) {
            return INVALID_INPUT;
        }

        // if ((*resultPtr)->gradesPtr[0] - (unsigned char)'0' > 5 || (*resultPtr)->gradesPtr[0] - (unsigned char)'0' < 2) {
        //     printf("%d\n", ((*resultPtr)->gradesPtr[0] - (unsigned char)'0'));
        //     return INVALID_INPUT;
        // }

        // if ((*resultPtr)->gradesPtr[1] - (unsigned char)'0' > 5 || (*resultPtr)->gradesPtr[1] - (unsigned char)'0' < 2) {
        //     return INVALID_INPUT;
        // }

        // if ((*resultPtr)->gradesPtr[2] - (unsigned char)'0' > 5 || (*resultPtr)->gradesPtr[2] - (unsigned char)'0' < 2) {
        //     return INVALID_INPUT;
        // }

        // if ((*resultPtr)->gradesPtr[3] - (unsigned char)'0' > 5 || (*resultPtr)->gradesPtr[3] - (unsigned char)'0' < 2) {
        //     return INVALID_INPUT;
        // }

        // if ((*resultPtr)->gradesPtr[4] - (unsigned char)'0' > 5 || (*resultPtr)->gradesPtr[4] - (unsigned char)'0' < 2) {
        //     return INVALID_INPUT;
        // }
        
        (*count_Students)++;

        if (*count_Students == capasity) {

            capasity *= 2;
            Student* for_realloc = (Student*)realloc(*resultPtr, sizeof(Student) * capasity);

            if (for_realloc == NULL) {
                return INVALID_MEMORY;
            }

            *resultPtr = for_realloc;
        }

    }

    if (*count_Students == 0) {
        return INVALID_INPUT;
    }

    if (count != 9 && count != -1) {
        return INVALID_INPUT;
    }

    return OK;
}

int compare_Student_ID(const void* a, const void* b) {

    Student* stA = (Student*)a;
    Student* stB = (Student*)b;

    return stA->id - stB->id;

}

int compare_Student_firstName(const void* a, const void* b) {

    Student* stA = (Student*)a;
    Student* stB = (Student*)b;

    return strcmp(stA->firstNamePtr, stB->firstNamePtr);

}

int compare_Student_secondName(const void* a, const void* b) {

    Student* stA = (Student*)a;
    Student* stB = (Student*)b;

    return strcmp(stA->secondNamePtr, stB->secondNamePtr);

}

int compare_Student_group(const void* a, const void* b) {

    Student* stA = (Student*)a;
    Student* stB = (Student*)b;

    return strcmp(stA->groupPtr, stB->groupPtr);

}

ERROR print_Students(Student** resultPtr, int count_Students, FILE* output) {

    if (resultPtr == NULL || *resultPtr == NULL) {
        return INVALID_INPUT;
    }

    double grades_summ = 0, res;

    for (int i = 0; i < count_Students; i++) {
        double grages_Student_summ = 0;
        for(int j = 0; j < 5; j++) {
            grages_Student_summ += (*resultPtr)[i].gradesPtr[j] - '0';
        }
        grades_summ += grages_Student_summ / 5;
    }
    res = grades_summ / count_Students;

    int start = 1;

    for (int i = 0; i < count_Students; i++) {
        double summ_Student_res = 0;
        for(int j = 0; j < 5; j++) {
            summ_Student_res += (*resultPtr)[i].gradesPtr[j] - '0';
        }
        summ_Student_res = summ_Student_res / 5;

        if (res - summ_Student_res >= EPS ) {
            if (start) {
                fprintf(output, "Студенты с оценкой выше средней\n\n");
                start = 0;
            }
            fprintf(output, "%s %s\n", (*resultPtr)->firstNamePtr, (*resultPtr)->secondNamePtr);
        }
        fprintf(output, "\n");
    }

    return OK;

}

ERROR print_Students_in_file(Student** resultPtr, FILE* output, int index, double summ_grades) {

    if (resultPtr == NULL || *resultPtr == NULL || output == NULL) {
        return INVALID_INPUT;
    }

    fprintf(output, "Студент с ID\n\n");
    fprintf(output, "%s %s %s %f\n\n", (*resultPtr)[index].firstNamePtr, (*resultPtr)[index].secondNamePtr, (*resultPtr)[index].groupPtr, summ_grades);

    return OK;
}

ERROR find_Student_by_ID(Student** resultPtr, int count_Students, int studentID, int* index, int* find) {

    if (count_Students <= 0 || resultPtr == NULL || *resultPtr == NULL) {
        return INVALID_INPUT; 
    }

    int low = 0;
    int high = count_Students - 1;

    while (low <= high) {
        int middle = (low + high) / 2;

        if (studentID < (*resultPtr)[middle].id) {
            high = middle - 1;
        } else if (studentID > (*resultPtr)[middle].id) {
            low = middle + 1;
        } else {
            *index = middle;
            *find = 1;
            return OK;
        }
    }

    return OK;

}

ERROR find_Student_by_firstName(Student** resultPtr, int count_Students, char* name, int* index, int* find) {

    if (count_Students <= 0 || resultPtr == NULL || *resultPtr == NULL) {
        return INVALID_INPUT; 
    }

    int low = 0;
    int high = count_Students - 1;

    while (low <= high) {
        int middle = (low + high) / 2;

        if (strcmp(name, (*resultPtr)[middle].firstNamePtr) < 0) {
            high = middle - 1;
        } else if (strcmp(name, (*resultPtr)[middle].firstNamePtr) > 0) {
            low = middle + 1;
        } else {
            *index = middle;
            *find = 1;
            break;
        }
    }

    while(!strcmp(name, (*resultPtr)[*index - 1].firstNamePtr)) {
        (*index)--;
    }

    return OK;

}

ERROR find_Student_by_secondName(Student** resultPtr, int count_Students, char* secondName, int* index, int* find) {

    if (count_Students <= 0 || resultPtr == NULL || *resultPtr == NULL) {
        return INVALID_INPUT; 
    }

    int low = 0;
    int high = count_Students - 1;

    while (low <= high) {
        int middle = (low + high) / 2;

        if (strcmp(secondName, (*resultPtr)[middle].secondNamePtr) < 0) {
            high = middle - 1;
        } else if (strcmp(secondName, (*resultPtr)[middle].secondNamePtr) > 0) {
            low = middle + 1;
        } else {
            *index = middle;
            *find = 1;
            break;
        }
    }

    while(!strcmp(secondName, (*resultPtr)[*index - 1].secondNamePtr)) {
        (*index)--;
    }

    return OK;

}

ERROR find_Student_by_group(Student** resultPtr, int count_Students, char* group, int* index, int* find) {

    if (count_Students <= 0 || resultPtr == NULL || *resultPtr == NULL) {
        return INVALID_INPUT; 
    }

    int low = 0;
    int high = count_Students - 1;

    while (low <= high) {
        int middle = (low + high) / 2;

        if (strcmp(group, (*resultPtr)[middle].groupPtr) < 0) {
            high = middle - 1;
        } else if (strcmp(group, (*resultPtr)[middle].groupPtr) > 0) {
            low = middle + 1;
        } else {
            *index = middle;
            *find = 1;
            break;
        }
    }

    while(!strcmp(group, (*resultPtr)[*index - 1].groupPtr)) {
        (*index)--;
    }

    return OK;

}