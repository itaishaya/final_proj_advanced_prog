// Shani Sharon *ID*
// Itai Shaya 207033622

#include "employee.h"
#include "menu.h"
#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS

int main()
{
    Employee* employee_head = NULL;
    if (!checkIfEmployeeFileExists())
    {
        employee_head = createDefaultAdmin();
    }
    else {
        employee_head = File2ListEmployees(employee_head);
    }
    run_system(employee_head);
    return 0;
}