#include "main.h"

ERROR create_String(char* str, String** resultPtr) {

    if (str == NULL || str[0] == '\0') {
        return INVALID_INPUT;
    }

    *resultPtr = (String *)malloc(sizeof(String));

    if (*resultPtr == NULL) {
        return INVALID_MEMORY;
    }

    (*resultPtr)->String_len = strlen(str);

    (*resultPtr)->StringPtr = (char*)malloc(sizeof(char) * ((*resultPtr)->String_len) + 1);

    if ((*resultPtr)->StringPtr == NULL) {
        return INVALID_MEMORY;
    }

    strcpy((*resultPtr)->StringPtr, str);

    return OK;

}

ERROR delete_String_data(String** resultPtr) {

    if (resultPtr == NULL || *resultPtr == NULL || (*resultPtr)->StringPtr == NULL) {  // Проверка double free(), но только если память 
        return INVALID_INPUT;                                                          // была освобождена а указатель нет, будет плохо
    }

    free((*resultPtr)->StringPtr);
    (*resultPtr)->StringPtr = NULL;
    (*resultPtr)->String_len = 0;

    return OK;

}

ERROR String_cmp(String*const* str1, String*const* str2, int* result) {

    if (*str1 == NULL || *str2 == NULL) {
        return INVALID_INPUT;
    } else if ((*str1)->StringPtr == NULL || (*str2)->StringPtr == NULL) {
        return INVALID_INPUT;
    }

    if ((*str1)->String_len == (*str2)->String_len) {

        *result = strcmp((*str1)->StringPtr, (*str2)->StringPtr);

        return OK;

    }

    *result = abs((*str1)->String_len - (*str2)->String_len);

    return OK;

}

ERROR String_equivalence(String** str1, String** str2, int* result) {

    if (*str1 == NULL || *str2 == NULL) {
        return INVALID_INPUT;
    } else if ((*str1)->StringPtr == NULL || (*str2)->StringPtr == NULL) {
        return INVALID_INPUT;
    }

    *result = strcmp((*str1)->StringPtr, (*str2)->StringPtr) ? 1 : 0;

    return OK;

}

ERROR copy_in_exist_String(String** str1, String** str2) { // Из str2 в str1

    if (*str1 == NULL || *str2 == NULL) {
        return INVALID_INPUT;
    } else if ((*str1)->StringPtr == NULL || (*str2)->StringPtr == NULL) {
        return INVALID_INPUT;
    } else if ((*str2)->String_len == 0) {
        return INVALID_INPUT;
    }

    strcpy((*str1)->StringPtr, (*str2)->StringPtr);

    (*str1)->String_len = (*str2)->String_len;

    return OK;

}

ERROR copy_in_new_String(String** str1, String** str2) { // Из str2 в str1

    if (*str2 == NULL) {
        return INVALID_INPUT;
    } else if ((*str2)->StringPtr == NULL) {
        return INVALID_INPUT;
    } else if ((*str2)->String_len == 0) {
        return INVALID_INPUT;
    }

    ERROR error = OK;

    error = create_String((*str2)->StringPtr, str1);

    if (error != OK) {
        return error;
    }

    return OK;

}

ERROR concatenation_Strings(String** str1, String** str2) { // Из str2 в str1

    if (*str1 == NULL || *str2 == NULL) {
        return INVALID_INPUT;
    } else if ((*str1)->StringPtr == NULL || (*str2)->StringPtr == NULL) {
        return INVALID_INPUT;
    }

    char* for_realloc = (char*)realloc((*str1)->StringPtr, (*str1)->String_len + (*str2)->String_len + 1);

    if (for_realloc == NULL) {
        return INVALID_INPUT;
    }

    (*str1)->StringPtr = for_realloc;

    for_realloc = NULL;

    strcat((*str1)->StringPtr, (*str2)->StringPtr);

    (*str1)->String_len += (*str2)->String_len;

    return OK;
}

ERROR destroy_String(String** str) {

    if (str == NULL || *str == NULL || (*str)->StringPtr == NULL) {  // Проверка double free(), но только если память  
        return INVALID_INPUT;                                        // была освобождена а указатель нет, будет плохо
    }

    free((*str)->StringPtr);
    (*str)->StringPtr = NULL;
    free(*str);
    *str = NULL;

    return OK;

}

ERROR valid_name_city_street(char* name) {

    if (name == NULL || name[0] == '\0') {
        return INVALID_INPUT;
    }

    int i = 0;
    char c;

    while ((c = name[i]) != '\0') {

        if (i == 0 && (c < 'A' || c > 'Z')) {
            return INVALID_INPUT;
        } else if ((i != 0 && (c < 'a' || c > 'z')) && c != ' ') {
            return INVALID_INPUT;
        }

        i++;
    }

    return OK;
}

ERROR valid_postal_code(char* postal_code) {

    if (postal_code == NULL) {
        return INVALID_INPUT;
    }

    int i = 0;
    char c;

    while ((c = postal_code[i]) != '\0') {
        if (c < '0' || c > '9') {
            return INVALID_INPUT;
        }

        i++;
    }

    return OK;
}

ERROR valid_frame(char* frame) {

    if (frame == NULL) {
        return INVALID_INPUT;
    }

    int i = 0;
    char c;

    while ((c = frame[i]) != '\0') {
        if (c >= '0' || c <= '9') {
            i++;
            continue;
        } else if (c >= 'a' || c <= 'z') {
            i++;
            continue;
        } else {
            return INVALID_INPUT;
        }
    }

    return OK;
}

int year_visokosniy(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

ERROR valid_time(char* time) {

    if (time == NULL) {
        return INVALID_INPUT;
    }

    int day, month, year, hour, minute, second;
    if (sscanf(time, "%2d:%2d:%4d %2d:%2d:%2d", &day, &month, &year, &hour, &minute, &second) != 6) {
        printf("INVALID_INPUT\n");
        return INVALID_INPUT;
    }

    if (month < 1 || month > 12) {
        printf("month\n");
        return INVALID_INPUT;
    }

    int days[] = {31, 28 + year_visokosniy(year), 31, 30, 31, 30, 31, 30, 31, 30, 31, 30};
    
    if (day < 1 || day > 31 || day > days[month]) {
        printf("day\n");
        return INVALID_INPUT;
    } else if (hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59) {
        printf("hour\n");
        return INVALID_INPUT;
    }

    return OK;

}

ERROR create_Address(Address** resultPtr, char* city, char* street, int house_number_, char* frame, int apartment_number_, char* postal_code) {

    if (frame == NULL || frame[0] == '\0') {
        return INVALID_INPUT;
    } else if (postal_code == NULL || postal_code[0] == '\0') {
        return INVALID_INPUT;
    } else if (house_number_ <= 0 || apartment_number_ <= 0) {
        return INVALID_INPUT;
    }

    ERROR error = OK;

    error = valid_name_city_street(city);

    if (error != OK) {
        printf("city\n");
        return error;
    }

    error = valid_name_city_street(street);

    if (error != OK) {
        printf("street\n");
        return error;
    }

    error = valid_frame(frame);

    if (error != OK) {
        printf("frame\n");
        return error;
    }

    error = valid_postal_code(postal_code);

    if (error != OK) {
        printf("postal_code\n");
        return error;
    }

    *resultPtr = (Address*)malloc(sizeof(Address));

    if (*resultPtr == NULL) {
        return INVALID_MEMORY;
    }

    error = create_String(city, &((*resultPtr)->cityPtr));

    if (error != OK) {                                              // Очистить память
        return error;
    }

    error = create_String(street, &((*resultPtr)->streetPtr));

    if (error != OK) {                                              // Очистить память
        return error;
    }

    error = create_String(frame, &((*resultPtr)->framePtr));

    if (error != OK) {                                              // Очистить память
        return error;
    }

    error = create_String(postal_code, &((*resultPtr)->postal_codePtr));

    if ((*resultPtr)->postal_codePtr->String_len != 6) {
        return INVALID_INPUT;
    }

    if (error != OK) {                                              // Очистить память
        return error;
    }

    (*resultPtr)->apartment_number = apartment_number_;

    (*resultPtr)->house_number = house_number_;

    return OK;

}



ERROR create_Mail(Mail** mailPtr, Address** addressPtr, float parcel_weight, char* postal_id, char* creation_time, char* delivery_time) {

    if (addressPtr == NULL || *addressPtr == NULL || 
        (*addressPtr)->cityPtr == NULL || 
        (*addressPtr)->streetPtr == NULL || 
        (*addressPtr)->framePtr == NULL || 
        (*addressPtr)->postal_codePtr == NULL ||
        (*addressPtr)->cityPtr->StringPtr == NULL || 
        (*addressPtr)->streetPtr->StringPtr == NULL || 
        (*addressPtr)->framePtr->StringPtr == NULL || 
        (*addressPtr)->postal_codePtr->StringPtr == NULL) {
        return INVALID_INPUT;
    } else if (postal_id == NULL || postal_id[0] == '\0') {
        return INVALID_INPUT;
    } else if (creation_time == NULL || creation_time[0] == '\0') {
        return INVALID_INPUT;
    } else if (delivery_time == NULL || delivery_time[0] == '\0') {
        return INVALID_INPUT;
    } else if (parcel_weight <= 0) {
        printf("11");
        return INVALID_INPUT;
    }

    ERROR error = OK;

    *mailPtr = (Mail*)malloc(sizeof(Mail));

    if (*mailPtr == NULL) {
        return INVALID_MEMORY;
    }

    error = valid_postal_code(postal_id);

    if (error != OK) {
        printf("valid_postal_code");
        return INVALID_INPUT;
    }

    error = valid_time(creation_time);

    if (error != OK) {
        printf("valid_time1");
        return error;
    }

    error = valid_time(delivery_time);

    if (error != OK) {
        printf("valid_time2");
        return error;
    }

    error = create_String(postal_id, &((*mailPtr)->postal_idPtr));

    if (error != OK) {                                              // Очистить память
        return error;
    } else if ((*mailPtr)->postal_idPtr->String_len != 14) {
        return INVALID_INPUT;
    }

    error = create_String(creation_time, &((*mailPtr)->creation_timePtr));

    if (error != OK) {                                              // Очистить память
        return error;
    }

    error = create_String(delivery_time, &((*mailPtr)->delivery_timePtr));

    if (error != OK) {                                              // Очистить память
        return error;
    } 

    (*mailPtr)->recipients_addressPtr = *addressPtr;

    (*mailPtr)->parcel_weight = parcel_weight;

    return OK;

}

ERROR create_Post_and_add_Address(Post** postPtr, Address** addressPtr) {

    if (addressPtr == NULL || *addressPtr == NULL || 
        (*addressPtr)->cityPtr == NULL || 
        (*addressPtr)->streetPtr == NULL || 
        (*addressPtr)->framePtr == NULL || 
        (*addressPtr)->postal_codePtr == NULL ||
        (*addressPtr)->cityPtr->StringPtr == NULL || 
        (*addressPtr)->streetPtr->StringPtr == NULL || 
        (*addressPtr)->framePtr->StringPtr == NULL || 
        (*addressPtr)->postal_codePtr->StringPtr == NULL) {
        return INVALID_INPUT;
    }

    *postPtr = (Post*)malloc(sizeof(Post));

    if (*postPtr == NULL) {
        return INVALID_INPUT;
    }

    (*postPtr)->post_officePtr = *addressPtr;

    return OK;

}

ERROR add_Mail_in_Post(Post** postPtr, Mail** mailPtr, int* mail_count) {

    if (postPtr == NULL || *postPtr == NULL || (*postPtr)->post_officePtr->cityPtr == NULL ||
        (*postPtr)->post_officePtr->cityPtr == NULL ||
        (*postPtr)->post_officePtr->framePtr == NULL ||
        (*postPtr)->post_officePtr->postal_codePtr == NULL ||
        (*postPtr)->post_officePtr->streetPtr == NULL ||
        (*postPtr)->post_officePtr->cityPtr->StringPtr == NULL ||
        (*postPtr)->post_officePtr->framePtr->StringPtr == NULL ||
        (*postPtr)->post_officePtr->postal_codePtr->StringPtr == NULL ||
        (*postPtr)->post_officePtr->streetPtr->StringPtr == NULL) {
        return INVALID_INPUT;
    } else if (mailPtr == NULL || *mailPtr == NULL ) {
        return INVALID_INPUT;
    }

    if (*mail_count == 0) {

        create_mail_array(postPtr);

        ((*postPtr)->mail_array)[(*mail_count)] = *mailPtr;

        (*mail_count)++;

        return OK;
    }

    (*mail_count)++;
    
    Mail** for_realloc = (Mail**)realloc((*postPtr)->mail_array, sizeof(Mail*) * (*mail_count));

    if (for_realloc == NULL) {
        return INVALID_INPUT;
    }

    (*postPtr)->mail_array = for_realloc;

    ((*postPtr)->mail_array)[(*mail_count) - 1] = *mailPtr;

    return OK;

}

ERROR create_mail_array(Post** postPtr) {

    if (postPtr == NULL || *postPtr == NULL || (*postPtr)->post_officePtr->cityPtr == NULL ||
        (*postPtr)->post_officePtr->cityPtr == NULL ||
        (*postPtr)->post_officePtr->framePtr == NULL ||
        (*postPtr)->post_officePtr->postal_codePtr == NULL ||
        (*postPtr)->post_officePtr->streetPtr == NULL ||
        (*postPtr)->post_officePtr->cityPtr->StringPtr == NULL ||
        (*postPtr)->post_officePtr->framePtr->StringPtr == NULL ||
        (*postPtr)->post_officePtr->postal_codePtr->StringPtr == NULL ||
        (*postPtr)->post_officePtr->streetPtr->StringPtr == NULL) {
        return INVALID_INPUT;
    } 

    Mail** temp = (Mail**)malloc(sizeof(Mail*));

    if (temp == NULL) {
        return INVALID_INPUT;
    }

    (*postPtr)->mail_array = temp;

    if ((*postPtr)->mail_array == NULL) {
        return INVALID_MEMORY;
    }

    return OK;

}

int copmare_Mails(const void* a, const void* b) {

    const Mail* mail1 = *(const Mail**)a;
    const Mail* mail2 = *(const Mail**)b;

    int result;

    String_cmp(&mail1->recipients_addressPtr->postal_codePtr, &mail2->recipients_addressPtr->postal_codePtr, &result);

    if (result != 0) {
        return result;
    }

    String_cmp(&mail1->postal_idPtr, &mail2->postal_idPtr, &result);

    return result;
}


ERROR binary_search(Post** postPtr, char* postalId, int count_mail, int* index) {

    if (postPtr == NULL || *postPtr == NULL || (*postPtr)->post_officePtr == NULL ||
        (*postPtr)->post_officePtr->cityPtr == NULL ||
        (*postPtr)->post_officePtr->framePtr == NULL ||
        (*postPtr)->post_officePtr->postal_codePtr == NULL ||
        (*postPtr)->post_officePtr->streetPtr == NULL ||
        (*postPtr)->post_officePtr->cityPtr->StringPtr == NULL ||
        (*postPtr)->post_officePtr->framePtr->StringPtr == NULL ||
        (*postPtr)->post_officePtr->postal_codePtr->StringPtr == NULL ||
        (*postPtr)->post_officePtr->streetPtr->StringPtr == NULL) {
        return INVALID_INPUT;
    } else if ((*postPtr)->mail_array[*index]->creation_timePtr == NULL || count_mail <= 0 ||
               (*postPtr)->mail_array[*index]->delivery_timePtr == NULL ||
               (*postPtr)->mail_array[*index]->postal_idPtr == NULL ||
               (*postPtr)->mail_array[*index]->creation_timePtr->StringPtr == NULL ||
               (*postPtr)->mail_array[*index]->delivery_timePtr->StringPtr == NULL ||
               (*postPtr)->mail_array[*index]->postal_idPtr->StringPtr == NULL ||
               (*postPtr)->mail_array[*index]->recipients_addressPtr->cityPtr == NULL ||
               (*postPtr)->mail_array[*index]->recipients_addressPtr->streetPtr == NULL ||
               (*postPtr)->mail_array[*index]->recipients_addressPtr->framePtr == NULL ||
               (*postPtr)->mail_array[*index]->recipients_addressPtr->postal_codePtr == NULL ||
               (*postPtr)->mail_array[*index]->recipients_addressPtr->cityPtr->StringPtr == NULL ||
               (*postPtr)->mail_array[*index]->recipients_addressPtr->streetPtr->StringPtr == NULL ||
               (*postPtr)->mail_array[*index]->recipients_addressPtr->framePtr->StringPtr == NULL ||
               (*postPtr)->mail_array[*index]->recipients_addressPtr->postal_codePtr->StringPtr == NULL) {
        return INVALID_INPUT;
    }

    int low = 0;
    int high = count_mail - 1;
    ERROR error = OK;

    String* postalIdPtr;
    error = create_String(postalId, &postalIdPtr);
    if (error != OK) {
        return error;
    }

    int check;

    error = String_equivalence(&postalIdPtr, &(*postPtr)->mail_array[0]->postal_idPtr, &check);
    if (error != OK) {
        destroy_String(&postalIdPtr);
        return error;
    }
    
    if (count_mail == 1 && !check) {
        *index = 0;
        return OK;
    } else if (count_mail == 1 && check) {
        printf("Нету таких бро(\n");
        return INVALID_INPUT;
    }

    while (low <= high) {
        int middle = (low + high) / 2;
        int result;

        error = String_equivalence(&postalIdPtr, &(*postPtr)->mail_array[middle]->postal_idPtr, &result);
        if (error != OK) {
            destroy_String(&postalIdPtr);
            return error;
        }

        if (result) {
            *index = middle;
            destroy_String(&postalIdPtr);
            return OK;
        }

        error = String_cmp(&postalIdPtr, &(*postPtr)->mail_array[middle]->postal_idPtr, &result);
        if (error != OK) {
            destroy_String(&postalIdPtr);
            return error;
        }

        if (result > 0) {
            high = middle - 1;
        } else {
            low = middle + 1;
        }
    }

    destroy_String(&postalIdPtr);

    printf("Нету таких бро(\n");
    return INVALID_INPUT;

}

ERROR delete_Mail(Post** postPtr, int index, int* count_mail) {

    if (postPtr == NULL || *postPtr == NULL || (*postPtr)->post_officePtr == NULL ||
        (*postPtr)->post_officePtr->cityPtr == NULL ||
        (*postPtr)->post_officePtr->framePtr == NULL ||
        (*postPtr)->post_officePtr->postal_codePtr == NULL ||
        (*postPtr)->post_officePtr->streetPtr == NULL ||
        (*postPtr)->post_officePtr->cityPtr->StringPtr == NULL ||
        (*postPtr)->post_officePtr->framePtr->StringPtr == NULL ||
        (*postPtr)->post_officePtr->postal_codePtr->StringPtr == NULL ||
        (*postPtr)->post_officePtr->streetPtr->StringPtr == NULL) {
        return INVALID_INPUT;
    } else if ((*postPtr)->mail_array[index]->creation_timePtr == NULL ||
               (*postPtr)->mail_array[index]->delivery_timePtr == NULL ||
               (*postPtr)->mail_array[index]->postal_idPtr == NULL ||
               (*postPtr)->mail_array[index]->creation_timePtr->StringPtr == NULL ||
               (*postPtr)->mail_array[index]->delivery_timePtr->StringPtr == NULL ||
               (*postPtr)->mail_array[index]->postal_idPtr->StringPtr == NULL ||
               (*postPtr)->mail_array[index]->recipients_addressPtr->cityPtr == NULL ||
               (*postPtr)->mail_array[index]->recipients_addressPtr->streetPtr == NULL ||
               (*postPtr)->mail_array[index]->recipients_addressPtr->framePtr == NULL ||
               (*postPtr)->mail_array[index]->recipients_addressPtr->postal_codePtr == NULL ||
               (*postPtr)->mail_array[index]->recipients_addressPtr->cityPtr->StringPtr == NULL ||
               (*postPtr)->mail_array[index]->recipients_addressPtr->streetPtr->StringPtr == NULL ||
               (*postPtr)->mail_array[index]->recipients_addressPtr->framePtr->StringPtr == NULL ||
               (*postPtr)->mail_array[index]->recipients_addressPtr->postal_codePtr->StringPtr == NULL) {
        return INVALID_INPUT;
    }
    destroy_String(&(*postPtr)->mail_array[index]->creation_timePtr);
    (*postPtr)->mail_array[index]->creation_timePtr = NULL;
    destroy_String(&(*postPtr)->mail_array[index]->delivery_timePtr);
    (*postPtr)->mail_array[index]->delivery_timePtr = NULL;
    destroy_String(&(*postPtr)->mail_array[index]->postal_idPtr);
    (*postPtr)->mail_array[index]->postal_idPtr = NULL;

    destroy_String(&(*postPtr)->mail_array[index]->recipients_addressPtr->cityPtr);
    (*postPtr)->mail_array[index]->recipients_addressPtr->cityPtr = NULL;

    destroy_String(&(*postPtr)->mail_array[index]->recipients_addressPtr->streetPtr);
    (*postPtr)->mail_array[index]->recipients_addressPtr->streetPtr = NULL;

    destroy_String(&(*postPtr)->mail_array[index]->recipients_addressPtr->framePtr);
    (*postPtr)->mail_array[index]->recipients_addressPtr->framePtr = NULL;

    destroy_String(&(*postPtr)->mail_array[index]->recipients_addressPtr->postal_codePtr);
    (*postPtr)->mail_array[index]->recipients_addressPtr->postal_codePtr = NULL;

    free((*postPtr)->mail_array[index]->recipients_addressPtr);
    (*postPtr)->mail_array[index]->recipients_addressPtr = NULL;

    free((*postPtr)->mail_array[index]);
    (*postPtr)->mail_array[index] = NULL;

    (*count_mail)--;

    return OK;
}

ERROR delete_Post(Post** postPtr, int* count_mail) {

    if (postPtr == NULL || *postPtr == NULL || (*postPtr)->post_officePtr == NULL ||
        (*postPtr)->post_officePtr->cityPtr == NULL ||
        (*postPtr)->post_officePtr->framePtr == NULL ||
        (*postPtr)->post_officePtr->postal_codePtr == NULL ||
        (*postPtr)->post_officePtr->streetPtr == NULL ||
        (*postPtr)->post_officePtr->cityPtr->StringPtr == NULL ||
        (*postPtr)->post_officePtr->framePtr->StringPtr == NULL ||
        (*postPtr)->post_officePtr->postal_codePtr->StringPtr == NULL ||
        (*postPtr)->post_officePtr->streetPtr->StringPtr == NULL ||
        (*postPtr)->mail_array == NULL) {
        return INVALID_INPUT;
    } 

    ERROR error = OK;

    int count = *count_mail;

    for (int i = 0; i < count; i++) {
        error = delete_Mail(postPtr, i, count_mail);

        if (error != OK) {
            return error;
        }
    }

    free((*postPtr)->mail_array);
    (*postPtr)->mail_array = NULL;

    if (*count_mail == 0) {
        (*postPtr)->mail_array = NULL;
    }

    destroy_String(&(*postPtr)->post_officePtr->postal_codePtr);
    (*postPtr)->post_officePtr->postal_codePtr = NULL;

    destroy_String(&(*postPtr)->post_officePtr->cityPtr);
    (*postPtr)->post_officePtr->cityPtr = NULL;

    destroy_String(&(*postPtr)->post_officePtr->framePtr);
    (*postPtr)->post_officePtr->framePtr = NULL;

    destroy_String(&(*postPtr)->post_officePtr->streetPtr);
    (*postPtr)->post_officePtr->streetPtr = NULL;

    free((*postPtr)->post_officePtr);
    (*postPtr)->post_officePtr = NULL;

    free(*postPtr);
    *postPtr = NULL;

    return OK;
}

int compare_Mail_By_Time(const void* a, const void* b) {
    const Mail* mail1 = *(const Mail**)a;
    const Mail* mail2 = *(const Mail**)b;

    if (mail1->creation_timePtr == NULL || mail2->creation_timePtr == NULL ||
        mail1->creation_timePtr->StringPtr == NULL || mail2->creation_timePtr->StringPtr == NULL) {
        return 0;
    }

    int day1, month1, year1, hour1, minute1, second1;
    int day2, month2, year2, hour2, minute2, second2;

    sscanf(mail1->creation_timePtr->StringPtr, "%2d:%2d:%4d %2d:%2d:%2d", &day1, &month1, &year1, &hour1, &minute1, &second1);

    sscanf(mail2->creation_timePtr->StringPtr, "%2d:%2d:%4d %2d:%2d:%2d", &day2, &month2, &year2, &hour2, &minute2, &second2);

    if (year1 != year2) return year1 - year2;
    if (month1 != month2) return month1 - month2;
    if (day1 != day2) return day1 - day2;
    if (hour1 != hour2) return hour1 - hour2;
    if (minute1 != minute2) return minute1 - minute2;

    return second1 - second2;
}

int parseDateTime(const char* dateTimeStr, struct tm* tm) {
    
    sscanf(dateTimeStr, "%2d:%2d:%4d %2d:%2d:%2d",
           &tm->tm_mday, &tm->tm_mon, &tm->tm_year,
           &tm->tm_hour, &tm->tm_min, &tm->tm_sec);

    tm->tm_mon -= 1;
    tm->tm_year -= 1900;

    return 1;
}

ERROR isDeliveredMail(Mail** mail, int* result) {
    if ((*mail)->delivery_timePtr == NULL || (*mail)->delivery_timePtr->StringPtr == NULL) {
        return INVALID_INPUT;
    }

    struct tm delivery_tm = {0};
    if (!parseDateTime((*mail)->delivery_timePtr->StringPtr, &delivery_tm)) {
        return INVALID_INPUT;
    }

    time_t delivery_time = mktime(&delivery_tm);
    if (delivery_time == -1) {
        return INVALID_INPUT;
    }

    time_t current_time;
    time(&current_time);

    *result = difftime(delivery_time, current_time) <= 0 ? 1 : 0;

    return OK;
}
