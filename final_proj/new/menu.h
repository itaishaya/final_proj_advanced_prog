// Shani Sharon 212432967
// Itai Shaya 207033622

#pragma once

#include "item.h"
#include "employee.h"
#include "customer.h"

void DisplayMenu(unsigned int userLevel, Employee* employeeList, Item* itemList, Customer* customerList, CustomerItem* customerItemList, Review* reviewList);
int HandleMenuSelection(unsigned int userLevel, Employee* employeeList, Item* itemList, Customer* customerList, CustomerItem* customerItemList, Review* reviewList);
void StartSystem(Employee* employeeList);
void ShutdownSystem(Employee* employeeList, Item* itemList, Customer* customerList, CustomerItem* customerItemList, Review* reviewList);
void SaveCustomersToFile(Customer* customerList);
void SaveEmployeesToFile(Employee* employeeList);
void SaveItemsToFile(Item* itemList);
void SaveCustomerItemsToFile(CustomerItem* customerItemList);
void SaveReviewsToFile(Review* reviewList);
Customer* LoadCustomersFromFile();
Employee* LoadEmployeesFromFile();
Item* LoadItemsFromFile();
CustomerItem* LoadCustomerItemsFromFile();
Review* LoadReviewsFromFile();