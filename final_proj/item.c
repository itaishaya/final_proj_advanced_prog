// Shani Sharon *ID*
// Itai Shaya 207033622

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "menu.h"
#include "item.h"
#include "logs.h"
#include "customer.h"

void AddNewItem(Item* head)
{
	/* This function adds new item to the items list it receives the item properties from the user
	* it adds the item to the sorted list according to the ID (serial number)
	* this function complexity is O(n) n - length of the items list because of the insertion to the sorted list.
	*/
	char log_txt[100];
	Item* newItem = (Item*)malloc(sizeof(Item));
	printf("Please enter these parametrs:\n");
	printf("ID: ");
	scanf("%d", &newItem->id);
	printf("Item type: ");
	scanf("%s", &newItem->item_type);
	printf("Country made: ");
	scanf("%s", &newItem->country_made);
	printf("Price: ");
	scanf("%f", &newItem->price);
	printf("Manufacturing Date (DD/MM/YYYY): ");
	scanf("%s", &newItem->manufacturing_date);
	printf("Inventory: ");
	scanf("%d", &newItem->inventory);
	if (newItem->inventory > 0)
		newItem->inStock = true;
	else
		newItem->inStock = false;
	if (head == NULL)
	{
		head = newItem;
		newItem->next = NULL;
		sprintf(log_txt, "Item %s was added to the store list\n", newItem->item_type);
		AddLog(log_txt);
		printf("Item added successfully\n");
		printf("press any key to continue\n");
		_getch();
		return;
	}
	Item* current = head->next;
	Item* prev = head;

	while (current != NULL)
	{
		if (newItem->id < current->id)
		{
			//adding item in the middle of the list
			prev->next = newItem; 
			newItem->next = current;
			sprintf(log_txt, "Item %s was added to the store list\n", newItem->item_type);
			AddLog(log_txt);
			printf("Item added successfully\n");
			printf("press any key to continue\n");
			_getch();
			return;
		}
		prev = current;
		current = current->next;
	}
	//adding to the end of the list (or first item)
	newItem->next = NULL; 
	prev->next = newItem;
	sprintf(log_txt, "Item %s was added to the store list\n", newItem->item_type);
	AddLog(log_txt);
	printf("Item added successfully\n");
	printf("press any key to continue\n");
	_getch();
}

void printItemDetails(Item* item)
{
	/* This function prints the item properties
	*/
	printf("\nItem id: %d\n", item->id);
	printf("Item country made: %s\n", item->country_made);
	printf("Item type: %s\n", item->item_type);
	printf("Item price: %.2f\n", item->price);
	printf("Item date: %s\n", item->manufacturing_date);
	printf("Item inventory: %d\n\n", item->inventory);
}

int searchItem(Item* head) 
{
    /* This function searches item in the items list
    * It prints a menu for the search criterias.
    * This function complexity is O(n) n - length of the list.
    */
    int select;
    char item_type[20] = "", country_made[20] = "", manufacturing_date[11] = "";
    float price = 0;
    int inventory = 0;
    bool inStock = false;

    printf("Please select what you would like to search by:\n");
    printf("1- Item type\n");
    printf("2- Country made\n");
    printf("3- Item type and country made\n");
    printf("4- Price (more than)\n");
    printf("5- Inventory (more than)\n");
    printf("6- Manufacturing Date\n");
    printf("7- In stock\n");
    printf("8- Exit\n");
    scanf("%d", &select);

    if (select == 8)
    {
        return 0;
    }

    switch (select) 
    {
    case 1:
        printf("Enter item type: ");
        scanf("%s", item_type);
        break;
    case 2:
        printf("Enter country made: ");
        scanf("%s", country_made);
        break;
    case 3:
        printf("Enter item type: ");
        scanf("%s", item_type);
        printf("Enter country made: ");
        scanf("%s", country_made);
        break;
    case 4:
        printf("Enter minimum price: ");
        scanf("%f", &price);
        break;
    case 5:
        printf("Enter minimum inventory: ");
        scanf("%d", &inventory);
        break;
    case 6:
        printf("Enter manufacturing date (DD/MM/YYYY): ");
        scanf("%s", manufacturing_date);
        break;
    case 7:
        printf("Enter '1' for in stock, '0' for out of stock: ");
        int stockInput;
        scanf("%d", &stockInput);
        inStock = (stockInput == 1);
        break;
    default:
        printf("Invalid selection.\n");
        return 0;
    }

    Item* current = head->next;
    bool found = false;

    while (current != NULL) {
        switch (select) {
        case 1:
            if (strcmp(item_type, current->item_type) == 0) 
                found = true;
            break;
        case 2:
            if (strcmp(country_made, current->country_made) == 0) 
                found = true;
            break;
        case 3:
            if (strcmp(item_type, current->item_type) == 0 && strcmp(country_made, current->country_made) == 0) 
                found = true;
            break;
        case 4:
            if (price < current->price) 
                found = true;
            break;
        case 5:
            if (inventory < current->inventory) 
                found = true;
            break;
        case 6:
            if (strcmp(manufacturing_date, current->manufacturing_date) == 0) 
                found = true;
            break;
        case 7:
            if (current->inStock == inStock) 
                found = true;
            break;
        }

        if (found)
        {
            printItemDetails(current);
        }
        current = current->next;
    }

    if (!found)
    {
        printf("No matching items found.\n");
        printf("Press any key to continue\n");
        _getch();
        return 0;
    }
    printf("Press any key to continue\n");
    _getch();
    return 1;
}

void UpdateItem(Item* head)
{
	/* This function updates item according to ID received from a user
	* if ID does'nt exist in the items list, it prints an appropriate message
	* this function complexity is O(n) n - list length.
	*/
	char log_txt[100];
	int id;
	bool found = false;
	printf("Enter the id of the item you want to update:\n");
	scanf("%d", &id);
	Item* current = head->next;
	while (current != NULL)
	{
		if (current->id == id)
		{
			found = true;
			int select;
			printf("Please select what field would you like to update:\n");
			printf("1- Item type\n");
			printf("2- Country made\n");
			printf("3- Price\n");
			printf("4- Inventory\n");
			printf("5- Manufacturing Date\n");
			printf("6- Exit\n");
			scanf("%d", &select);
			switch (select)
			{
			case 1:
				printf("Enter new item type:\n");
				scanf("%s", &current->item_type);
				sprintf(log_txt, "The item type of item ID %d was updated to %s\n", current->id, current->item_type);
				AddLog(log_txt);
				break;
			case 2:
				printf("Enter new country made:\n");
				scanf("%s", &current->country_made);
				sprintf(log_txt, "The county made item ID %d was updated to %s\n", current->id, current->country_made);
				AddLog(log_txt);
				break;
			case 3:
				printf("Enter new price:\n");
				scanf("%f", &current->price);
				sprintf(log_txt, "The price of item ID %d was updated to %.2f\n", current->id, current->price);
				AddLog(log_txt);
				break;
			case 4:
				printf("Enter new inventory:\n");
				scanf("%d", &current->inventory);
				if (current->inventory > 0)
				{
					current->inStock = true;
					sprintf(log_txt, "The inventory of item ID %d was updated to %d\n", current->id, current->inventory);
					AddLog(log_txt);
				}
				else
				{
					current->inStock = false;
					sprintf(log_txt, "Item ID %d is out of stock\n", current->id);
					AddLog(log_txt);
				}
				break;
			case 5:
				printf("Enter new manufacturing date:\n");
				scanf("%s", &current->manufacturing_date);
				sprintf(log_txt, "The manufacturing date of item ID %d was updated to %s\n", current->id, current->manufacturing_date);
				AddLog(log_txt);
				scanf("%s", &current->manufacturing_date);
				break;
			case 6:
				return;
			default:
				printf("option do not exist, try again\n");
				return;
			}
		}
		current = current->next;
	}
	if (!found)
	{
		printf("item with ID:%d not found!");
		sprintf(log_txt,  "Item with ID %d was not found \n", id);
		AddLog(log_txt);
	}
	printf("press any key to continue\n");
	_getch();
}

void RemoveItem(Item* head) 
{
	/* This function removes an item from the list based on the ID provided by the user.
	* If the ID does not exist in the list, it prints an appropriate message.
	* This function complexity is O(n) n - items list length
	*/
	char log_txt[100];
	int id;

	printf("Enter the ID of the item to remove:\n");
	scanf("%d", &id);

	Item* current = head->next, * prev = head;
	bool found = false;

	while (current) {
		if (current->id == id) 
		{
			prev->next = current->next;
			sprintf(log_txt, "%s was removed from the store list\n", current->item_type);
			AddLog(log_txt);
			free(current);
			printf("Item removed successfully.\n");
			printf("Press any key to continue\n");
			_getch();
			return;
		}
		prev = current;
		current = current->next;
	}
	printf("Item with ID %d not found!" ,id);
	sprintf(log_txt, "Item with ID:%d was seareched to remove but not found\n", id);
	AddLog(log_txt);
	printf("Press any key to continue\n");
	_getch();
}

void SellItem(Item* items_head, ItemsOfCustomer* items_of_customer_head) 
{
	/* This function processes the sale of an item to a customer.
	 * It verifies the item ID, stock availability, and purchase constraints.
	 * If the item is available and within the allowed purchase limits, it deducts the stock
	 * and records the transaction.
	 * If the item does not exist or the purchase is invalid, an appropriate message is printed.
	 * This function complexity is O(n), where n is the length of the item list.
	 */
	char log_txt[100];
	int item_id, customer_id, count, credit_card;
	bool found = false;
	printf("Enter the id of the customer that wants to buy:\n");
	scanf("%d", &customer_id);
	printf("Enter the id of the item that the customer wants to buy:\n");
	scanf("%d", &item_id);
	printf("Enter the count of the item you want to buy:\n");
	scanf("%d", &count);

	if (count > 3) 
	{
		printf("You're allowed to buy only 3 items\n");
		printf("press any key to continue\n");
		_getch();
		return;
	}

	// Find the item
	Item* current_item = items_head->next;
	while (current_item != NULL && !found)
	{
		if (current_item->id == item_id)
		{
			found = true;
		}
		else 
		{
			current_item = current_item->next;
		}
	}

	if (!found) {
		printf("Item not found!\n");
		sprintf(log_txt, "Costumer with ID:%d tried tou buy:%d item(s) with ID %d but the item not found\n", customer_id, count, item_id);
		AddLog(log_txt);
		printf("press any key to continue\n");
		_getch();
		return;
	}

	if (!current_item->inStock || count > current_item->inventory) {
		printf("We only have %d items, you can try again\n", current_item->inventory);
		sprintf(log_txt, "Costumer with ID:%d tried tou buy:%d item(s) with ID %d but there was only %d items\n", customer_id, count, item_id, current_item->inventory);
		AddLog(log_txt);
		printf("press any key to continue\n");
		_getch();
		return;
	}

	printf("You need to pay now, enter your credit card number\n");
	scanf("%d", &credit_card);

	// Update inventory
	current_item->inventory -= count;
	current_item->inStock = (current_item->inventory > 0);

	printf("Item sold successfully!\n");

	// Create new purchase record
	ItemsOfCustomer* newItemsOfCustomer = (ItemsOfCustomer*)malloc(sizeof(ItemsOfCustomer));
	newItemsOfCustomer->customer_id = customer_id;
	newItemsOfCustomer->item_id = item_id;
	newItemsOfCustomer->item_quantity = count;
	newItemsOfCustomer->item_price = current_item->price;
	newItemsOfCustomer->purchase_date = time(NULL);
	newItemsOfCustomer->next = NULL;

	// Insert in sorted order by item ID
	ItemsOfCustomer* prev = items_of_customer_head;
	ItemsOfCustomer* current = items_of_customer_head->next;

	while (current && current->item_id < item_id) {
		prev = current;
		current = current->next;
	}

	newItemsOfCustomer->next = current;
	prev->next = newItemsOfCustomer;

	sprintf(log_txt, "%d item(s) with ID %d was sold to customer with ID %d\n", count, item_id, customer_id);
	AddLog(log_txt);

	printf("press any key to continue\n");
	_getch();
}

void PurchasedItemsByCustomer(ItemsOfCustomer* items_of_customer_head)
{
	/* This function displays all purchased items by a specific customer.
	 * It searches for purchases matching the given customer ID and prints details.
	 * If no purchases are found, no output is shown.
	 * Complexity: O(n), n - the number of purchases by customer.
	 */
	int customer_id;
	printf("Enter the id of the customer that you want to see his purchases:\n");
	scanf("%d", &customer_id);

	ItemsOfCustomer* current = items_of_customer_head->next;
	while (current != NULL) 
	{
		if (current->customer_id == customer_id) 
		{
			char purchaseDateStr[11];
			strftime(purchaseDateStr, sizeof(purchaseDateStr), "%d/%m/%Y", localtime(&current->purchase_date));
			printf("Customer ID: %d, Item ID: %d, Qty: %d, Price: %.2f, Date: %s\n", current->customer_id, current->item_id, current->item_quantity, current->item_price, purchaseDateStr);
		}
		current = current->next;
	}
	printf("press any key to continue\n");
	_getch();
}

void ShowProfit(ItemsOfCustomer* items_of_customer_head) 
{
	/* This function calculates and displays the total profit and item sales.
	 * It goes over all purchases and accumulates revenue.
	 * Complexity: O(n), n - number of purchases of customer.
	 */
	float profit = 0;
	int quantity = 0;
	ItemsOfCustomer* current = items_of_customer_head->next;
	while (current != NULL) 
	{
		profit += (current->item_price) * (current->item_quantity);
		quantity += current->item_quantity;
		current = current->next;
	}
	printf("\nTotal profit: %.2f\nItems sold: %d\n", profit, quantity);
	printf("press any key to continue\n");
	_getch();
}

void AddCustomerReview(Review* review_head) 
{
	/* This function adds a customer review for a specific item.
	 * It ensures valid input for review scores (1-10) and inserts it in sorted order.
	 * Complexity: O(n), n - number of reviews
	 */
	Review* newReview = (Review*)malloc(sizeof(Review));
	printf("Enter Item ID:\n");
	scanf("%d", &newReview->item_id);
	printf("Enter Item Type:\n");
	scanf("%s", newReview->item_type);
	printf("Enter Review (1-10):\n");
	scanf("%d", &newReview->customer_review);
	while (newReview->customer_review < 1 || newReview->customer_review > 10) 
	{
		printf("Invalid number, try again\n");
		scanf("%d", &newReview->customer_review);
	}
	Review* prev = review_head;
	Review* current = review_head->next;
	while (current != NULL && current->item_id < newReview->item_id) 
	{
		prev = current;
		current = current->next;
	}
	newReview->next = current;
	prev->next = newReview;

	printf("Review added successfully\n");
	char log_txt[100];
	sprintf(log_txt, "Review for %s (ID: %d) added.\n", newReview->item_type, newReview->item_id);
	AddLog(log_txt);
	printf("press any key to continue\n");
	_getch();
}

void GetReviewsBySpecificItem(Review* review_head) 
{
	/* This function retrieves all reviews for a specific item ID
	 * It searches through the review list and displays matching reviews
	 * Complexity: O(n),  n - number of reviews
	 */
	int item_id, counter = 0;
	printf("Enter the item ID to see reviews:\n");
	scanf("%d", &item_id);
	printf("Reviews for item ID %d:\n", item_id);

	Review* current = review_head->next;
	while (current != NULL) 
	{
		if (current->item_id == item_id) 
		{
			printf("%d ", current->customer_review);
			counter++;
		}
		current = current->next;
	}
	if(counter==0)
	{ 
		printf("No reviews for this item\n");
	}
	printf("press any key to continue\n");
	_getch();
}

void ReturnItem(Item* items_head, ItemsOfCustomer* items_of_customer_head) 
{
	/* This function handles item returns if within the 15-day return period.
	 * It updates the inventory and removes purchases as necessary
	 * Complexity: O(n), where n - number of purchases of customer
	 */
	char log_txt[100];
	int customer_id, item_id, return_qty, available_qty = 0;
	time_t currentTime = time(NULL);

	printf("Enter Customer ID:\n");
	scanf("%d", &customer_id);
	printf("Enter Item ID:\n");
	scanf("%d", &item_id);
	printf("Enter Quantity to Return:\n");
	scanf("%d", &return_qty);

	ItemsOfCustomer* current = items_of_customer_head->next;
	while (current != NULL) 
	{
		if (difftime(currentTime, current->purchase_date) / (60 * 60 * 24) < 15 &&
			current->customer_id == customer_id && current->item_id == item_id) 
		{
			available_qty += current->item_quantity;
		}
		current = current->next;
	}

	if (available_qty == 0) 
	{
		printf("Return not possible, conditions not met\n");
	}
	else if (available_qty < return_qty) 
	{
		printf("Can only return %d items, try again\n", available_qty);
		ReturnItem(items_head, items_of_customer_head);
	}
	else 
	{
		ItemsOfCustomer* prev = items_of_customer_head, * curr = items_of_customer_head->next;
		int temp_qty = return_qty;
		while (curr != NULL) 
		{
			if (difftime(currentTime, curr->purchase_date) / (60 * 60 * 24) < 15 &&
				curr->customer_id == customer_id && curr->item_id == item_id) {
				if (temp_qty <= curr->item_quantity) {
					curr->item_quantity -= temp_qty;
					UpdateReturningInItemList(items_head, curr, temp_qty);
					printf("Return successful\n");
					sprintf(log_txt, "Customer %d returned %d of item %d\n", customer_id, return_qty, item_id);
					AddLog(log_txt);
					break;
				}
				temp_qty -= curr->item_quantity;
				prev->next = curr->next;
				UpdateReturningInItemList(items_head, curr, curr->item_quantity);
			}
			prev = curr;
			curr = curr->next;
		}
	}
	printf("press any key to continue\n");
	_getch();
}

void UpdateReturningInItemList(Item* items_head, ItemsOfCustomer* returned_item, int qty) 
{
	/* This function updates the item list after a return.
	 * It restores the inventory and sets inStock status accordingly
	 * Complexity: O(n), where n - length of items list
	 */
	Item* current = items_head->next;
	while (current != NULL) 
	{
		if (current->id == returned_item->item_id) 
		{
			current->inventory += qty;
			current->inStock = true;
			break;
		}
		current = current->next;
	}
}
