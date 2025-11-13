#include "contact.h"
// Dummy contact data
static Contact dummyContacts[] = {
    {"Abhi Abhi", "1234567890", "abhi@example.com"},
    {"Ram Ram", "09876543210", "ram@example.com"},
    {"Abhi Abhi", "1112223333", "abhi@company.com"},
};

void populateAddressBook(AddressBook* addressBook)
{
   int size=sizeof(dummyContacts)/sizeof(dummyContacts[0]);
   for(int i=0;i<size;i++)
   {
       addressBook->contacts[i]=dummyContacts[i];
       (addressBook->contactCount)++;
   }
}