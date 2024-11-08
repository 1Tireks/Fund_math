#include "main.h"

int main() {

    ERROR error = OK;
    char *a = "123456789";
    char *b = "ABCDEFGHI";
    String* string1 = NULL;
    String* string2 = NULL;
    //int cmp;

    // Тест если удаляем несуществующий элемент типа String

    // error = delete_String_content(&string1);

    // if (error != OK) {
    //     printf("%d\n", error);
    //     return error;
    // }





    error = create_String(a, &string1);

    if (error != OK) {
        printf("%d\n", error);
        return error;
    }

    printf("%s %d\n", string1->StringPtr, string1->String_len);

    error = create_String(b, &string2);

    if (error != OK) {
        printf("%d\n", error);
        return error;
    }

    printf("%s %d\n", string2->StringPtr, string2->String_len);


    error = concatenation_Strings(&string1, &string2);

    if (error != OK) {
        printf("%d\n", error);
        return error;
    }

    printf("%s %d\n", string1->StringPtr, string1->String_len);


    




    // error = String_cmp(&string2, &string1, &cmp);

    // if (error != OK) {
    //     printf("%d\n", error);
    //     return error;
    // }

    // printf("%d\n", cmp);



    // error = delete_String_data(&string);

    // if (error != OK) {
    //     printf("%d\n", error);
    //     return error;
    // }

    // printf("%s %d\n", string1->StringPtr, string1->String_len);





    // Тест если удаляем несуществующее поле StringPtr элемента типа String

    // error = delete_String_content(&string1);

    // if (error != OK) {
    //     printf("%d\n", error);
    //     return error;
    // }



    

    // error = copy_in_new_String(&string2, &string1);

    // if (error != OK) {
    //     printf("%d\n", error);
    //     return error;
    // }

    // printf("%s %d\n", string2->StringPtr, string2->String_len);







    error = destroy_String(&string2);

    if (error != OK) {
        printf("%d\n", error);
        return error;
    }

    error = destroy_String(&string1);

    if (error != OK) {
        printf("%d\n", error);
        return error;
    }

    return OK;
}