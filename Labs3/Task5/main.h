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
#define EPS 10e-2

typedef enum {
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    FILE_READING_ERROR,
} ERROR;

typedef struct {
    int id;
    char firstNamePtr[21];
    char secondNamePtr[51];
    char groupPtr[16];
    unsigned char gradesPtr[5];
} Student;


ERROR read_Students_from_file(FILE* input, int* count_Students, Student** resultPtr, int capasity);
ERROR print_Students(Student** resultPtr, int count_Students, FILE* output);
ERROR find_Student_by_ID(Student** resultPtr, int count_Students, int studentID, int* index, int* find);
ERROR print_Students_in_file(Student** resultPtr, FILE* output, int index, double summ_grades);
ERROR find_Student_by_firstName(Student** resultPtr, int count_Students, char* name, int* index, int* find);
ERROR find_Student_by_secondName(Student** resultPtr, int count_Students, char* secondName, int* index, int* find);
ERROR find_Student_by_group(Student** resultPtr, int count_Students, char* group, int* index, int* find);

int compare_Student_ID(const void* a, const void* b);
int compare_Student_firstName(const void* a, const void* b);
int compare_Student_secondName(const void* a, const void* b);
int compare_Student_group(const void* a, const void* b);


#endif