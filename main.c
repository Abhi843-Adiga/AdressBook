#include <stdio.h>
#include "contact.h"
#include "file.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        if(scanf("%d",&choice)==1 && (choice>=1 && choice<=6))
        {
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                printf("Select sort criteria:\n");
                printf("1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("Enter your choice: ");
                int sortChoice;
                printf("Enter your choice: ");
                if(scanf("%d", &sortChoice)==1 && (sortChoice<=3 && sortChoice>=1))
                listContacts(&addressBook, sortChoice);
                else
                {
                    printf("Please provide correct sortchoice\n");
                    while(getchar()!='\n');
                }
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
        }
        }
        else
        {
            printf("Invalid choice\n");
            while(getchar()!='\n');
        }
    } while (choice != 6);
    
       return 0;
}
