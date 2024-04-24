#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX_NAME_LENGTH 50

// Defines the structure for an item
struct Item {
    int item_id;
    char *item_name;
    float price;
    int quantity;
};

// Defines the structure for customer
struct Customer {
    char *name;
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

    // Display of stock
}
int main() {
    printf("WELCOME TO SUPERMARKET\n");
    // Sample stock data
    struct Item stock[] = {
        {101,"Yogurt          ", 100, 100},
        {102,"Milk            ", 25, 1},
        {103,"Curd            ", 10, 1},
        {104,"panner          ",100,150},
        {105,"butter          ",90,150},
        /*fruits 0-6*/
        {106,"apple           ",150,3},
        {107,"banana          ",200,5},
        {108,"pineapple       ",30,1},
        {109,"strawberry      ",250,3},
        {110,"mango           ",156,3},
        /*vegetables 0-6*/
        {111,"Beans           ",150,3},
        {112,"Carrot          ",200,5},
        {113,"Tomato          ",30,5},
        {114,"Onion           ",250,3},
        {115,"potato          ",156,2},
        {116,"ginger          ",20,1},
        /*toiletry*/
        {117,"toothbrush      ",120,3},
        {118,"toothpaste      ",211,3},
        {119,"soap            ",50,5},
        {120,"shampoo         ",280,3},
        {121,"lotion          ",100,2},
        /*non perishable*/
        {122,"oil             ",150,1},
        {123,"Atta            ",150,2},
        {124,"Moong daal      ",30,3},
        {125,"Rice            ",250,5},
        {126,"Idli dosa batter",156,3},
       
    };


    int num_items = sizeof(stock) / sizeof(stock[0]); // Calculate the number of items in the stock

    // Display the available stock
    displayStock(stock, num_items);

    struct Customer customer; // Declaring a variable of type 'Customer' to store customer details
    customer.num_items = 0; // Initializing the number of items as 0

    // Input customer name
    printf("Enter customer name: ");
    customer.name = malloc(MAX_NAME_LENGTH * sizeof(char)); // memory allocation
    if (customer.name == NULL) {
        printf("Memory allocation failed.\n");
        return 1; // Exit with failure
    }
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
        printf("Enter item name: ");
        customer.items[i].item_name = malloc(MAX_NAME_LENGTH * sizeof(char)); // Allocate memory for item name
        if (customer.items[i].item_name == NULL) {
            printf("Memory allocation failed.\n");
            return 1; // Exit with failure
        }
        scanf("%s", customer.items[i].item_name); 
        printf("Enter price: $");
        scanf("%f", &customer.items[i].price);
        printf("Enter quantity: ");
        scanf("%d", &customer.items[i].quantity); 
    }

    // Display the bill
    displayBill(customer, stock, num_items);

    // Free dynamically allocated memory for customer name and item names
    free(customer.name);
    for (int i = 0; i < customer.num_items; i++) {
        free(customer.items[i].item_name);
    }

    return 0;
}
