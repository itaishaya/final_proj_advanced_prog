// Shani Sharon 212432967
// Itai Shaya 207033622

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "customer.h"
#include "menu.h"
#include "item.h"
#include "logs.h"

#define _CRT_SECURE_NO_WARNINGS

void FindCustomerById(Customer* customerList) {
    /* Searches for a customer by ID and prints their details if found.
     * Complexity: O(n), where n is the number of customers.
     */
    Customer* current = customerList->next;
    int customerId;
    bool isFound = false;
    char logMessage[100];

    printf("Enter the ID of the customer you are looking for: ");
    scanf("%d", &customerId);

    while (current != NULL) {
        if (current->id == customerId) {
            isFound = true;
            DisplayCustomerDetails(current);
            sprintf(logMessage, "Customer with ID %d found and details printed.\n", customerId);
            AddLogEntry(logMessage);
            printf("Press any key to continue.\n");
            _getch();
            return;
        }
        current = current->next;
    }

    if (!isFound) {
        printf("Customer with ID %d not found.\n", customerId);
        sprintf(logMessage, "Customer with ID %d not found.\n", customerId);
        AddLogEntry(logMessage);
    }
    printf("Press any key to continue.\n");
    _getch();
}

void DisplayCustomerDetails(Customer* customer) {
    /* Prints the details of a customer. */
    printf("ID: %d\n", customer->id);
    printf("First Name: %s\n", customer->firstName);
    printf("Last Name: %s\n", customer->lastName);

    char joinDateStr[11];
    strftime(joinDateStr, sizeof(joinDateStr), "%d/%m/%Y", localtime(&customer->joinDate));
    printf("Join Date: %s\n", joinDateStr);
}

void AddNewCustomer(Customer* customerList) {
    /* Adds a new customer to the list, sorted by join date.
     * Complexity: O(n), where n is the number of customers.
     */
    time_t currentTime;
    bool isAdded = false;
    Customer* newCustomer = (Customer*)malloc(sizeof(Customer));

    printf("Please enter the following details:\n");
    printf("ID (9 digits): ");
    scanf("%d", &newCustomer->id);

    while (newCustomer->id < 100000000 || newCustomer->id > 999999999) {
        printf("Invalid ID. Please enter a 9-digit ID: ");
        scanf("%d", &newCustomer->id);
    }

    printf("First Name: ");
    scanf("%s", newCustomer->firstName);
    printf("Last Name: ");
    scanf("%s", newCustomer->lastName);

    newCustomer->joinDate = time(&currentTime);

    Customer* current = customerList->next;
    Customer* previous = customerList;

    while (current != NULL) {
        if (difftime(newCustomer->joinDate, current->joinDate) < 0) {
            // Insert new customer in the correct position.
            previous->next = newCustomer;
            newCustomer->next = current;
            isAdded = true;
            break;
        }
        previous = current;
        current = current->next;
    }

    if (!isAdded) {
        // Insert at the end of the list.
        previous->next = newCustomer;
        newCustomer->next = NULL;
    }

    char logMessage[100];
    sprintf(logMessage, "Customer %s %s with ID %d added.\n", newCustomer->firstName, newCustomer->lastName, newCustomer->id);
    AddLogEntry(logMessage);

    printf("Customer added successfully.\n");
    printf("Press any key to continue.\n");
    _getch();
}

void RemoveCustomerById(Customer* customerList) {
    /* Removes a customer by ID.
     * Complexity: O(n), where n is the number of customers.
     */
    int customerId;
    printf("Enter the ID of the customer to remove: ");
    scanf("%d", &customerId);

    Customer* current = customerList->next;
    Customer* previous = customerList;

    while (current != NULL) {
        if (current->id == customerId) {
            previous->next = current->next;
            printf("%s was removed.\n", current->firstName);

            char logMessage[100];
            sprintf(logMessage, "Customer %s %s with ID %d removed.\n", current->firstName, current->lastName, current->id);
            AddLogEntry(logMessage);

            free(current);
            printf("Press any key to continue.\n");
            _getch();
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("Customer with ID %d not found.\n", customerId);
    printf("Press any key to continue.\n");
    _getch();
}