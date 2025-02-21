// Shani Sharon *ID*
// Itai Shaya 207033622

#pragma once

#include "item.h"
#include "employee.h"
#include "customer.h"

void showMenu(unsigned int employeeLevel, Employee* employee_head, Item* item_head, Customer* customers_head, ItemsOfCustomer* items_of_customer_head, Review* review_head);
int chooseOption(unsigned int employeeLevel, Employee* employee_head, Item* item_head, Customer* customers_head, ItemsOfCustomer* items_of_customer_head, Review* review_head);
void run_system(Employee* employees);
void shutdown(Employee* employee_head, Item* item_head, Customer* customers_head, ItemsOfCustomer* items_of_customer_head, Review* review_head);
void ListCustomers2File(Customer* head);
void ListEmployees2File(Employee* head);
void ListItems2File(Item* head);
void ListItemsOfCustomer2File(ItemsOfCustomer* head);
void ListReviews2File(Review* head);
Customer* File2ListCustomers();
Employee* File2ListEmployees();
Item* File2ListItems();
ItemsOfCustomer* File2ListListItemsOfCustomer();
Review* File2ListReviews();