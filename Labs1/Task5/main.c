#include "main.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    double eps, x, summ = 0.0;;

    switch (convert_str_to_double(argv[1], &eps))
        {
        case INVALID_INPUT:
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        case INVALID_MEMORY:
            printf("INVALID_MEMORY\n");
            return INVALID_MEMORY;
        default:
            break;
        } 
    switch (convert_str_to_double(argv[2], &x))
        {
        case INVALID_INPUT:
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        case INVALID_MEMORY:
            printf("INVALID_MEMORY\n");
            return INVALID_MEMORY;
        default:
            break;
        }

    if (10/eps >= pow(10, 9)) {
        printf("INVALID_INPUT");
        return INVALID_INPUT;
    }
        
    if (first_summ(x, eps, &summ) == DATA_TYPE_OVERFLOW) {
        printf("Переполнение при вычислении суммы 1\n");
    } else {
        printf("Вычисленное значение суммы 1: %lf\n", summ);
    }
    
    summ = 0.0;
    if (second_summ(x, eps, &summ) == DATA_TYPE_OVERFLOW) {
        printf("Переполнение при вычислении суммы 2\n");
    } else {
        printf("Вычисленное значение суммы 2: %lf\n", summ);
    }
    
    summ = 0.0;
    if (third_summ(x, eps, &summ) == DATA_TYPE_OVERFLOW) {
        printf("Ряд 3 расходится\n");
    } else {
        printf("Вычисленное значение суммы 3: %lf\n", summ);
    }
    
    summ = 0.0;
    if (fourth_summ(x, eps, &summ) == DATA_TYPE_OVERFLOW) {
        printf("Ряд 4 расходится\n");
    } else {
        printf("Вычисленное значение суммы 4: %lf\n", summ);
    }    
    
    return OK;


}

