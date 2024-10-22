#include "main.h"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    double eps;


    if (convert_str_to_double(argv[1], &eps) != OK || eps <= 0) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    if (10/eps >= pow(10, 9)) {
        printf("INVALID_INPUT");
        return INVALID_INPUT;
    }

    double res_a = integral(eps, integral_a);
    printf("a: %lf\n", res_a);

    double res_b = integral(eps, integral_b);
    printf("b: %lf\n", res_b);

    double res_c = integral(eps, integral_c);
    printf("c: %lf\n", res_c);

    double res_d = integral(eps, integral_d);
    printf("d: %lf\n", res_d);

    return 0;
}