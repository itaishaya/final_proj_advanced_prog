// Shani Sharon 212432967
// Itai Shaya 207033622

#include "employee.h"
#include "menu.h"
#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS

int main()
{
    Employee* employee_head = NULL;
    if (!CheckEmployeeFileExists())
    {
        employee_head = CreateDefaultAdmin();
    }
    else {
        employee_head = LoadEmployeesFromFile(employee_head);
    }
    run_system(employee_head);
    return 0;
}