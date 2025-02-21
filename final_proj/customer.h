// Shani Sharon *ID*
// Itai Shaya 207033622

#pragma once

#include <time.h>

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

void SearchCustomers(Customer* head);
void PrintCustomerCharacteristics(Customer* current);
void AddNewCustomer(Customer* head);
void RemoveCustomer(Customer* head);
