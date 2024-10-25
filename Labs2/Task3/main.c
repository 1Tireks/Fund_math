#include "main.h"

int main() { 
    int* result, current_elem;
    ERROR error = find_word(&result, &current_elem, "test\ntest", 4, "test1.txt", "test1.txt", "test2.txt", "test3.txt");

    if (error != OK){
        if (error == INVALID_INPUT) {
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        } else if (error == INVALID_MEMORY) {
            printf("INVALID_MEMORY\n");
            return INVALID_MEMORY;
        } else if (error == FILE_READING_ERROR) {
            printf("FILE_READING_ERROR\n");
            return FILE_READING_ERROR;
        }
    }

    for (int i = 0; i < current_elem; i++) {
        printf("line %d; simbol %d\n", result[i], result[i+1]);
        i += 1;
    }
    
    printf("Result: %i\n", current_elem / 2);
    free(result);

    return OK;
}