#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX_NAME_LENGTH 50
#define FILENAME "stock.txt"

// Defines the structure for an item
struct Item {
    int item_id;
    char item_name[MAX_NAME_LENGTH];
    float price;
    int quantity;
};

// Defines the structure for customer
struct Customer {
    char name[MAX_NAME_LENGTH];
    struct Item items[MAX_ITEMS];
    int num_items;
    long long int phone;
};

void displayStock(struct Item stock[], int num_items) {
    printf("\nSupermarket Stock\n");
    printf("------------------------------\n");
    printf("ID\tName\t\tPrice\t\tQuantity\n");
    printf("------------------------------\n");
    for (int i = 0; i < num_items; i++) {
        printf("%d\t%s\t\t$%.2f\t\t%d\n", stock[i].item_id, stock[i].item_name, stock[i].price, stock[i].quantity);
    }
    printf("------------------------------\n");
}

// function to display the bill for a customer
void displayBill(struct Customer c, struct Item stock[], int num_items) {
    printf("\n\nSupermarket\n");
    printf("----------\n");
    printf("Customer Name: %s\n", c.name);
    printf("Phone Number: %lld\n", c.phone);
    printf("------------------------------\n");
    printf("ID\tName\t\tPrice\t\tQuantity\n");
    printf("------------------------------\n");
    float total_amount = 0;
    for (int i = 0; i < c.num_items; i++) {
        printf("%d\t%s\t\t$%.2f\t\t%d\n", c.items[i].item_id, c.items[i].item_name, c.items[i].price, c.items[i].quantity);
        total_amount += c.items[i].price * c.items[i].quantity; // Update total amount considering quantity
    }
    // (assuming gst=18%)
    float gst_amount = total_amount * 0.18;
    total_amount += gst_amount;

    printf("------------------------------\n");
    printf("Total Amount (incl. GST 18%%): $%.2f\n", total_amount);
    printf("------------------------------\n");
    printf("THANK YOU FOR VISITING!\n");
    printf("VISIT AGAIN!");
}

// Function to write stock data to a file
void writeStockToFile(struct Item stock[], int num_items) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < num_items; i++) {
        fprintf(file, "%d %s %.2f %d\n", stock[i].item_id, stock[i].item_name, stock[i].price, stock[i].quantity);
    }

    fclose(file);
}

// Function to read stock data from a file
int readStockFromFile(struct Item stock[]) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return 0;
    }

    int num_items = 0;
    while (fscanf(file, "%d %s %f %d", &stock[num_items].item_id, stock[num_items].item_name, &stock[num_items].price, &stock[num_items].quantity) != EOF) {
        num_items++;
    }

    fclose(file);
    return num_items;
}

int main() {
    printf("WELCOME TO SUPERMARKET\n");

    struct Item stock[MAX_ITEMS];
    int num_items = readStockFromFile(stock); // Read stock data from file

    if (num_items == 0) {
        printf("No stock data found.\n");
        return 1;
    }

    // Display the available stock
    displayStock(stock, num_items);

    struct Customer customer; // Declaring a variable of type 'Customer' to store customer details
    customer.num_items = 0; // Initializing the number of items as 0

    // Input customer name
    printf("Enter customer name: ");
    scanf("%s", customer.name);

    // Input phone number
    printf("Enter phone number: ");
    scanf("%lld", &customer.phone); // Use %lld ->long long int

    // Input total number of items
    printf("Enter the total number of items: ");
    scanf("%d", &customer.num_items);

    // Input details for each item
    for (int i = 0; i < customer.num_items; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("Enter item ID: ");
        scanf("%d", &customer.items[i].item_id);
        printf("Enter price: $");
        scanf("%f", &customer.items[i].price);
        printf("Enter quantity: ");
        scanf("%d", &customer.items[i].quantity);
        // Assuming item names are not necessary for bill generation as they are not requested again.
    }

    // Display the bill
    displayBill(customer, stock, num_items);

    // Write stock data back to file (assuming no changes to stock quantities)
    writeStockToFile(stock, num_items);

    return 0;
}

