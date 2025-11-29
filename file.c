#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
  
    FILE *fp=fopen("contacts.txt","w");
    if(fp==NULL)
    {
        printf("could not open file for writing\n");
        return;
    }
    fprintf(fp,"%d\n",addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);
}
void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fp=fopen("contacts.txt","r");
    if(fp==NULL)
    {
        printf("No saved contacts found.Create one...\n");
        addressBook->contactCount=0;
        return;
    }
    if(fscanf(fp,"%d\n",&addressBook->contactCount)!=1)
    {
        printf("Empty contact file.Start fresh...\n");
        addressBook->contactCount=0;
        fclose(fp);
        return;
    }
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);
}
