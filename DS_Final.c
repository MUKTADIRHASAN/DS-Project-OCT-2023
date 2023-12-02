#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

struct Item {
    char name[50];
    float rating;
    float price;
    int item_Id_No;
    struct Item* next;
    struct Item* prev;
};

int cust_id = 1;
struct Item* head;
struct Item* last;
int Today_Customer = 0;
float total_income = 0;

struct order_list {
    int Customer_ID;
    int items[10][2];
    float amount;
    char date[11];
    struct order_list* next;
    struct order_list* prev;
};

struct order_list* head1;
struct order_list* last1;

struct Item* getnewNode(char a[], float p, int fin) {
    struct Item* temp = (struct Item*)malloc(sizeof(struct Item));
    temp->item_Id_No = fin;
    strcpy(temp->name, a);
    temp->rating = 4.0;
    temp->price = p;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

void insertion(char n[], float p, int fin) {
    struct Item* temp1 = getnewNode(n, p, fin);
    if (head == NULL) {
        head = temp1;
        last = temp1;
    }
    else {
        temp1->prev = last;
        last->next = temp1;
        last = temp1;
    }
}

struct order_list* getnewNode_list() {
    struct order_list* temp = (struct order_list*)malloc(sizeof(struct order_list));
    temp->next = temp->prev = NULL;
    return temp;
}

void Display() {
    printf("                                                  -------------                                                        \n");
    printf("-------------------------------------------------------MENU------------------------------------------------------------\n");
    printf("                                                  -------------                                                        \n");
    printf("INDEX   ITEMNAME        PRICE           RATING\n");

    struct Item* temp = head;
    if (head == NULL) {
        printf("Empty");
    }

    while (temp != NULL) {
        printf("%d\t%s\t%.2f\t\t%.2f \n", temp->item_Id_No, temp->name, temp->price, temp->rating);
        temp = temp->next;
    }

    printf("-------------------------------------------------------------------------------------------------------------------\n");
}

int login() {
    char username[20];
    char userpwd[11];
    int i;

    printf("Enter your user Name : ");
    scanf("%s", username);

    printf("Enter your password : ");
    for (i = 0; i < 10; i++) {
        userpwd[i] = getch();
        printf("*");
    }
    userpwd[i] = '\0';

    if (!strcmp(username, "Admin") && !strcmp(userpwd, "adminadmin")) {
        printf("\n\nLogged In Successful\n");
        return 1;
    }
    else {
        printf("\n\nIncorrect username or password\n");
        return 0;
    }
}

void order() {
    int a[10][2];
    int n, j = 0, i = 0;

    do {
        printf("Please Enter the ITEM ID NUMBER OF ITEM AND QUANTITY: ");
        for (i = 0; i < 2; i++) {
            scanf("%d", &a[j][i]);
        }
        j++;
        printf("Do you want more items?\n 1. yes\n 2. no\n");
        scanf("%d", &n);
    } while (n == 1);

    float total_amount = 0.0;
    char name[25];
    char Date[11];

    printf("Enter your name : ");
    scanf("%s", name);
    printf("Enter Today's Date : ");
    scanf("%s", Date);

    int k = 0;
    printf("\n----------------------------------------------------------------------------------------------------\n");
    printf("                                                    BILL                                              \n");

    printf("Name: %s\n", name);
    printf("Date: %s\n", Date);

    for (k = 0; k < j; k++) {
        struct Item* temp = head;
        while (temp->item_Id_No != a[k][0]) {
            temp = temp->next;
        }
        printf("-------------------------------------------------------------------------------------------------------\n");
        printf("%d\t%s\t%d\t\t%.2f \n", temp->item_Id_No, temp->name, a[k][1], (a[k][1] * (temp->price)));
        total_amount += (a[k][1] * (temp->price));
    }
    printf("--------------------------------------------------------------------------------------------------------\n");
    printf("\nTotal payable Amount is: %.2f \n", total_amount);
    printf("--------------------------------------------------------------------------------------------------------\n");

    struct order_list* temp2 = getnewNode_list();
    temp2->amount = total_amount;
    temp2->Customer_ID = cust_id++;

    int p, s;

    for (p = 0; p < j; p++) {
        for (s = 0; s < 2; s++) {
            temp2->items[p][s] = a[p][s];
        }
    }

    if (head1 == NULL) {
        head1 = last1 = temp2;
    }
    else {
        last1->next = temp2;
        temp2->prev = last1;
        last1 = temp2;
    }

    strcpy(temp2->date, Date);

    Today_Customer++;
    total_income += total_amount;

    char orderData[100];
    snprintf(orderData, sizeof(orderData), "Name: %s, Date: %s, Total payable Amount: %.2f ", name, Date, total_amount);
    saveDataToFile("order_history.txt", orderData);
}

void saveDataToFile(const char* fileName, const char* data) {
    FILE* file = fopen(fileName, "a");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    fprintf(file, "%s\n", data);
    fclose(file);
}

void display_ord_list() {
    printf("                                                  -------------                                                   \n");
    printf("--------------------------------------------------ORDER HISTORY----------------------------------------------------\n");
    printf("                                                  -------------                                                   \n");
    printf("SR_NO   DATE        TOTAL AMOUNT\n");

    struct order_list* temp = head1;
    if (head1 == NULL) {
        printf("Empty");
    }
    while (temp != NULL) {
        printf("%d\t%s\t%0.2f\t\n", temp->Customer_ID, temp->date, temp->amount);
        temp = temp->next;
    }
}

int main() {
    head = NULL;
    last = NULL;

    insertion("Egg        ", 15.00, 1);
    insertion("Canned fish", 250.50, 2);
    insertion("Pasta      ", 150.87, 3);
    insertion("Rice       ", 70.23, 4);
    insertion("Dried fruit", 360.80, 5);
    insertion("Yogurt     ", 91.50, 6);
    insertion("ICE CREAM  ", 60.23, 7);
    insertion("BREAD      ", 23.15, 8);
    insertion("COLD DRINK ", 20.13, 9);

    int choice;

    do {
        printf("\n--------------------------------------------------------------------------------------------------------\n");
        printf("1. ITEM PART\n");
        printf("2. ADMIN PANEL\n");
        printf("3. EXIT\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("");
            int ex;

            do {
                printf("1. ITEM LIST\n2. ORDER\n");
                int n;
                scanf("%d", &n);

                switch (n) {
                case 1:
                    Display();
                    break;
                case 2:
                    order();
                    break;
                }

                printf("1. ITEM PART\n2. MAIN MENU\n");
                scanf("%d", &ex);
            } while (ex == 1);
            break;

        case 2:
            printf("\n");
            int k = login();
            int e;
            if (k == 1) {
                do {
                    printf("--------------------------------------------------------------------------------------------------------\n");
                    printf("1. ADD NEW ITEM\n");
                    printf("2. TODAY's TOTAL INCOME\n");
                    printf("3. TODAY TOTAL NUMBER OF CUSTOMER\n");
                    printf("4. ORDER HISTORY\n");
                    printf("5. LIST OF ITEMS\n");

                    int ch;
                    scanf("%d", &ch);
                    switch (ch) {
                    case 1:
                        printf(" ");
                        float p;
                        int fin;
                        char n[50];

                        printf("Enter The Name Of Item: ");
                        scanf("%s", n);

                        printf("Enter The Price Of Item: ");
                        scanf("%.2f ", &p);

                        printf("Enter The item_id_No Of Item: ");
                        scanf("%d", &fin);

                        insertion(n, p, fin);
                        printf("--------------------------------------------------------------------------------------------------------\n");
                        printf("------------------------NEW ITEM IS ADDED SUCCESSFULLY------------------------------\n");
                        printf("--------------------------------------------------------------------------------------------------------\n");
                        printf("\n");
                        break;

                    case 2:
                        printf("--------------------------------------------------------------------------------------------------------\n");
                        printf("------------------------TODAY's TOTAL INCOME: %.2f \n", total_income);
                        printf("--------------------------------------------------------------------------------------------------------\n");
                        break;

                    case 3:
                        printf("--------------------------------------------------------------------------------------------------------\n");
                        printf("------------------------TODAY TOTAL NO OF CUSTOMER VISITED ID: %d\n", Today_Customer);
                        printf("--------------------------------------------------------------------------------------------------------\n");
                        break;

                    case 4:
                        printf("--------------------------------------------------------------------------------------------------------\n");
                        printf("------------------------ORDER SUMMARY\n");
                        printf("--------------------------------------------------------------------------------------------------------\n");
                        display_ord_list();
                        printf("\n");
                        break;

                    case 5:
                        printf("\n");
                        Display();
                        break;
                    }
                } while (e == 1);
            }
        }
    } while (choice != 3);

    return 0;
}
