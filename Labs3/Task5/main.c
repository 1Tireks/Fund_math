#include "main.h"

int main(int argc, char* argv[]) {

    if (argc < 2 || argc > 3) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    const char* trassFile = NULL;

    if (argc == 3) {
        trassFile = argv[2];

        char* realpath1 = realpath(argv[1], NULL);
        char* realpath2 = realpath(trassFile, NULL);

        if (realpath1 == NULL || realpath2 == NULL) {
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        }

        if (!strcmp(realpath1, realpath2)) {
            free(realpath1);
            free(realpath2);
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        }

        free(realpath1);
        free(realpath2);
    } else {
        char* realpath1 = realpath(argv[1], NULL);

        if (realpath1 == NULL) {
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        }

        free(realpath1);
    }

    FILE* input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("FILE_READING_ERROR\n");
        return FILE_READING_ERROR;
    }

    ERROR error = OK;
    int countStudents = 0;
    Student* studentsPtr = NULL;

    error = read_Students_from_file(input, &countStudents, &studentsPtr, INITIAL_CAPASITY);

    if (error != OK) {
        printf("%d", error);
        return INVALID_INPUT;
    }

    printf("%c %c %c %c %c\n", studentsPtr[0].gradesPtr[0], studentsPtr[0].gradesPtr[1], studentsPtr[0].gradesPtr[2], studentsPtr[0].gradesPtr[3], studentsPtr[0].gradesPtr[4]);

    int choice, exit = 1;

    while (exit) {
        printf("1 - Вывести в файл студентов с средней оценкой выше среднего\n");
        printf("2 - Найти и вывести студента по ID\n");
        printf("3 - Найти и вывести студентов по имени\n");
        printf("4 - Найти и вывести студентов по фамилии\n");
        printf("5 - Найти и вывести студентов по группе\n");
        printf("6 - Сортировать студентов по ID\n");
        printf("7 - Сортировать студентов по имени\n");
        printf("8 - Сортировать студентов по фамилии\n");
        printf("9 - Сортировать студентов по группе\n");
        printf("10 - Вывести студентов\n");
        printf("0 - Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        while (getchar() != '\n') {}

        switch (choice) {

            case 1: {

                if (trassFile) {
                    
                    FILE* output = fopen(trassFile, "w");

                    if (output == NULL) {
                        printf("FILE_READING_ERROR\n");
                        fclose(input);
                        return FILE_READING_ERROR;
                    }
                    error = print_Students(&studentsPtr, countStudents, output);

                    if (error != OK) {
                        return INVALID_INPUT;
                    }

                    fclose(output);

                } else {
                    printf("Нет трассирововчного файла\n");
                }
                break;
            }

            case 2: {
                int id, index;
                printf("Enter ID: ");
                scanf("%d", &id);
                while (getchar() != '\n') {}
                int find = 0;

                qsort(studentsPtr, countStudents, sizeof(Student), compare_Student_ID);

                error = find_Student_by_ID(&studentsPtr, countStudents, id, &index, &find);

                if (error != OK) {
                    return INVALID_INPUT;
                }

                if (find) {
                    double summ_Student_res = 0;
                    for(int j = 0; j < 5; j++) {
                        printf("Grade %d: %u\\n", j, studentsPtr[index].gradesPtr[j]);
                        summ_Student_res += (double)(studentsPtr[index].gradesPtr[j] - '0');
                    }
                    summ_Student_res = summ_Student_res / 5;

                    printf("%s %s %s %f\n", studentsPtr[index].firstNamePtr, studentsPtr[index].secondNamePtr, studentsPtr[index].groupPtr, summ_Student_res);



                    if (trassFile) {
                        FILE* output = fopen(trassFile, "w");

                        if (output == NULL) {
                            printf("FILE_READING_ERROR\n");
                            fclose(input);
                            return FILE_READING_ERROR;
                        }

                        error = print_Students_in_file(&studentsPtr, output, index, summ_Student_res);

                        if (error != OK) {
                            return INVALID_INPUT;
                        }

                        fclose(output);

                    }
                } else {
                    printf("Нет такого\n");
                }

                break;
            }

            case 3: {
                int index;
                char name[51];
                printf("Enter Name: ");
                scanf("%s", name);
                while (getchar() != '\n') {}
                int find = 0;

                qsort(studentsPtr, countStudents, sizeof(Student), compare_Student_firstName);

                error = find_Student_by_firstName(&studentsPtr, countStudents, name, &index, &find);

                if (error != OK) {
                    return INVALID_INPUT;
                }

                if (find) {
                    printf("Найденные студенты\n");
                    while (!strcmp(name, studentsPtr[index].firstNamePtr)) {
                        double summ_Student_res = 0;
                        for (int j = 0; j < 5; j++) {
                            summ_Student_res += studentsPtr[index].gradesPtr[j] - '0';
                        }
                        summ_Student_res /= 5;

                        printf("%s %s %s %f", studentsPtr[index].firstNamePtr, studentsPtr[index].secondNamePtr, studentsPtr[index].groupPtr, summ_Student_res);



                        if (trassFile) {
                            FILE* output = fopen(trassFile, "w");

                            if (output == NULL) {
                                printf("FILE_READING_ERROR\n");
                                fclose(input);
                                return FILE_READING_ERROR;
                            }

                            error = print_Students_in_file(&studentsPtr, output, index, summ_Student_res);

                            if (error != OK) {
                                return INVALID_INPUT;
                            }

                            fclose(output);

                        }
                        index++;
                    }
                } else {
                    printf("Нет такого\n");
                }
                break;
            }

            case 4: {
                int index;
                char secondName[51];
                printf("Enter secondName: ");
                scanf("%s", secondName);
                while (getchar() != '\n') {}
                int find = 0;

                qsort(studentsPtr, countStudents, sizeof(Student), compare_Student_secondName);

                error = find_Student_by_secondName(&studentsPtr, countStudents, secondName, &index, &find);

                if (error != OK) {
                    return INVALID_INPUT;
                }

                if (find) {
                    printf("Найденные студенты\n");
                    while (!strcmp(secondName, studentsPtr[index].firstNamePtr)) {
                        double summ_Student_res = 0;
                        for (int j = 0; j < 5; j++) {
                            summ_Student_res += studentsPtr[index].gradesPtr[j] - '0';
                        }
                        summ_Student_res /= 5;

                        printf("%s %s %s %f", studentsPtr[index].firstNamePtr, studentsPtr[index].secondNamePtr, studentsPtr[index].groupPtr, summ_Student_res);



                        if (trassFile) {
                            FILE* output = fopen(trassFile, "w");

                            if (output == NULL) {
                                printf("FILE_READING_ERROR\n");
                                fclose(input);
                                return FILE_READING_ERROR;
                            }

                            error = print_Students_in_file(&studentsPtr, output, index, summ_Student_res);

                            if (error != OK) {
                                return INVALID_INPUT;
                            }

                            fclose(output);

                        }
                        index++;
                    }
                } else {
                    printf("Нет такого\n");
                }
                break;
            }

            case 5: {
                int index;
                char group[16];
                printf("Enter secondName: ");
                scanf("%s", group);
                while (getchar() != '\n') {}
                int find = 0;

                qsort(studentsPtr, countStudents, sizeof(Student), compare_Student_group);

                error = find_Student_by_group(&studentsPtr, countStudents, group, &index, &find);

                if (error != OK) {
                    return INVALID_INPUT;
                }

                if (find) {
                    printf("Найденные студенты\n");
                    while (!strcmp(group, studentsPtr[index].firstNamePtr)) {
                        double summ_Student_res = 0;
                        for (int j = 0; j < 5; j++) {
                            summ_Student_res += studentsPtr[index].gradesPtr[j] - '0';
                        }
                        summ_Student_res /= 5;

                        printf("%s %s %s %f", studentsPtr[index].firstNamePtr, studentsPtr[index].secondNamePtr, studentsPtr[index].groupPtr, summ_Student_res);



                        if (trassFile) {
                            FILE* output = fopen(trassFile, "w");

                            if (output == NULL) {
                                printf("FILE_READING_ERROR\n");
                                fclose(input);
                                return FILE_READING_ERROR;
                            }

                            error = print_Students_in_file(&studentsPtr, output, index, summ_Student_res);

                            if (error != OK) {
                                return INVALID_INPUT;
                            }

                            fclose(output);

                        }
                        index++;
                    }
                } else {
                    printf("Нет такого\n");
                }
                break;
            }

            case 6: {
                qsort(studentsPtr, countStudents, sizeof(Student), compare_Student_ID);
                break;
            }

            case 7: {
                qsort(studentsPtr, countStudents, sizeof(Student), compare_Student_firstName);
                break;
            }

            case 8: {
                qsort(studentsPtr, countStudents, sizeof(Student), compare_Student_secondName);
                break;
            }

            case 9: {
                qsort(studentsPtr, countStudents, sizeof(Student), compare_Student_group);
                break;
            }
            case 10: {
                for(int i = 0; i < countStudents; i++) {
                    printf("%d %s %s %s\n",studentsPtr[i].id, studentsPtr[i].firstNamePtr, studentsPtr[i].secondNamePtr, studentsPtr[i].groupPtr);
                }
                break;
            }

            case 0: {
                exit = 0;
                break;
            }



        }


    }





    fclose(input);

    return OK;

}