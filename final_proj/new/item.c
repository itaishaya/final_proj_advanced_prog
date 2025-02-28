#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "menu.h"
#include "item.h"
#include "logs.h"
#include "customer.h"

void AddNewItem(Item* itemList) {
    /* Adds a new item to the inventory.
     * Complexity: O(n), where n is the number of items.
     */
    char logMessage[100];
    Item* newItem = (Item*)malloc(sizeof(Item));

    printf("Enter item details:\n");
    printf("ID: ");
    scanf("%d", &newItem->id);
    printf("Item Type: ");
    scanf("%s", newItem->itemType);
    printf("Country Made: ");
    scanf("%s", newItem->countryMade);
    printf("Price: ");
    scanf("%f", &newItem->price);
    printf("Manufacturing Date (DD/MM/YYYY): ");
    scanf("%s", newItem->manufacturingDate);
    printf("Inventory: ");
    scanf("%d", &newItem->inventory);

    newItem->inStock = (newItem->inventory > 0);
    newItem->next = NULL;

    Item* current = itemList->next;
    Item* previous = itemList;

    while (current != NULL && newItem->id > current->id) {
        previous = current;
        current = current->next;
    }

    // Insert in the middle or at the end.
    previous->next = newItem;
    newItem->next = current;

    sprintf(logMessage, "Item %s added to inventory.\n", newItem->itemType);
    AddLogEntry(logMessage);

    printf("Item added successfully.\n");
    printf("Press any key to continue.\n");
    _getch();
}

void DisplayItemDetails(Item* item) {
    /* Prints the details of an item. */
    printf("\nItem ID: %d\n", item->id);
    printf("Item Type: %s\n", item->itemType);
    printf("Country Made: %s\n", item->countryMade);
    printf("Price: %.2f\n", item->price);
    printf("Manufacturing Date: %s\n", item->manufacturingDate);
    printf("Inventory: %d\n", item->inventory);
    printf("In Stock: %s\n", item->inStock ? "Yes" : "No");
}

int SearchItem(Item* itemList) {
    /* Searches for items based on user-defined criteria.
     * Complexity: O(n), where n is the number of items.
     */
    int selection;
    char itemType[20] = "", countryMade[20] = "", manufacturingDate[11] = "";
    float price = 0;
    int inventory = 0;
    bool inStock = false;

    printf("Search by:\n");
    printf("1 - Item Type\n");
    printf("2 - Country Made\n");
    printf("3 - Item Type and Country Made\n");
    printf("4 - Price (greater than)\n");
    printf("5 - Inventory (greater than)\n");
    printf("6 - Manufacturing Date\n");
    printf("7 - In Stock\n");
    printf("8 - Exit\n");
    scanf("%d", &selection);

    if (selection == 8) {
        return 0;
    }

    switch (selection) {
    case 1:
        printf("Enter Item Type: ");
        scanf("%s", itemType);
        break;
    case 2:
        printf("Enter Country Made: ");
        scanf("%s", countryMade);
        break;
    case 3:
        printf("Enter Item Type: ");
        scanf("%s", itemType);
        printf("Enter Country Made: ");
        scanf("%s", countryMade);
        break;
    case 4:
        printf("Enter Minimum Price: ");
        scanf("%f", &price);
        break;
    case 5:
        printf("Enter Minimum Inventory: ");
        scanf("%d", &inventory);
        break;
    case 6:
        printf("Enter Manufacturing Date (DD/MM/YYYY): ");
        scanf("%s", manufacturingDate);
        break;
    case 7:
        printf("Enter 1 for in stock, 0 for out of stock: ");
        int stockInput;
        scanf("%d", &stockInput);
        inStock = (stockInput == 1);
        break;
    default:
        printf("Invalid selection.\n");
        return 0;
    }

    Item* current = itemList->next;
    bool isFound = false;
    int foundCount = 0;

    while (current != NULL) {
        switch (selection) {
        case 1:
            if (strcmp(itemType, current->itemType) == 0) isFound = true;
            break;
        case 2:
            if (strcmp(countryMade, current->countryMade) == 0) isFound = true;
            break;
        case 3:
            if (strcmp(itemType, current->itemType) == 0 && strcmp(countryMade, current->countryMade) == 0) isFound = true;
            break;
        case 4:
            if (price < current->price) isFound = true;
            break;
        case 5:
            if (inventory < current->inventory) isFound = true;
            break;
        case 6:
            if (strcmp(manufacturingDate, current->manufacturingDate) == 0) isFound = true;
            break;
        case 7:
            if (current->inStock == inStock) isFound = true;
            break;
        }

        if (isFound) {
            DisplayItemDetails(current);
            isFound = false;
            foundCount++;
        }
        current = current->next;
    }

    if (foundCount == 0) {
        printf("No matching items found.\n");
    }

    printf("Press any key to continue.\n");
    _getch();
    return 1;
}

void UpdateItemDetails(Item* itemList) {
    /* Updates an item's details based on user input.
     * Complexity: O(n), where n is the number of items.
     */
    char logMessage[100];
    int itemId;
    bool isFound = false;

    printf("Enter the ID of the item to update: ");
    scanf("%d", &itemId);

    Item* current = itemList->next;

    while (current != NULL) {
        if (current->id == itemId) {
            isFound = true;
            int selection;
            printf("Select field to update:\n");
            printf("1 - Item Type\n");
            printf("2 - Country Made\n");
            printf("3 - Price\n");
            printf("4 - Inventory\n");
            printf("5 - Manufacturing Date\n");
            printf("6 - Exit\n");
            scanf("%d", &selection);

            switch (selection) {
            case 1:
                printf("Enter new Item Type: ");
                scanf("%s", current->itemType);
                sprintf(logMessage, "Item ID %d: Item Type updated to %s.\n", current->id, current->itemType);
                AddLogEntry(logMessage);
                break;
            case 2:
                printf("Enter new Country Made: ");
                scanf("%s", current->countryMade);
                sprintf(logMessage, "Item ID %d: Country Made updated to %s.\n", current->id, current->countryMade);
                AddLogEntry(logMessage);
                break;
            case 3:
                printf("Enter new Price: ");
                scanf("%f", &current->price);
                sprintf(logMessage, "Item ID %d: Price updated to %.2f.\n", current->id, current->price);
                AddLogEntry(logMessage);
                break;
            case 4:
                printf("Enter new Inventory: ");
                scanf("%d", &current->inventory);
                current->inStock = (current->inventory > 0);
                sprintf(logMessage, "Item ID %d: Inventory updated to %d.\n", current->id, current->inventory);
                AddLogEntry(logMessage);
                break;
            case 5:
                printf("Enter new Manufacturing Date: ");
                scanf("%s", current->manufacturingDate);
                sprintf(logMessage, "Item ID %d: Manufacturing Date updated to %s.\n", current->id, current->manufacturingDate);
                AddLogEntry(logMessage);
                break;
            case 6:
                return;
            default:
                printf("Invalid option.\n");
                return;
            }
        }
        current = current->next;
    }

    if (!isFound) {
        printf("Item with ID %d not found.\n", itemId);
        sprintf(logMessage, "Item with ID %d not found.\n", itemId);
        AddLogEntry(logMessage);
    }

    printf("Press any key to continue.\n");
    _getch();
}

void RemoveItemById(Item* itemList) {
    /* Removes an item from the inventory.
     * Complexity: O(n), where n is the number of items.
     */
    char logMessage[100];
    int itemId;

    printf("Enter the ID of the item to remove: ");
    scanf("%d", &itemId);

    Item* current = itemList->next;
    Item* previous = itemList;
    bool isFound = false;

    while (current != NULL) {
        if (current->id == itemId) {
            previous->next = current->next;
            sprintf(logMessage, "Item %s removed from inventory.\n", current->itemType);
            AddLogEntry(logMessage);
            free(current);
            printf("Item removed successfully.\n");
            printf("Press any key to continue.\n");
            _getch();
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("Item with ID %d not found.\n", itemId);
    sprintf(logMessage, "Item with ID %d not found.\n", itemId);
    AddLogEntry(logMessage);

    printf("Press any key to continue.\n");
    _getch();
}