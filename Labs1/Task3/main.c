#include "main.h"

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    } else if (!((argv[1][0] == '-' || argv[1][0] == '/') && argv[1][2] == '\0')) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    switch(argv[1][1]) 
    {
        case 'q': {

            if (argc != 6) {
                printf("INVALID_INPUT\n");
                return INVALID_INPUT;
            }

            double eps, num1, num2, num3;

            if ((convert_str_to_double(argv[2], &eps) != OK) ||
                (convert_str_to_double(argv[3], &num1) != OK) ||
                (convert_str_to_double(argv[4], &num2) != OK) ||
                (convert_str_to_double(argv[5], &num3) != OK))
            {
                printf("INVALID_INPUT\n");
                return INVALID_INPUT;
             }

            if (eps <= 0) {
                printf("INVALID_INPUT\n");
                return INVALID_INPUT;
            }

            generate_permutations(num1, num2, num3, eps);

            break;
        }
        case 'm': {

            if (argc != 4) {
                printf("INVALID_INPUT\n");
                return INVALID_INPUT;
            }

            long int num1, num2;

            if ((convert_str_to_int(argv[2], &num1, 10) != OK) ||
                (convert_str_to_int(argv[3], &num2, 10) != OK) )
            {
                printf("INVALID_INPUT\n");
                return INVALID_INPUT;
            }

            if (num1 == 0 || num2 == 0) {
                printf("INVALID_INPUT\n");
                return INVALID_INPUT;
            }

            if (is_multiple(num1, num2) == 1) {
                printf("Да, делится\n");
            } else {
                printf("Нет, не делится\n");
            }


            break;
        }
        case 't': {

            if (argc != 6) {
                printf("INVALID_INPUT\n");
                return INVALID_INPUT;
            }

            double eps, num1, num2, num3;

            if ((convert_str_to_double(argv[2], &eps) != OK) ||
                (convert_str_to_double(argv[3], &num1) != OK) ||
                (convert_str_to_double(argv[4], &num2) != OK) ||
                (convert_str_to_double(argv[5], &num3) != OK))
            {
                printf("INVALID_INPUT\n");
                return INVALID_INPUT;
            }

            if (eps <= 0) {
                printf("INVALID_INPUT\n");
                return INVALID_INPUT;
            }

            if (can_form_triangle(eps, num1, num2, num3) == 1) {
                printf("Да, являются\n");
            } else {
                printf("Нет, не являются\n");
            }

            break;

        }

        default:

        printf("Такого флага нет в доступных флагах\n");

        break;

    }

    return 0;
}
