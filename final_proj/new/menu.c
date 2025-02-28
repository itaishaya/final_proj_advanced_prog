// Shani Sharon 212432967
// Itai Shaya 207033622

#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "item.h"
#include "employee.h"
#include "customer.h"
#include "utils.h"

void DisplayMenu(unsigned int userLevel, Employee* employeeList, Item* itemList, Customer* customerList, CustomerItem* customerItemList, Review* reviewList) {
    /* Displays the menu based on the user's level. */
    printf("\nWelcome to the Shoe Shop!\n\n");

    switch (userLevel) {
    case 1: // Admin
        printf("Admin Menu:\n");
        printf("1 - Search Item\n");
        printf("2 - Add Item\n");
        printf("3 - Remove Item\n");
        printf("4 - Search Customer\n");
        printf("5 - Add Customer\n");
        printf("6 - Remove Customer\n");
        printf("7 - Update Item Details\n");
        printf("8 - Sell Item\n");
        printf("9 - Display Customer Purchases\n");
        printf("10 - Process Item Return\n");
        printf("11 - Calculate Profit\n");
        printf("12 - Get Item Reviews\n");
        printf("13 - Add Item Review\n");
        printf("14 - Add Employee\n");
        printf("15 - Exit\n");
        break;
    case 2: // Employee
        printf("Employee Menu:\n");
        printf("1 - Search Item\n");
        printf("2 - Add Item\n");
        printf("3 - Remove Item\n");
        printf("4 - Search Customer\n");
        printf("5 - Add Customer\n");
        printf("6 - Remove Customer\n");
        printf("7 - Update Item Details\n");
        printf("8 - Sell Item\n");
        printf("9 - Display Customer Purchases\n");
        printf("10 - Process Item Return\n");
        printf("11 - Calculate Profit\n");
        printf("12 - Get Item Reviews\n");
        printf("13 - Add Item Review\n");
        printf("14 - Exit\n");
        break;
    case 3: // Practicioner
        printf("Practicioner Menu:\n");
        printf("1 - Search Item\n");
        printf("2 - Add Item\n");
        printf("3 - Search Customer\n");
        printf("4 - Add Customer\n");
        printf("5 - Display Customer Purchases\n");
        printf("6 - Process Item Return\n");
        printf("7 - Calculate Profit\n");
        printf("8 - Get Item Reviews\n");
        printf("9 - Add Item Review\n");
        printf("10 - Exit\n");
        break;
    default:
        printf("Invalid level. Please enter a level between 1 and 3.\n");
        scanf("%d", &userLevel);
        DisplayMenu(userLevel, employeeList, itemList, customerList, customerItemList, reviewList);
        return;
    }

    HandleMenuSelection(userLevel, employeeList, itemList, customerList, customerItemList, reviewList);
}

int HandleMenuSelection(unsigned int userLevel, Employee* employeeList, Item* itemList, Customer* customerList, CustomerItem* customerItemList, Review* reviewList) {
    /* Handles user menu selection. */
    int selection;
    scanf("%d", &selection);

    while (selection < 1 || selection > 15) {
        printf("Invalid option. Please try again.\n");
        scanf("%d", &selection);
    }

    switch (selection) {
    case 1:
        SearchItem(itemList);
        break;
    case 2:
        AddNewItem(itemList);
        break;
    case 3:
        if (userLevel < 3) RemoveItemById(itemList);
        else FindCustomerById(customerList);
        break;
    case 4:
        if (userLevel < 3) FindCustomerById(customerList);
        else AddNewCustomer(customerList);
        break;
    case 5:
        if (userLevel < 3) AddNewCustomer(customerList);
        else DisplayCustomerPurchases(customerItemList);
        break;
    case 6:
        if (userLevel < 3) RemoveCustomerById(customerList);
        else ProcessItemReturn(itemList, customerItemList);
        break;
    case 7:
        if (userLevel < 3) UpdateItemDetails(itemList);
        else CalculateProfit(customerItemList);
        break;
    case 8:
        if (userLevel < 3) SellItem(itemList, customerItemList, customerList);
        else GetReviewsByItemId(reviewList);
        break;
    case 9:
        if (userLevel < 3) DisplayCustomerPurchases(customerItemList);
        else AddCustomerReview(reviewList, itemList);
        break;
    case 10:
        if (userLevel < 3) ProcessItemReturn(itemList, customerItemList);
        else return;
        break;
    case 11:
        if (userLevel < 3) CalculateProfit(customerItemList);
        break;
    case 12:
        if (userLevel < 3) GetReviewsByItemId(reviewList);
        break;
    case 13:
        if (userLevel < 3) AddCustomerReview(reviewList, itemList);
        break;
    case 14:
        if (userLevel == 1) AddNewEmployee(employeeList);
        else return;
        break;
    case 15:
        if (userLevel == 1) return;
        break;
    default:
        printf("Invalid option.\n");
        return;
    }

    DisplayMenu(userLevel, employeeList, itemList, customerList, customerItemList, reviewList);
}

void StartSystem(Employee* employeeList) {
    /* Initializes the system and starts the menu. */
    Item* itemList = LoadItemsFromFile();
    Customer* customerList = LoadCustomersFromFile();
    CustomerItem* customerItemList = LoadCustomerItemsFromFile();
    Review* reviewList = LoadReviewsFromFile();

    Employee* currentEmployee = AuthenticateEmployee(employeeList);

    if (currentEmployee == NULL) {
        printf("Login failed.\n");
        ShutdownSystem(employeeList, itemList, customerList, customerItemList, reviewList);
        return;
    }

    DisplayMenu(currentEmployee->level, employeeList, itemList, customerList, customerItemList, reviewList);
    ShutdownSystem(employeeList, itemList, customerList, customerItemList, reviewList);
}

void ShutdownSystem(Employee* employeeList, Item* itemList, Customer* customerList, CustomerItem* customerItemList, Review* reviewList) {
    /* Saves all data to files and shuts down the system. */
    SaveCustomersToFile(customerList);
    SaveEmployeesToFile(employeeList);
    SaveItemsToFile(itemList);
    SaveCustomerItemsToFile(customerItemList);
    SaveReviewsToFile(reviewList);
}

void SaveCustomersToFile(Customer* customerList) {
    /* Saves the customer list to a file. */
    FILE* customerFile = fopen("customers.txt", "w");
    Customer* current = customerList->next;

    while (current != NULL) {
        char joinDateStr[11];
        strftime(joinDateStr, sizeof(joinDateStr), "%d/%m/%Y", localtime(&current->joinDate));
        fprintf(customerFile, "%d\t%s\t%s\t%s\n", current->id, current->firstName, current->lastName, joinDateStr);
        current = current->next;
    }

    fclose(customerFile);
}

void SaveEmployeesToFile(Employee* employeeList) {
    /* Saves the employee list to a file. */
    FILE* employeeFile = fopen("employees.txt", "w");
    Employee* current = employeeList;

    while (current != NULL) {
        fprintf(employeeFile, "%s\t%s\t%s\t%d\n", current->username, current->firstName, current->password, current->level);
        current = current->next;
    }

    fclose(employeeFile);
}

void SaveItemsToFile(Item* itemList) {
    /* Saves the item list to a file. */
    FILE* itemFile = fopen("items.bin", "wb");
    Item* current = itemList->next;

    while (current != NULL) {
        fwrite(current, sizeof(Item), 1, itemFile);
        current = current->next;
    }

    fclose(itemFile);
}

void SaveCustomerItemsToFile(CustomerItem* customerItemList) {
    /* Saves the customer items list to a file. */
    FILE* customerItemFile = fopen("items_of_customer.bin", "wb");
    CustomerItem* current = customerItemList->next;

    while (current != NULL) {
        fwrite(current, sizeof(CustomerItem), 1, customerItemFile);
        current = current->next;
    }

    fclose(customerItemFile);
}

void SaveReviewsToFile(Review* reviewList) {
    /* Saves the reviews list to a file. */
    FILE* reviewFile = fopen("reviews.txt", "w");
    Review* current = reviewList->next;

    while (current != NULL) {
        fprintf(reviewFile, "%d\t%s\t%d\n", current->itemId, current->itemType, current->customerReview);
        current = current->next;
    }

    fclose(reviewFile);
}