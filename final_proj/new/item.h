// Shani Sharon 212432967
// Itai Shaya 207033622

#pragma once


#include <stdbool.h>
#include "customer.h"

typedef struct item {
    int id;
    char itemType[20];
    char countryMade[20];
    char manufacturingDate[11];
    float price;
    bool inStock;
    int inventory;
    struct item* next;
} Item;

typedef struct review {
    int itemId;
    char itemType[20];
    int customerReview;
    struct review* next;
} Review;

void AddNewItem(Item* itemList);
void DisplayItemDetails(Item* item);
int SearchItem(Item* itemList);
void UpdateItemDetails(Item* itemList);
void RemoveItemById(Item* itemList);
void SellItem(Item* itemList, CustomerItem* customerItemList, Customer* customerList);
void DisplayCustomerPurchases(CustomerItem* customerItemList);
void CalculateProfit(CustomerItem* customerItemList);
void AddCustomerReview(Review* reviewList, Item* itemList);
void GetReviewsByItemId(Review* reviewList);
void ProcessItemReturn(Item* itemList, CustomerItem* customerItemList);
void UpdateInventoryAfterReturn(Item* itemList, CustomerItem* returnedItem, int quantity);