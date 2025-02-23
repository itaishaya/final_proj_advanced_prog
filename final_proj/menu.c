// Shani Sharon *ID*
// Itai Shaya 207033622

#include <stdio.h>
#include "menu.h"
#include "item.h"
#include "employee.h"
#include "customer.h"
#include "utils.h"

void showMenu(unsigned int level, Employee* employee_head, Item* item_head, Customer* customers_head, ItemsOfCustomer* items_of_customer_head, Review* review_head)
{
    /* This function displays a menu to the user, it receives an employee level as input
    * to present the correct menu to the user with appropriate selections.
    * if level is not valid - it prints appropriate message and asking for the level again.
    */
    printf("\nWelcome to the shoes shop!\n\n");
    switch (level) {
    case 1: //Admin
        printf("Hi Admin, please choose an option:\n");
        printf("1 - Search an item\n");
        printf("2 - Add a new item\n");
        printf("3 - Remove an item\n");
        printf("4 - Search a costumer\n");
        printf("5 - Add a new customer\n");
        printf("6 - Remove a customer\n");
        printf("7 - Update shoe details\n");
        printf("8 - Sell an item\n");
        printf("9 - Display sales per customer\n");
        printf("10 - Return an item to the shop\n");
        printf("11 - Show profit\n");
        printf("12 - Get customer review for an item\n");
        printf("13 - Add customer review for an item\n");
        printf("14 - Add a new employee\n");
        printf("15 - Exit\n");
        chooseOption(level, employee_head, item_head, customers_head, items_of_customer_head, review_head);
        break;
    case 2: //Employee
        printf("Hi Employee, choose one option:\n");
        printf("1 - Search an item\n");
        printf("2 - Add a new item\n");
        printf("3 - Remove an item\n");
        printf("4 - Search a costumer\n");
        printf("5 - Add a new customer\n");
        printf("6 - Remove a customer\n");
        printf("7 - Update shoe details\n");
        printf("8 - Sell an item\n");
        printf("9 - Display sales per customer\n");
        printf("10 - Return an item to the shop\n");
        printf("11 - Show profit\n");
        printf("12 - Get customer review for an item\n");
        printf("13 - Add customer review for an item\n");
        printf("14 - Exit\n");
        chooseOption(level, employee_head, item_head, customers_head, items_of_customer_head, review_head);
        break;
    case 3: //Practicioner
        printf("Hi Practicioner, choose one option:n");
        printf("1 - Search an item\n");
        printf("2 - Add a new item\n");
        printf("3 - Search a costumer\n");
        printf("4 - Add a new customer\n");
        printf("5 - Display sales per customer\n");
        printf("6 - Return an item to the shop\n");
        printf("7 - Show profit\n");
        printf("8 - Get customer review for an item\n");
        printf("9 - Add customer review for an item\n");
        printf("10 - Exit\n");
        chooseOption(level, employee_head, item_head, customers_head, items_of_customer_head, review_head);
        break;
    default:
        printf("Invalid employee level, please enter employee level again 1-3\n");
        scanf("%d", &level);
        showMenu(level, employee_head, item_head, customers_head, items_of_customer_head, review_head);
    }
    return;
}

int chooseOption(unsigned int level, Employee* employee_head, Item* item_head, Customer* customers_head, ItemsOfCustomer* items_of_customer_head, Review* review_head) 
{
    /* This function let the user to choose option and does the appropriate task
    * It also contains a input check functionality
    */
    int option;
    scanf("%d", &option);
    while (option < 1 || option > 3 ) 
    {
        printf("Invalid option. Try again\n");
        while (getchar() != '\n');
        scanf("%d", &option);
    }

    switch (option) {
    case 1:
        searchItem(item_head);
        break;
    case 2:
        AddNewItem(item_head);
        break;
    case 3:
        if (level < 3) 
            RemoveItem(item_head);
        else
            SearchCustomer(customers_head);
        break;
    case 4:
        if (level < 3)
            SearchCustomer(customers_head);
        else
            AddCustomer(customers_head);
        break;
    case 5:
        if (level < 3)
            AddCustomer(customers_head);
        else
            PurchasedItemsByCustomer(items_of_customer_head);
        break;
    case 6:
        if (level < 3) 
            RemoveCustomer(customers_head);
        else 
            ReturnItem(item_head, items_of_customer_head);
        break;
    case 7:
        if (level < 3) 
            UpdateItem(item_head);
        else 
            ShowProfit(items_of_customer_head);
        break;
    case 8:
        if (level < 3) 
            SellItem(item_head, items_of_customer_head);
        else 
            GetRreviewsBySpecificItem(review_head);
        break;
    case 9:
        if (level < 3) 
            PurchasedItemsByCustomer(items_of_customer_head);
        else 
            AddCustomerReview(review_head);
        break;
    case 10:
        if (level < 3)
            ReturnItem(item_head, items_of_customer_head);
        else 
            return;
        break;
    case 11:
        if (level < 3) 
            ShowProfit(items_of_customer_head);
        break;
    case 12:
        if (level < 3) 
            GetRreviewsBySpecificItem(review_head);
        break;
    case 13:
        if (level < 3) 
            AddCustomerReview(review_head);
        break;
    case 14:
        if (level == 1) 
            AddNewEmployee(employee_head);
        else 
            return;
        break;
    case 15:
        if (level == 1) 
            return;
        break;
    default:
        printf("Invalid option. Try again.\n");
        chooseOption(level, employee_head, item_head, customers_head, items_of_customer_head, review_head);
        return;
    }
    showMenu(level, employee_head, item_head, customers_head, items_of_customer_head, review_head);
}


