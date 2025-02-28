#pragma once

typedef struct employee {
    char username[20];
    char firstName[10];
    char password[10];
    unsigned int level; // 1 - admin, 2 - employee, 3 - practicioner
    struct employee* next;
} Employee;

int CheckEmployeeFileExists();
Employee* CreateDefaultAdmin();
Employee* AuthenticateEmployee(Employee* employeeList);
void AddNewEmployee(Employee* employeeList);