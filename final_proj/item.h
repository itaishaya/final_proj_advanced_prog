// Shani Sharon *ID*
// Itai Shaya 207033622

#pragma once

#include <stdbool.h>
#include "customer.h"

typedef struct item {
    int id;
    char item_type[20];
    char country_made[20];
    char manufacturing_date[11];
    float price;
    bool inStock;
    int inventory;
    struct item* next;
} Item;

typedef struct review {
    int item_id;
    char item_type[20];
    int customer_review;
    struct review* next;
} Review;


void AddNewItem(Item* head);
void printItemCharacteristics(Item* item);
int searchItems(Item* head);
void UpdateItem(Item* head);
void RemoveItem(Item* head);
void SellItem(Item* items_head, ItemsOfCustomer* item_of_customer_head);
void PurchasedItemsByCustomer(ItemsOfCustomer* items_of_customer_head);
void ShowProfit(ItemsOfCustomer* items_of_customer_head);
void AddCustomerReview(Review* review_head);
void GetRreviewsBySpecificItem(Review* review_head);
void ReturnItem(Item* items_head, ItemsOfCustomer* items_of_customer_head);
void UpdateReturningInItemList(Item* items_head, ItemsOfCustomer* current_item_of_customer, int temp_quantity);