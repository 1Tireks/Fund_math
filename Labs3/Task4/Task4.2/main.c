#include "main.h"

int main() {

    Post* postPtr = NULL;
    int mail_count = 0;
    ERROR error = OK;


    int choice, exit = 1;

    while (exit) {
        printf("1) Добавить Mail\n2) Удалить Mail по ID\n3) Найти Mail по ID\n4) Список Доставленных Mails\n5) Список Недоставленных Mails\n6) Выход\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        while (getchar() != '\n') {}

        switch (choice) {
            case 1: {

                if (postPtr == NULL && mail_count == 0) {

                    Address* address_postPtr = NULL;

                    char city_post[50];
                    char street_post[50];
                    char frame_post[20];
                    char postal_code_post[20];
                    int house_number_post;
                    int apartment_number_post;

                    printf("Введите данные о почтовом отделении:\n1) Город почтового отделения\n2) Улица почтового отделения\n3) Номер дома почтового отделения\n4) Корпус почтового отделения\n5) Номер квартиры почтового отделения\n6) Индекс почтового отделения\n");

                    printf("Город почтового отделения: ");
                    scanf("%s", city_post);
                    while (getchar() != '\n') {}

                    printf("Улица почтового отделения: ");
                    fgets(street_post, sizeof(street_post), stdin);
                    street_post[strcspn(street_post, "\n")] = '\0';

                    printf("Номер дома почтового отделения: ");
                    scanf("%d", &house_number_post);
                    while (getchar() != '\n') {}

                    printf("Корпус почтового отделения: ");
                    scanf("%s", frame_post);
                    while (getchar() != '\n') {}

                    printf("Номер квартиры почтового отделения: ");
                    scanf("%d", &apartment_number_post);
                    while (getchar() != '\n') {}

                    printf("Индекс почтового отделения: ");
                    scanf("%s", postal_code_post);
                    while (getchar() != '\n') {}

                    error = create_Address(&address_postPtr, city_post, street_post, house_number_post, frame_post, apartment_number_post, postal_code_post);
                    
                    if (error != OK) {
                        delete_Post(&postPtr, &mail_count);
                        return error;
                    }
                    error = create_Post_and_add_Address(&postPtr, &address_postPtr);

                    if (error != OK) {
                        delete_Post(&postPtr, &mail_count);
                        return error;
                    }
                    postPtr->mail_array = NULL;
                    
                }

                char city[50];
                char street[50];
                char frame[20];
                char postal_code[20];
                char postal_id[30];
                char creation_time[30];
                char delivery_time[30];
                int apartment_number_;
                int house_number_;
                float parcel_weight_;

                printf("Введите данные получателя:\n1) Город\n2) Улица\n3) Номер дома\n4) Корпус\n5) Номер квартиры\n6) Индекс получателя\n7) Вес посылки\n8) Почтовый идентификатор\n9) Время создания\n10) Время вручения\n");

                printf("Город получателя: ");
                scanf("%s", city);
                while (getchar() != '\n') {}

                printf("Улица получателя: ");
                fgets(street, sizeof(street), stdin);
                street[strcspn(street, "\n")] = '\0';

                printf("Номер дома получателя: ");
                scanf("%d", &house_number_);
                while (getchar() != '\n') {}

                printf("Корпус получателя: ");
                scanf("%s", frame);
                while (getchar() != '\n') {}

                printf("Номер квартиры получателя: ");
                scanf("%d", &apartment_number_);
                while (getchar() != '\n') {}

                printf("Индекс получателя: ");
                scanf("%s", postal_code);
                while (getchar() != '\n') {}

                printf("Вес посылки: ");
                scanf("%f", &parcel_weight_);
                while (getchar() != '\n') {}

                printf("Почтовый идентификатор: ");
                scanf("%s", postal_id);
                while (getchar() != '\n') {}

                printf("Время создания: ");
                fgets(creation_time, sizeof(creation_time), stdin);
                creation_time[strcspn(creation_time, "\n")] = '\0';

                printf("Время вручения: ");
                fgets(delivery_time, sizeof(delivery_time), stdin);
                delivery_time[strcspn(delivery_time, "\n")] = '\0';

                Address* addressPtr = NULL;
                Mail* mailPtr = NULL;
                

                error = create_Address(&addressPtr, city, street, house_number_, frame, apartment_number_, postal_code);

                if (error != OK) {
                    printf("create_Address %d\n", error);
                    delete_Post(&postPtr, &mail_count);
                    return error;
                }
                error = create_Mail(&mailPtr, &addressPtr, parcel_weight_, postal_id, creation_time, delivery_time);

                if (error != OK) {
                    printf("create_Mail %d\n", error);
                    delete_Post(&postPtr, &mail_count);
                    return error;
                }

                error = add_Mail_in_Post(&postPtr, &mailPtr, &mail_count);

                if (error != OK) {
                    printf("add_Mail_in_Post %d\n", error);
                    delete_Post(&postPtr, &mail_count);
                    return error;
                }


                //printf("Адрес почтового отделения:\n\n%s\n%s\n%d\n%s\n%d\n%s\n", (*postPtr).post_officePtr->cityPtr->StringPtr, (*postPtr).post_officePtr->streetPtr->StringPtr, (*postPtr).post_officePtr->house_number, (*postPtr).post_officePtr->framePtr->StringPtr, (*postPtr).post_officePtr->apartment_number, (*postPtr).post_officePtr->postal_codePtr->StringPtr);
                //printf("Адрес получателя:\n\n%s\n%s\n%d\n%s\n%d\n%s\n", ((*postPtr).mail_array)[mail_count - 1]->recipients_addressPtr->cityPtr->StringPtr, ((*postPtr).mail_array)[mail_count - 1]->recipients_addressPtr->streetPtr->StringPtr, ((*postPtr).mail_array)[mail_count - 1]->recipients_addressPtr->house_number, ((*postPtr).mail_array)[mail_count - 1]->recipients_addressPtr->framePtr->StringPtr, ((*postPtr).mail_array)[mail_count - 1]->recipients_addressPtr->house_number, ((*postPtr).mail_array)[mail_count - 1]->recipients_addressPtr->postal_codePtr->StringPtr);
                //printf("Инфа о посылке:\n\n%f\n%s\n%s\n%s\n", ((*postPtr).mail_array)[mail_count - 1]->parcel_weight, ((*postPtr).mail_array)[mail_count - 1]->postal_idPtr->StringPtr, ((*postPtr).mail_array)[mail_count - 1]->creation_timePtr->StringPtr, ((*postPtr).mail_array)[mail_count - 1]->delivery_timePtr->StringPtr);


                break;
            }
            case 2: {

                if (postPtr == NULL) {
                    printf("ЙЕЙ Саздай пост баля\n");
                    break;
                }

                if ((*postPtr).mail_array == NULL) {
                    printf("Удалять НЕЧЕГО!!!\n");
                    break;
                }

                char postal_id_for_search[20];

                printf("Почтовый идентификатор: ");
                scanf("%s", postal_id_for_search);
                while (getchar() != '\n') {}
                int index;

                qsort((*postPtr).mail_array, mail_count, sizeof(Mail*), copmare_Mails);

                error = binary_search(&postPtr, postal_id_for_search, mail_count, &index);

                if (error != OK) {
                    printf("%d", error);
                    delete_Post(&postPtr, &mail_count);
                    return error;
                }

                error = delete_Mail(&postPtr, index, &mail_count);

                if (error != OK) {
                    printf("%d", error);
                    delete_Post(&postPtr, &mail_count);
                    return error;
                }
                break;
            }
            case 3: {

                if (postPtr == NULL) {
                    printf("ЙЕЙ Саздай пост баля\n");
                    break;
                }

                if ((*postPtr).mail_array == NULL) {
                    printf("Удалять НЕЧЕГО!!!\n");
                    break;
                }

                char postal_id_for_search[20];

                printf("Почтовый идентификатор: ");
                scanf("%s", postal_id_for_search);
                while (getchar() != '\n') {}
                int i;

                qsort((*postPtr).mail_array, mail_count, sizeof(Mail*), copmare_Mails);

                error = binary_search(&postPtr, postal_id_for_search, mail_count, &i);

                if (error != OK) {
                    printf("%d", error);
                    delete_Post(&postPtr, &mail_count);
                    return error;
                }

                printf("Адрес получателя:\n\n%s\n%s\n%d\n%s\n%d\n%s\n\n", ((*postPtr).mail_array)[i]->recipients_addressPtr->cityPtr->StringPtr, ((*postPtr).mail_array)[i]->recipients_addressPtr->streetPtr->StringPtr, ((*postPtr).mail_array)[i]->recipients_addressPtr->house_number, ((*postPtr).mail_array)[i]->recipients_addressPtr->framePtr->StringPtr, ((*postPtr).mail_array)[i]->recipients_addressPtr->house_number, ((*postPtr).mail_array)[i]->recipients_addressPtr->postal_codePtr->StringPtr);
                printf("Инфа о посылке:\n\n%f\n%s\n%s\n%s\n\n", ((*postPtr).mail_array)[i]->parcel_weight, ((*postPtr).mail_array)[i]->postal_idPtr->StringPtr, ((*postPtr).mail_array)[i]->creation_timePtr->StringPtr, ((*postPtr).mail_array)[i]->delivery_timePtr->StringPtr);
                

                break;
            }
            case 4: {

                if (postPtr == NULL) {
                    printf("ЙЕЙ Саздай пост баля\n");
                    break;
                }

                if ((*postPtr).mail_array == NULL) {
                    printf("Выводить НЕЧЕГО!!!\n");
                    break;
                }


                qsort((*postPtr).mail_array, mail_count, sizeof(Mail*), compare_Mail_By_Time);

                printf("Информация о почтовом отделении:\n\n");
                printf("Адрес почтового отделения:\n\n%s\n%s\n%d\n%s\n%d\n%s\n\n", (*postPtr).post_officePtr->cityPtr->StringPtr, (*postPtr).post_officePtr->streetPtr->StringPtr, (*postPtr).post_officePtr->house_number, (*postPtr).post_officePtr->framePtr->StringPtr, (*postPtr).post_officePtr->apartment_number, (*postPtr).post_officePtr->postal_codePtr->StringPtr);

                for (int i = 0; i < mail_count; i++) {

                    int result, counter = 1;

                    error = isDeliveredMail(&(*postPtr).mail_array[i], &result);

                    if (error != OK) {
                        printf("%d", error);
                        delete_Post(&postPtr, &mail_count);
                        return error;
                    }

                    if (result) {
                        printf("Mail №%d:\n", counter);
                        counter++;
                        printf("Адрес получателя:\n\n%s\n%s\n%d\n%s\n%d\n%s\n\n", ((*postPtr).mail_array)[i]->recipients_addressPtr->cityPtr->StringPtr, ((*postPtr).mail_array)[i]->recipients_addressPtr->streetPtr->StringPtr, ((*postPtr).mail_array)[i]->recipients_addressPtr->house_number, ((*postPtr).mail_array)[i]->recipients_addressPtr->framePtr->StringPtr, ((*postPtr).mail_array)[i]->recipients_addressPtr->house_number, ((*postPtr).mail_array)[i]->recipients_addressPtr->postal_codePtr->StringPtr);
                        printf("Инфа о посылке:\n\n%f\n%s\n%s\n%s\n\n", ((*postPtr).mail_array)[i]->parcel_weight, ((*postPtr).mail_array)[i]->postal_idPtr->StringPtr, ((*postPtr).mail_array)[i]->creation_timePtr->StringPtr, ((*postPtr).mail_array)[i]->delivery_timePtr->StringPtr);
                    }
                }

                break;

            }
            case 5:
                if (postPtr == NULL) {
                    printf("ЙЕЙ Саздай пост баля\n");
                    break;
                }

                if ((*postPtr).mail_array == NULL) {
                    printf("Выводить НЕЧЕГО!!!\n");
                    break;
                }

                qsort((*postPtr).mail_array, mail_count, sizeof(Mail*), compare_Mail_By_Time);

                printf("Информация о почтовом отделении:\n\n");
                printf("Адрес почтового отделения:\n\n%s\n%s\n%d\n%s\n%d\n%s\n\n", (*postPtr).post_officePtr->cityPtr->StringPtr, (*postPtr).post_officePtr->streetPtr->StringPtr, (*postPtr).post_officePtr->house_number, (*postPtr).post_officePtr->framePtr->StringPtr, (*postPtr).post_officePtr->apartment_number, (*postPtr).post_officePtr->postal_codePtr->StringPtr);

                for (int i = 0; i < mail_count; i++) {

                    int result, counter = 1;

                    error = isDeliveredMail(&(*postPtr).mail_array[i], &result);

                    if (error != OK) {
                        printf("%d", error);
                        delete_Post(&postPtr, &mail_count);
                        return error;
                    }

                    if (!result) {
                        printf("Mail №%d:\n", counter);
                        counter++;
                        printf("Адрес получателя:\n\n%s\n%s\n%d\n%s\n%d\n%s\n\n", ((*postPtr).mail_array)[i]->recipients_addressPtr->cityPtr->StringPtr, ((*postPtr).mail_array)[i]->recipients_addressPtr->streetPtr->StringPtr, ((*postPtr).mail_array)[i]->recipients_addressPtr->house_number, ((*postPtr).mail_array)[i]->recipients_addressPtr->framePtr->StringPtr, ((*postPtr).mail_array)[i]->recipients_addressPtr->house_number, ((*postPtr).mail_array)[i]->recipients_addressPtr->postal_codePtr->StringPtr);
                        printf("Инфа о посылке:\n\n%f\n%s\n%s\n%s\n\n", ((*postPtr).mail_array)[i]->parcel_weight, ((*postPtr).mail_array)[i]->postal_idPtr->StringPtr, ((*postPtr).mail_array)[i]->creation_timePtr->StringPtr, ((*postPtr).mail_array)[i]->delivery_timePtr->StringPtr);
                    }
                }
                break;
            case 6: {
                exit = 0;
                break;
            }
                
            default: {
                printf("Ты инвалид введи нормальное число!\n");
            }
        }
    }

    delete_Post(&postPtr, &mail_count);

    return OK;
}

// 23:06:2023 20:44:36
// 06:07:2025 14:55:08

//06:10:2005 14:14:14