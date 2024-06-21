#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000
// In each data, there is quantity, name, category
struct data {
    int quantity;
    char name[MAX];
    char category[MAX];
    int weight;
    struct data *next;    
    struct data *prev;
};

struct data *head = NULL, *newnode, *temp;
//Menu 
void gudangTitle(){
    printf(" _______  __   __  ______   _______  __    _  _______    _______  ______    _______  _______  _______  _______  __   __  _______  _______ \n");
    printf("|       ||  | |  ||      | |   _   ||  |  | ||       |  |       ||    _ |  |       ||       ||       ||       ||  | |  ||       ||       |\n");
    printf("|    ___||  | |  ||  _    ||  |_|  ||   |_| ||    ___|  |    _  ||   | ||  |   _   ||_     _||   _   ||_     _||  |_|  ||    _  ||    ___|\n");
    printf("|   | __ |  |_|  || | |   ||       ||       ||   | __   |   |_| ||   |_||_ |  | |  |  |   |  |  | |  |  |   |  |       ||   |_| ||   |___ \n");
    printf("|   ||  ||       || |_|   ||       ||  _    ||   ||  |  |    ___||    __  ||  |_|  |  |   |  |  |_|  |  |   |  |_     _||    ___||    ___|\n");
    printf("|   |_| ||       ||       ||   _   || | |   ||   |_| |  |   |    |   |  | ||       |  |   |  |       |  |   |    |   |  |   |    |   |___ \n");
    printf("|_______||_______||______| |__| |__||_|  |__||_______|  |___|    |___|  |_||_______|  |___|  |_______|  |___|    |___|  |___|    |_______|\n");
}

void menu(){
    system("cls");
    gudangTitle();
    printf("================Warehouse Inventory=============\n");
    printf("==1. Input Data                               ==\n");
    printf("==2. View Data                                ==\n");
    printf("==3. Delete Data                              ==\n");
    printf("==4. Export Data to CSV                       ==\n");
    printf("==5. Import data from CSV                     ==\n");
    printf("==0. Exit                                     ==\n");
    printf("================================================\n");
}

void inputData() {
    char itemName[MAX];
    int itemQuantity, itemWeight;
    char itemCategory[MAX];

    printf("Masukan Nama Barang: ");
    getchar();
    scanf("%[^\n]", itemName);
    printf("\nJumlah Barang: ");
    getchar();
    scanf("%d", &itemQuantity);
    printf("\nBerat Barang: ");
    getchar();
    scanf("%d", &itemWeight);
    printf("\nKategori Barang: ");
    getchar();
    scanf("%[^\n]", itemCategory);

    temp = head;
    //mengecek apabila ada data yang sama, data akan diperbarui jumlahnya dan beratnya
    while (temp != NULL) {
        if (strcmp(temp->name, itemName) == 0) {
            temp->quantity += itemQuantity;
            temp->weight += itemWeight;
            printf("Jumlah barang telah diperbarui.\n");
            return;
        }
        temp = temp->next;
    }

    newnode = (struct data*)malloc(sizeof(struct data));
    strcpy(newnode->name, itemName);
    newnode->quantity = itemQuantity;
    newnode->weight = itemWeight;
    strcpy(newnode->category, itemCategory);
    newnode->prev = NULL;
    newnode->next = NULL;

    if (head == NULL){
        head = newnode;
    }else{
        newnode -> next = head;
        head = newnode;
    }
    printf("Barang telah masuk ke dalam database\n");
}
//delete seesuai nama
void deleteName() {
    if (head == NULL) {
        printf("No such item inside the inventory\n");
        return;
    }
    char delName[MAX];
    printf("Enter the name of the item to delete: ");
    getchar();
    scanf("%[^\n]", delName);

    temp = head;
    while (temp != NULL && strcmp(temp->name, delName) != 0) {
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Item not found\n");
        return;
    }
    
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next;
    }
    
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    
    free(temp);
    printf("Item has been deleted successfully\n");
}
//implementasi stack
void checkout(){
      if (head == NULL){
        printf("No such item inside the inventory\n");
        return;
    }

    temp = head;
    head = head->next;
    if (head != NULL) {
        head->prev = NULL;
    }
    free(temp);
    printf("================================================\n");
    printf("=======Item has been deleted successfully=======\n");
    printf("================================================\n");
}
void checkoutByName() {
    char ref[MAX];
    printf("Input the name of the item you wish to checkout: ");
    getchar();  // Consume the newline character left by the previous input
    scanf("%[^\n]", ref);
    if (head == NULL) {
        printf("There are no data in the inventory\n");
        return;
    }
    temp = head;
    while (temp != NULL && strcmp(temp->name, ref) != 0) {
        temp = temp->next;
    }
    if (temp != NULL && strcmp(temp->name, ref) == 0) {
        printf("Data is found, do you want to delete all(1) or delete some(2)? ");
        int c;
        scanf("%d", &c);
        switch (c) {
            case 1:
                if (temp->prev != NULL) {
                    temp->prev->next = temp->next;
                } else {
                    head = temp->next;
                }

                if (temp->next != NULL) {
                    temp->next->prev = temp->prev;
                }
                free(temp);
                printf("Item has been deleted successfully\n");
                break;
            case 2:
                printf("How much of the data do you want to delete?\n");
                printf("There are currently %d of %s\n", temp->quantity, temp->name);
                int r;
                printf(">>");
                scanf("%d", &r);
                if (r <= temp->quantity) {
                    temp->quantity -= r;
                    printf("Data is updated\n");
                } else {
                    printf("Not enough items to delete\n");
                }
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } else {
        printf("Item not found\n");
    }
}
//menu delete data
void deleteData(){
       int c;  
    if (head == NULL){
        printf("Inventory Data is empty\n");
        return;
    }
    printf("================================================\n");
    printf("Select view method: \n");
    printf("1. Check out\n");
    printf("2. Delete by name\n");
    printf("3. Checkout by name\n");
    printf("================================================\n");
    printf("Enter your input: ");
    scanf("%d", &c);
    
    switch(c){
        case 1:
            checkout();
            break;
        case 2:
            deleteName();
            break;
        case 3:
            checkoutByName();
            break;
        default:
            printf("Invalid Choice\n");
            break;
    }
    
}
//display seluruh inventory berdasarkan barang yang paling baru di masukan
void displayAll() {
    if (head == NULL) {
        printf("Inventory Data is empty\n");
        return;
    }

    temp = head;
    printf("%-20s %-15s %-15s %-15s\n", "Name", "Quantity", "Weight", "Category");
    while (temp != NULL) {
        printf("%-20s %-15d %-15d %-15s\n", temp->name, temp->quantity, temp->weight, temp->category);
        temp = temp->next;
    }
}
//mengdisplay data sesuai dengan nama yang dicari
void displayName(){
    if (head == NULL) {
        printf("Inventory Data is empty\n");
        return;
    }
 
    temp = head;
    char ref[MAX];
    printf("Input the name of the item: ");
    scanf("%[^\n]", ref);
    getchar();
    printf("%-20s %-15s %-15s %-15s\n", "Name", "Quantity", "Weight", "Category");
    while (temp != NULL){
        if(strcmp(temp->name, ref) == 0){
            printf("%-20s %-15d %-15d %-15s\n", temp->name, temp->quantity, temp->weight, temp->category);
        }
        temp = temp->next;
    }
}
//mengdisplay data yang kategorinya sama
void displayCategory() {
    if (head == NULL) {
        printf("Inventory Data is empty\n");
        return;
    }

    temp = head;
    char ref[MAX];
    printf("Input the category of the item: ");
    scanf("%[^\n]", ref);
    getchar();
    printf("%-20s %-15s %-15s %-15s\n", "Name", "Quantity", "Weight", "Category");
    while (temp != NULL) {
        if (strcmp(temp->category, ref) == 0) {
            printf("%-20s %-15d %-15d %-15s\n", temp->name, temp->quantity, temp->weight, temp->category);
        }
        temp = temp->next;
    }
}
//menu display
void display(){
    int c;  
    if (head == NULL){
        printf("Inventory Data is empty\n");
        return;
    }
    printf("Select view method: \n");
    printf("1. View all\n");
    printf("2. View by name\n");
    printf("3. View by category\n");
    printf("Enter your input: ");
    scanf("%d", &c);
    getchar();
    
    switch(c){
        case 1:
            displayAll();
            break;
        case 2:
            displayName();
            break;
        case 3:
            displayCategory();
            break;
        default:
            printf("Invalid Choice\n");
            break;
    }
}
void importFromCSV() {
    FILE *fp = fopen("Inventory.csv", "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return;
    }
    
    char buffer[MAX];
    fgets(buffer, MAX, fp); // Skip the header line

    while (fgets(buffer, MAX, fp)) {
        newnode = (struct data*)malloc(sizeof(struct data));
        sscanf(buffer, "%[^,],%d,%d,%[^,]", newnode->name, &newnode->quantity, &newnode->weight, newnode->category);
        newnode->prev = NULL;
        newnode->next = NULL;

        if (head == NULL) {
            head = newnode;
        } else {
            newnode->next = head;
            head->prev = newnode;
            head = newnode;
        }
    }

    fclose(fp);
    printf("Data has been imported from Inventory.csv successfully.\n");
}
//melakukan export to csv (masih ada bug)
void exportToCSV(){
    FILE *fp = fopen("Inventory.csv","w");
    if (fp == NULL){
        printf("failed to make a file\n");
    }
    fprintf(fp, "Name,Quantity,Weight,Category\n");
    temp = head;
    while (temp != NULL) {
        fprintf(fp, "%s,%d,%d,%s\n", temp->name, temp->quantity, temp->weight, temp->category);
        temp = temp->next;
    }
    
    fclose(fp);
    printf("Data has been exported to inventory.csv successfully.\n");
}
//main
int main(){
  int m;
    do{
        menu();
        do{
            printf(">>> ");
            scanf("%d", &m);   
               }while(m > 4);
    switch(m) {
        case 1:
           inputData();
           break;
        case 2:
           display();
           break;
        case 3:
           deleteData();
           break;
        case 4:
            exportToCSV();
            break;
        case 5:
            importFromCSV();
            break;
        case 0:
            printf("BYE BYE!\n");
            break;
        default:
           printf("Waduh ga ada pilihannya cok\n");
           break;
    }
  }while(m !=0);
 return 0;   
}