#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <time.h>

typedef enum {
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
} ERROR;

typedef struct {
    char* StringPtr;
    int String_len;
} String;

typedef struct {
    String* cityPtr;
    String* streetPtr;
    String* framePtr;
    String* postal_codePtr;   // 6 цифр
    int apartment_number;     // > 0
    int house_number;         // > 0
} Address;

typedef struct {
    Address* recipients_addressPtr;
    String* postal_idPtr;     //14 цифр
    String* creation_timePtr; //“dd:MM:yyyy hh:mm:ss”
    String* delivery_timePtr; //“dd:MM:yyyy hh:mm:ss”
    float parcel_weight;      // > 0
} Mail;

typedef struct {
    Address* post_officePtr;
    Mail** mail_array;
} Post;






ERROR create_String(char* str, String** resultPtr);
ERROR delete_String_data(String** resultPtr);
ERROR String_cmp(String*const* str1, String*const* str2, int* result);
ERROR String_equivalence(String** str1, String** str2, int* result);
ERROR copy_in_exist_String(String** str1, String** str2);
ERROR copy_in_new_String(String** str1, String** str2);
ERROR concatenation_Strings(String** str1, String** str2);
ERROR destroy_String(String** str);

ERROR create_Address(Address** resultPtr, char* city, char* street, int house_number_, char* frame, int apartment_number_, char* postal_code);
ERROR create_Mail(Mail** mailPtr, Address** addressPtr, float parcel_weight, char* postal_id, char* creation_time, char* delivery_time);
ERROR create_Post_and_add_Address(Post** postPtr, Address** addressPtr);
ERROR create_mail_array(Post** postPtr);
ERROR add_Mail_in_Post(Post** postPtr, Mail** mailPtr, int* mail_count);

ERROR binary_search(Post** postPtr, char* postalCode, int count_mail, int* index);
int copmare_Mails(const void* a, const void* b);
ERROR delete_Mail(Post** postPtr, int index, int* count_mail);
ERROR delete_Post(Post** postPtr, int* count_mail);
int compare_Mail_By_Time(const void* a, const void* b);
ERROR isDeliveredMail(Mail** mail, int* result);

#endif