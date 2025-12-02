#include <stdio.h>
#include "contact.h"
#include "file.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\n%*s|%-20s|\n",50,""," ADDRESS BOOK MENU");
        printf("%*s|%-20s|\n",50,"","1. Create contact");
        printf("%*s|%-20s|\n",50,"","2. Search contact");
        printf("%*s|%-20s|\n",50,"","3. Edit contact");
        printf("%*s|%-20s|\n",50,"","4. Delete contact");
        printf("%*s|%-20s|\n",50,"","5. List all contacts");
        printf("%*s|%-20s|\n",50,"","6. Exit");
        printf("\nEnter your choice: ");
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
                printf("\n%*s|%-24s|\n",50,""," Select Sort Criteria");
                printf("%*s|%-24s|\n",50,"","1. Sort by Name");
                printf("%*s|%-24s|\n",50,"","1. Sort by Phone Number");
                printf("%*s|%-24s|\n",50,"","1. Sort by Email ID");
                printf("\nEnter your choice: ");
                int sortChoice;
                if(scanf("%d", &sortChoice)==1 && (sortChoice<=3 && sortChoice>=1))
                listContacts(&addressBook, sortChoice);
                else
                {
                    printf("\nPlease Provide Correct Sortchoice\n");
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
            printf("Invalid choice!!\n");
            while(getchar()!='\n');
        }
    } while (choice != 6);
    
       return 0;
}
