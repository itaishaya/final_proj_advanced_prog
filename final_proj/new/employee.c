#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "employee.h"
#include "logs.h"

int CheckEmployeeFileExists() {
    /* Checks if the employee file exists.
     * Returns 1 if the file exists, 0 otherwise.
     */
    FILE* file = fopen("employees.txt", "r");
    if (file == NULL) {
        return 0;
    }
    fclose(file);
    return 1;
}

Employee* CreateDefaultAdmin() {
    /* Creates a default admin user if no employee file exists.
     * Also creates necessary files for customers, items, logs, and reviews.
     */
    FILE* employeeFile = fopen("employees.txt", "w");
    Employee* admin = (Employee*)malloc(sizeof(Employee));
    if (admin == NULL) {
        fclose(employeeFile);
        return NULL; // Handle allocation error
    }

    strcpy(admin->username, "admin");
    strcpy(admin->firstName, "manager");
    strcpy(admin->password, "12345678");
    admin->level = 1;
    admin->next = NULL;

    // Create other necessary files.
    FILE* customerFile = fopen("customers.txt", "w");
    FILE* itemFile = fopen("items.bin", "wb");
    FILE* customerItemFile = fopen("items_of_customer.bin", "wb");
    FILE* logFile = fopen("logs.log", "w");
    FILE* reviewFile = fopen("reviews.txt", "w");

    fclose(customerFile);
    fclose(itemFile);
    fclose(employeeFile);
    fclose(customerItemFile);
    fclose(logFile);
    fclose(reviewFile);

    char logMessage[100];
    sprintf(logMessage, "Default admin user created: %s %s\n", admin->username, admin->firstName);
    AddLogEntry(logMessage);

    return admin;
}

Employee* AuthenticateEmployee(Employee* employeeList) {
    /* Handles employee login with 3 attempts.
     * Complexity: O(n), where n is the number of employees.
     */
    Employee* current = employeeList;
    char username[20];
    char password[10];
    char logMessage[100];

    for (int i = 0; i < 3; i++) {
        printf("Enter username: ");
        scanf("%19s", username);
        printf("Enter password: ");
        scanf("%9s", password);

        while (current != NULL) {
            if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0) {
                printf("Welcome, %s %s!\n", current->firstName, current->username);
                sprintf(logMessage, "Employee %s %s logged in.\n", current->username, current->firstName);
                AddLogEntry(logMessage);
                return current;
            }
            current = current->next;
        }

        current = employeeList;
        printf("Incorrect username or password.\n");
    }

    printf("Too many failed attempts.\n");
    sprintf(logMessage, "Unauthorized login attempt.\n");
    AddLogEntry(logMessage);
    return NULL;
}

void AddNewEmployee(Employee* employeeList) {
    /* Adds a new employee to the system.
     * Complexity: O(n), where n is the number of employees.
     */
    Employee* newEmployee = (Employee*)malloc(sizeof(Employee));
    char logMessage[100];

    printf("Enter employee details:\n");
    printf("Username: ");
    scanf("%s", newEmployee->username);
    printf("First Name: ");
    scanf("%s", newEmployee->firstName);
    printf("Password: ");
    scanf("%s", newEmployee->password);
    printf("Level (1-3): ");
    scanf("%d", &newEmployee->level);

    Employee* current = employeeList;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newEmployee;
    newEmployee->next = NULL;

    sprintf(logMessage, "New employee added: %s %s (Level %d)\n", newEmployee->username, newEmployee->firstName, newEmployee->level);
    AddLogEntry(logMessage);

    printf("Employee added successfully.\n");
    printf("Press any key to continue.\n");
    _getch();
}