#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#define INITIAL_CAPASITY 10
#define KOPEYKA 10e2

typedef enum {
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    FILE_READING_ERROR,
} ERROR;

typedef struct {
    unsigned int id;
    char FirstName[21];
    char SecondName[51];
    double salary;
} Employer;

ERROR read_info_from_file(FILE* file, Employer** result, int* size_result, int capasity);
ERROR save_employees(FILE* file, Employer** result, int size_result);
int compare_Employer(const void* a, const void* b);
ERROR remove_Emploeer(Employer** resultPtr);

#endif