#pragma once

#include <time.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct customer_item {
    int customerId;
    int itemId;
    int itemQuantity;
    float itemPrice;
    time_t purchaseDate;
    struct customer_item* next;
} CustomerItem;

typedef struct customer {
    int id;
    char firstName[10];
    char lastName[10];
    time_t joinDate;
    struct customer* next;
} Customer;

void FindCustomerById(Customer* customerList);
void DisplayCustomerDetails(Customer* customer);
void AddNewCustomer(Customer* customerList);
void RemoveCustomerById(Customer* customerList);