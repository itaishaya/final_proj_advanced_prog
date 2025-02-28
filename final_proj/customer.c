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

void SearchCustomer(Customer* head)
{
	/* This function search for a customer according to ID requested by the user.
	* this function receives the head of the customer list, if customer found it prints the 
	* customer details. if not - it prints customer not found.
	* This function complexity is O(n) n - customers list length because this list is not sorted
	*/
	Customer* current = head->next;
	int id;
	bool found = false;
	char log_txt[100];
	printf("Enter ID of the customer you are looking for:");
	scanf("%d", &id);
	while (current != NULL)
	{
		if (id == current->id)
		{
			// found costumer with this ID
			found = true;
			PrintCustomerDetails(current);
			sprintf(log_txt, "Searched and found customer with ID:%d, printed customer's details\n", id);
			AddLog(log_txt);
			printf("Press any key to continue\n");
			_getch();
			return;
		}
		current = current->next;
	}
	if (!found)
	{
		printf("Costumer: %0d not found!", id);
		sprintf(log_txt, "Searched and not found customer with ID:%d\n", id);
		AddLog(log_txt);
	}
	printf("Press any key to continue\n");
	_getch();
}

void PrintCustomerDetails(Customer* current)
{
	/* This function prints the customer details
	*/
	printf("ID: %d\n", current->id);
	printf("First name: %s\n", current->first_name);
	printf("Last name: %s\n", current->last_name);
	char joinDateStr[11];
	strftime(joinDateStr, sizeof(joinDateStr), "%d/%m/%Y", localtime(&current->join_date));
	printf("Join date: %s\n", joinDateStr);
}

void AddCustomer(Customer* head)
{
	/* This function adds new customer to the costumers list.
	* It receives from the user the costumer details and insert it to the costumers list.
	* The costumer list is sorted according to the join date, it inserts the new customer according to it.
	* This function complexity is O(n) n - length of list. due to sorted insertion.
	*/
	time_t currentTime;
	bool added = false;
	Customer* new_customer = (Customer*)malloc(sizeof(Customer));
	printf("Please enter these parametrs:\n");
	printf("ID:\n");
	scanf("%d", &new_customer->id);
	while (new_customer->id < 100000000 || new_customer->id > 999999999)
	{
		printf("Please enter a 9 digit ID\n");
		scanf("%d", &new_customer->id);
	}
	printf("First name:\n");
	scanf("%s", &new_customer->first_name);
	printf("Last name:\n");
	scanf("%s", &new_customer->last_name);
	new_customer->join_date = time(&currentTime);
	Customer* current = head->next;
	Customer* prev = head;
	while (current != NULL)
	{
		if (difftime(new_customer->join_date, current->join_date) < 0) 
		{
			//new customer joined earlier from existing customer
			added = true;
			if (prev == NULL)
			{
				new_customer->next = current;
				head = new_customer;
				break;
			}
			prev->next = new_customer;
			new_customer->next = current;
			break;
		}
		prev = current;
		current = current->next;
	}
	if (!added)
	{
		// new customer joined last (or first to join)
		new_customer->next = NULL;
		prev->next = new_customer;
	}
	char log_txt[100];
	sprintf(log_txt, "Customer %s %s with ID %d was added\n", new_customer->first_name, new_customer->last_name, new_customer->id);
	AddLog(log_txt);
	printf("Customer added successfully\n");
	printf("press any key to continue\n");
	_getch();
}

void RemoveCustomer(Customer* head)
{
	/* This function removes a customer according to it's ID received from the user.
	* This function complexity is O(n) n - length of list, due to search in the list
	* If ID not found the program prints appropriate message.
	*/
	int id;
	printf("Enter the ID of the customer you want to remove: ");
	scanf("%d", &id);
	Customer* current = head->next;
	Customer* prev = head;

	while (current != NULL) {
		if (current->id == id) 
		{
			// Costumer found
			prev->next = current->next;
			printf("%s was removed\n", current->first_name);
			char log_txt[100];
			sprintf(log_txt, "Customer %s %s with ID %d was removed\n", current->first_name, current->last_name, current->id);
			AddLog(log_txt);
			free(current);
			printf("Press any key to continue\n");
			_getch();
			return;
		}
		prev = current;
		current = current->next;
	}
	printf("Customer with ID:%0d not found!\n", id);
}