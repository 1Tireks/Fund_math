#include "main.h"

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }
    
    if (!(((argv[1][0] == '-') || (argv[1][0] == '/')) && (argv[1][2] == '\0'))) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    long int number = 0;

    if (convert_str_to_int(argv[2], &number, 10) != OK) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    switch (argv[1][1]) 
    {

    case 'h': {

        int* result_h = NULL;
        int size_arr_result_h = 0;
        ERROR status_h = multiple_of_number(number, &result_h, &size_arr_result_h);

        if (status_h == INVALID_MEMORY) {
            printf("INVALID_MEMORY\n");
            free(result_h);
            result_h = NULL;
            return INVALID_INPUT;
        } else if (status_h == INVALID_INPUT) {
            printf("INVALID_INPUT\n");
            free(result_h);
            result_h = NULL;
            return INVALID_INPUT;
        }

        if (size_arr_result_h == 0) {
            printf("Таких чисел нет.");
        } else {
            for (int i = 0; i < size_arr_result_h; ++i) {
                printf("%d ", result_h[i]);
            }
        }

        free(result_h);
        result_h = NULL;

        break;

    }
    
    case 'p': {

        int res;

        if (isPrime(number, &res) != OK) {
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        }

        if(!res){
            printf("Число является простым.");
        } else {
            printf("Число является cоставным.");
        }

        break;

    }

    case 's': {

        int size_arr_result_s = (number == 0) ? 1 : log10l(labs(number));
        char* result_s = NULL;

        if (split_number_to_digits(number, &result_s, &size_arr_result_s) == INVALID_MEMORY) {
            printf("INVALID_MEMORY\n");
            free(result_s);
            result_s = NULL;
            return INVALID_MEMORY;
        }

        for (int i = 0; i < size_arr_result_s; ++i) {
            printf("%c ", result_s[i]);
        }

        free(result_s);
        result_s = NULL;

        break;

    }

    case 'e': {

        if (number > 10 || number < 0) {
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        }

        table_of_degrees(number);
        
        break;

    }

    case 'a': {

        long long int result_a = 0;

        if (sum_of_numbers(number, &result_a) == INVALID_MEMORY)
        {
            printf("INVALID_MEMORY");
            return INVALID_MEMORY;
        }

        printf("%lld", result_a);

        break;

    }
    
    case 'f': {

        if(number < 0) {
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        }

        unsigned long long int result_f = 1;

        if(factorial_of_a_number(number, &result_f) == INVALID_MEMORY) {
            printf("INVALID_MEMORY\n");
            return INVALID_MEMORY;
        }

        printf("%llu\n", result_f);

        break;

    }

    default:

        printf("Ошибка: такого флага нет в доступных флагах: %s\n", argv[1]);

        break;

    }

    return OK;

}