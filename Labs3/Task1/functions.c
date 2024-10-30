#include "main.h"

int binary_remainder_of_division(int a, int r) {
    return ((a >> r) << r) ^ a;
}

void increment(int *a) {

    if (a == NULL) {
        return INVALID_INPUT;
    }

    int carry = 1;

    while (carry) {

        int result = *a ^ carry; // +1 XOR-ом

        carry = (*a & carry) << 1; // проверяем будет ли перенос и сдвигаем

        *a = result;

    }

    // return OK;

}

void decrement(int *a) {

    // if (a == NULL) {
    //     return INVALID_INPUT;
    // }

    int carry = 1;

    while(carry) {

        int result = *a ^ carry; // -1 XOR-ом

        carry = (~(*a) & carry) << 1; // проверяем будет ли перенос и сдвигаем

        *a = result;

    }
}

ERROR binary_conversion(int r, const long long int number, char* result) {

    char my_ASCII[] = "0123456789ABCDEFGHIJKLMNOPQRSTUV";

    if (result == NULL) {
        return INVALID_INPUT;
    } else if (number >= LLONG_MAX || number <= -LLONG_MAX) {
        return INVALID_INPUT;
    }

    long long int number_ = number;

    if (number < 0) {
        number_ = ~number_ + 1;
    }

    int index = 0;

    while (number_) {

        int digit = binary_remainder_of_division(number_, r);

        result[index] = my_ASCII[digit];

        increment(&index);

        number_ = number_ >> r;
    }

    if (number < 0) {
        result[index] = '-';
        increment(&index);
    }

    result[index] = '\0';

    decrement(&index);

    int j = index;

    increment(&index);

    for (int i = 0; i < (index >> 1); increment(&i)) {
        char temp = result[i];
        result[i] = result[j];
        result[j] = temp;
        decrement(&j);
    }

    return OK;

}