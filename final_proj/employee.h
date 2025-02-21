// Shani Sharon *ID*
// Itai Shaya 207033622

#pragma once

typedef struct employee {
    char username[20];
    char firstname[10];
    char password[10];
    unsigned int level; // 1 - admin, 2 - employee, 3 - practicioner
    struct employee* next;
} Employee;

int checkIfEmployeeFileExists();
Employee* createDefaultAdmin();
Employee* login(Employee* head);
void AddNewEmployee(Employee* head);