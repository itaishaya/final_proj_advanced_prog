// Shani Sharon *ID*
// Itai Shaya 207033622

#include <stdio.h>
#include <stdlib.h>
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
    int option,check;
    check = scanf("%d", &option);
    while (check != 1)
    {
        printf("Invalid option. Try again\n");
        while (getchar() != '\n');
        check = scanf("%d", &option);
    }

    switch (option) {
    case 1:
        searchItem(item_head);
        break;
    case 2:
        AddNewItem(&item_head);
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
            GetReviewsBySpecificItem(review_head);
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
            GetReviewsBySpecificItem(review_head);
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

void run_system(Employee* employee_head)
{
    /* This function initializes the program. It reads data from files and starts the menu function
    * This functions comlexity is linear due to reads of files and login function (assume O(n))
    * When this function stops and the showMenu function ends, it closes the program and saves the 
    * lists to files using shutdown_system function
    */
    Item* item_head = File2ListItems();
    Customer* customers_head = File2ListCustomers();
    ItemsOfCustomer* items_of_customer_head = File2ListItemsOfCustomer();
    Review* review_head = File2ListReviews();
    Employee* currentEmployee = login(employee_head);

    if (currentEmployee == NULL)
    {
        printf("Login failed\n");
        shutdown_system(employee_head, item_head, customers_head, items_of_customer_head, review_head);
        return;
    }
    showMenu(currentEmployee->level, employee_head, item_head, customers_head, items_of_customer_head, review_head);
    shutdown_system(employee_head, item_head, customers_head, items_of_customer_head, review_head);
}

void shutdown_system(Employee* employee_head, Item* item_head, Customer* customers_head, ItemsOfCustomer* items_of_customer_head, Review* review_head)
{
    /* This function copies all Lists containing data to files to close the program properly
    * This function complexity is linear due to the list read and file write
    */
    ListCustomers2File(customers_head);
    ListEmployees2File(employee_head);
    ListItems2File(item_head);
    ListItemsOfCustomer2File(items_of_customer_head);
    ListReviews2File(review_head);
}

void ListCustomers2File(Customer* head)
{
    /* This function copies all customers in the list to a customer text file
    * This function complexity is O(n) n - length of customers file
    */
    FILE* file = fopen("customers.txt", "w");
    Customer* current = head->next;
    while (current != NULL)
    {
        char joinDateStr[11];
        strftime(joinDateStr, sizeof(joinDateStr), "%d/%m/%Y", localtime(&current->join_date));

        fprintf(file, "%d\t%s\t%s\t%s\n", current->id, current->first_name, current->last_name, joinDateStr);
        current = current->next;
    }
    fclose(file);
}

void ListEmployees2File(Employee* head)
{
    /* This function copies all employees in the list to a employees text file
    * This function complexity is O(n) n - length of employees list
    */
    FILE* file = fopen("employees.txt", "w");
    Employee* current = head;
    while (current != NULL)
    {
        fprintf(file, "%s\t%s\t%s\t%d\n", current->username, current->firstname, current->password, current->level);
        current = current->next;
    }
    fclose(file);
}

void ListItems2File(Item* head)
{
    /* This function copies all items in the list to a items binary file
    * This function complexity is O(n) n - length of items list
    */
    FILE* file = fopen("items.bin", "wb");
    if (head == NULL)
    {
        fclose(file);
        return;
    }
    Item* current = head;
    while (current != NULL)
    {
        fwrite(current, sizeof(Item), 1, file);
        current = current->next;
    }
    fclose(file);
}

void ListItemsOfCustomer2File(ItemsOfCustomer* head)
{
    /* This function copies all items of customer in the list to a binary file
    * This function complexity is O(n) n - length of list
    */
    FILE* file = fopen("items_of_customer.bin", "wb");
    ItemsOfCustomer* current = head->next;
    while (current != NULL)
    {
        fwrite(current, sizeof(ItemsOfCustomer), 1, file);
        current = current->next;
    }
    fclose(file);
}

void ListReviews2File(Review* head)
{
    /* This function copies all reviews of customers in the reviews list to a file
    * This function complexity is O(n) n - length of list
    */
    FILE* file = fopen("reviews.txt", "w");
    Review* current = head->next;
    while (current != NULL)
    {
        fprintf(file, "%d\t%s\t%d\n", current->item_id, current->item_type, current->customer_review);
        current = current->next;
    }
    fclose(file);
}


Customer* File2ListCustomers()
{
    /* This function copies the customers from the file to a customers list
    * This function complexity is O(n) n - length of customers list
    */
    Customer* new_customer = NULL;
    Customer* head = (Customer*)malloc(sizeof(Customer));
    head->id = 0;
    head->next = NULL;
    Customer* current = head;
    FILE* file = fopen("customers.txt", "r");
    if (file == NULL)
    {
        return head;
    }
    char join_date_str[11];
    while (!feof(file))
    {
        new_customer = (Customer*)malloc(sizeof(Customer));
        if (fscanf(file, "%d\t%s\t%s\t%s\n", &new_customer->id, &new_customer->first_name, &new_customer->last_name, &join_date_str) != EOF) {
            new_customer->join_date = convertStringToTime(join_date_str);
            new_customer->next = NULL;
            current->next = new_customer;
            current = new_customer;
        }
    }
    free(new_customer);
    fclose(file);
    return head;
}

Employee* File2ListEmployees()
{
    /* This function creates an employees list from an employees file
    * This function complexity is O(n) n - length of employees list
    */
    FILE* file = fopen("employees.txt", "r");
    Employee* new_employee = NULL;
    Employee* head = (Employee*)malloc(sizeof(Employee));
    Employee* current = head;
    head->next = NULL;
    fscanf(file, "%s\t%s\t%s\t%d\n", &head->username, &head->firstname, &head->password, &head->level);
    while (!feof(file))
    {
        new_employee = (Employee*)malloc(sizeof(Employee));
        fscanf(file, "%s\t%s\t%s\t%d\n", &new_employee->username, &new_employee->firstname, &new_employee->password, &new_employee->level);
        new_employee->next = NULL;
        current->next = new_employee;
        current = new_employee;
    }
    free(new_employee);
    fclose(file);
    return head;
}

//Item* File2ListItems()
//{
//    /* This function copies data from items file to a list of items
//    * This function complexity is O(n) n - length of items list
//    */
//    Item* head = (Item*)malloc(sizeof(Item));
//    head->id = 0;
//    head->next = NULL;
//    Item* current = head;
//    FILE* file = fopen("items.bin", "rb");
//    Item* new_item = NULL;
//    if (file == NULL)
//    {
//        return current;
//    }
//    while (new_item = (Item*)malloc(sizeof(Item)) && fread(new_item, sizeof(Item), 1, file) == 1)
//    {
//        new_item->next = NULL;
//        current->next = new_item;
//        current = new_item;
//    }
//    free(new_item);
//    fclose(file);
//    return head;
//}

Item* File2ListItems()
{
    FILE* file = fopen("items.bin", "rb");
    if (file == NULL)
    {
        return NULL; // Return NULL if the file cannot be opened
    }

    Item* head = NULL;
    Item* current = NULL;

    Item temp;
    while (fread(&temp, sizeof(Item), 1, file) == 1)
    {
        Item* newItem = (Item*)malloc(sizeof(Item));
        if (newItem == NULL)
        {
            fclose(file);
            return head; // Return what we have so far in case of allocation failure
        }
        *newItem = temp; // Copy the read data
        newItem->next = NULL;

        if (head == NULL)
        {
            head = newItem;
            current = newItem;
        }
        else
        {
            current->next = newItem;
            current = newItem;
        }
    }

    fclose(file);
    return head;
}



ItemsOfCustomer* File2ListItemsOfCustomer()
{
    /* This function copies data from items of customer binary file to a items of customer list
    * This function complexity is O(n) n - length of items of customer list
    */
    ItemsOfCustomer* head = (ItemsOfCustomer*)malloc(sizeof(ItemsOfCustomer));
    head->customer_id = 0;
    head->next = NULL;
    ItemsOfCustomer* current = head;
    FILE* file = fopen("items_of_customer.bin", "rb");
    if (file == NULL)
    {
        return head;
    }
    ItemsOfCustomer* new_item_of_customer = NULL;
    while ((new_item_of_customer = (ItemsOfCustomer*)malloc(sizeof(ItemsOfCustomer))) && fread(new_item_of_customer, sizeof(ItemsOfCustomer), 1, file))
    {
        new_item_of_customer->next = NULL;
        current->next = new_item_of_customer;
        current = new_item_of_customer;
    }
    free(new_item_of_customer);
    fclose(file);
    return head;
}

Review* File2ListReviews()
{
    /* This function copies reviews file to a reviews list
    * This function complexity is O(n) n - length of reviews list
    */
    Review* head = (Review*)malloc(sizeof(Review));
    head->item_id = 0;
    head->next = NULL;
    Review* current = head;
    FILE* file = fopen("reviews.txt", "r");
    Review* new_review = NULL;
    if (file == NULL)
    {
        return current;
    }
    while (!feof(file))
    {
        new_review = (Review*)malloc(sizeof(Review));
        if (fscanf(file, "%d\t%s\t%d\n", &new_review->item_id, &new_review->item_type, &new_review->customer_review) != EOF) {
            new_review->next = NULL;
            current->next = new_review;
            current = new_review;
        }
    }
    fclose(file);
    return head;
}