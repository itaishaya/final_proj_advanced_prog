// Shani Sharon *ID*
// Itai Shaya 207033622

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "employee.h"
#include "logs.h"

int checkIfEmployeeFileExists()
{
    // First function required - check if employees file exists
    // This function returns 0 if file does'nt exist and returns 1 if it does
    FILE* file = fopen("employees.txt", "r");
    if (file == NULL)
    {
        return 0;
    }
    fclose(file);
    return 1;
}

Employee* createDefaultAdmin()
{
	/* Second required function for creation of default admnin for program
	* On startup, the program looking for the employees.txt file. 
	* if it does'nt exist, the program will create this file with default admin properties.
	* username:admin, firstname:manager, password:12345678, admin level is 1 and employee list will contain 1 element
	* this function also creates the customers file, items file, 
	*/
	FILE* employees_file = fopen("employees.txt", "w");
	Employee* new_employee = (Employee*)malloc(sizeof(Employee));
	strcpy(new_employee->username, "admin");
	strcpy(new_employee->firstname, "manager");
	strcpy(new_employee->password, "12345678");
	new_employee->level = 1;
	new_employee->next = NULL;
	FILE* customers_file = fopen("customers.txt", "w");
	FILE* items_file = fopen("items.bin", "wb");
	FILE* items_of_customer_file = fopen("items_of_customer.bin", "wb");
	FILE* log_file = fopen("logs.log", "w");
	FILE* reviews_file = fopen("reviews.txt", "w");
	fclose(customers_file);
	fclose(items_file);
	fclose(employees_file);
	fclose(items_of_customer_file);
	fclose(log_file);
	fclose(reviews_file);
	char log[100];
	sprintf(log, "%s %s created a default admin user\n", new_employee->username, new_employee->firstname);
	AddLog(log_file);
	return new_employee;
}

Employee* login(Employee* head)
{
	/* This function performs the login of an employee.
	* On each login every employee has 3 tries to sign in.
	* The function searches each time for the employee in the employees list.
	* This function comlexity is O(n), n - number of employees
	*/
	Employee* current = head;
	char username[20];
	char password[10];
	char log_txt[100];

	for (int i = 0; i < 3; i++)
	{
		printf("Enter username: \n");
		scanf("%19s", username);
		username[19] = '\0';

		printf("Enter password: \n");
		scanf("%9s", password);
		password[9] = '\0';

		while (current != NULL) {
			if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0)
			{
				// employee is found
				printf("Welcome %s %s\n", current->firstname, current->username);
				sprintf(log_txt, "employee %s %s logged in\n", current->username, current->firstname);
				AddLog(log_txt);
				return current;
			}
			current = current->next;
		}
		current = head;
		printf("Incorrect username or password!\n");
	}
	// employee not found
	printf("Too many attempts!\n");
	sprintf(log_txt, "unauthorized user tried to login\n");
	AddLog(log_txt);
	return NULL;
}

void AddNewEmployee(Employee* head)
{
	/* This function adds new employee to the system.
	It adds new employee in the end of the employees list
	*/
	Employee* new_employee = (Employee*)malloc(sizeof(Employee));
	char log_txt[100];
	printf("Please enter employee properties:\n");
	printf("Username:\n");
	scanf("%s", &new_employee->username);
	printf("First name:\n");
	scanf("%s", &new_employee->firstname);
	printf("Password:\n");
	scanf("%s", &new_employee->password);
	printf("Level:\n");
	scanf("%d", &new_employee->level);
	Employee* current = head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new_employee;
	new_employee->next = NULL;
	sprintf(log_txt, "the employee: %s %s created as new employee with level %d\n", new_employee->username, new_employee->firstname, new_employee->level);
	AddLog(log_txt);
	printf("press any key to continue\n");
	_getch();
}