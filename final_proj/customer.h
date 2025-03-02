// Shani Sharon 212432967
// Itai Shaya 207033622

#pragma once

#include <time.h>
#define _CRT_SECURE_NO_WARNINGS


typedef struct items_of_customer
{
    int customer_id;
    int item_id;
    int item_quantity;
    float item_price;
    time_t purchase_date;
    struct items_of_customer* next;
} ItemsOfCustomer;

typedef struct customer
{
    int id;
    char first_name[10];
    char last_name[10];
    time_t join_date;
    struct customer* next;
} Customer;

void SearchCustomer(Customer* head);
void PrintCustomerDetails(Customer* current);
void AddCustomer(Customer* head);
void RemoveCustomer(Customer* head);
