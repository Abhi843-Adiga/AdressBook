#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "populate.h"
#include "file.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    if(sortCriteria==1)
    {
        for(int i=0;i<addressBook->contactCount;i++)
        {
    printf("%s %s %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);           
        }
    }
    else if(sortCriteria==2)
    {
        for(int i=0;i<addressBook->contactCount;i++)
        {
          printf("%s %s %s\n",addressBook->contacts[i].phone,addressBook->contacts[i].email,addressBook->contacts[i].name);
        }
    } 
    else if(sortCriteria==3)
    {
        for(int i=0;i<addressBook->contactCount;i++)
        {
          printf("%s %s %s\n",addressBook->contacts[i].email,addressBook->contacts[i].name,addressBook->contacts[i].phone);
        }
    }
}

void initialize(AddressBook *addressBook) {
     addressBook->contactCount = 0;
     //populateAddressBook(addressBook);
     loadContactsFromFile(addressBook);
}
int validatephone(char *phone)
{
   if((strlen(phone))==10)
   return 1;
   return 0;
}
int validateemail(char *email)
{
    int sp=0;
    int l=strlen(email);
    if(l<4)
    return 0;
    char *cp=strchr(email,'@');
    if(cp==NULL)
    return 0;
    for(int i=0;i<l;i++)
    {
        if(email[i]==' ')
        {sp=1;
         break;
        }
    }
    int d=strcmp(email+l-4,".com");
    char *r=strchr(cp+1,'@');
    if((!sp) && (cp!=email) && (!d) &&(!r))
    return 1;
    return 0;
}
int checkphone(AddressBook *addressBook,char *phone,int *ind)
{
    int m,c=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        m=0;
        if(strcmp(phone,addressBook->contacts[i].phone)==0)
        m=1;
        if(m)
        ind[c++]=i;
    }
    return c;
}   
    
int checkname(AddressBook *addressBook,char *name,int *ind)
{
    int m,c=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        m=0;
        if(strcmp(name,addressBook->contacts[i].name)==0)
        m=1;
        if(m)
        ind[c++]=i;
    }
    return c;
}
int checkemail(AddressBook *addressBook,char *email,int *ind)
{
    int m,c=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        m=0;
        if(strcmp(email,addressBook->contacts[i].email)==0)
        m=1;
        if(m)
        ind[c++]=i;
    }
    return c;
} 
void createContact(AddressBook *addressBook)
{
    char name[20],email[25],phone [20],res=0,pc=0,ec=0;
    int ind[25];
    printf("Enter name to create: ");
    scanf(" %[^\n]",name);
    do
    {
    printf("Enter phone No. to create: ");
    scanf(" %[^\n]",phone);
    pc=validatephone(phone);
    res=checkphone(addressBook,phone,ind);
    if(pc)
    {
        if(res)
        printf("Phone no. already exist\n");
    } 
    else
    printf("Phone no. should be 10 digits man\n");
    } while (pc==0 || res==1);
    do
    {
    printf("Enter email ID to create: ");
    scanf(" %[^\n]",email);
    ec=validateemail(email);
    res=checkemail(addressBook,email,ind);
    if(ec)
    {
       if(res)
       printf("Email ID already exists\n");
    }
    else
    printf("Email ID is INVALID\n");
    } while (ec==0 || res==1);

    strcpy(addressBook->contacts[addressBook->contactCount].name,name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email,email);
    (addressBook->contactCount)++;
}

void searchContact(AddressBook *addressBook) 
{ 
    printf("1. search by name\n2. search by ph no\n3.search by email id\n");
    int option,flag=0,ind[25],collect;
    char name[20],phone[20],email[25];
    printf("Choose option:\n");
    scanf("%d",&option);
     
    switch(option)
    {
        case 1:
        printf("Enter name to search: ");
        scanf(" %[^\n]",name);
        flag=checkname(addressBook,name,ind);
        if(flag>0)
        {
            for(int i=0;i<flag;i++)
            {
                collect=ind[i];
                printf("%d %s %s %s\n",collect,addressBook->contacts[collect].name,addressBook->contacts[collect].phone,addressBook->contacts[collect].email);
            }
        }
        else
        printf("Name isn't present\n");
        break;
        case 2:
        printf("Enter phone to search: ");
        scanf(" %[^\n]",phone);
        flag=checkphone(addressBook,phone,ind);
        if(flag>0)
        {
            for(int i=0;i<flag;i++)
            {
                collect=ind[i];
                printf("%d %s %s %s\n",collect,addressBook->contacts[collect].name,addressBook->contacts[collect].phone,addressBook->contacts[collect].email);
            }
        }
        else
        printf("Phone no. isn't present\n");
        break;
        case 3:
        printf("Enter email ID to search: ");
        scanf(" %[^\n]",email);
        flag=checkemail(addressBook,email,ind);
        if(flag>0)
        {
            for(int i=0;i<flag;i++)
            {
                collect=ind[i];
                printf("%d %s %s %s\n",collect,addressBook->contacts[collect].name,addressBook->contacts[collect].phone,addressBook->contacts[collect].email);
            }
        }
        else
        printf("Email ID isn't present\n");
        break;
        default:
        printf("try again U choose wrong option\n");
    }
}

void editContact(AddressBook *addressBook)
{
    int option,choice,index=-1,flag=0,uindex,pc=0,ec=0,res=0,ind[25],collect;
    char name[20],phone[20],email[25];
    printf("1.Choose by name\n2.Choose by phone\n3.Choose by email\n");
    printf("Choose option: ");
    scanf("%d",&option);
    switch(option)
    {
        case 1:
        printf("Enter name: ");
        scanf(" %[^\n]",name);
        flag=checkname(addressBook,name,ind);
        if(flag>0)
        {
            for(int i=0;i<flag;i++)
            {
                collect=ind[i];
                printf("%d %s %s %s\n",collect,addressBook->contacts[collect].name,addressBook->contacts[collect].phone,addressBook->contacts[collect].email);
            }
        }
        else
        printf("Name isn't present\n");
        break;
        case 2:
        printf("Enter phone no.: ");
        scanf(" %[^\n]",phone);
        flag=checkphone(addressBook,phone,ind);
        if(flag>0)
        {
            for(int i=0;i<flag;i++)
            {
                collect=ind[i];
                printf("%d %s %s %s\n",collect,addressBook->contacts[collect].name,addressBook->contacts[collect].phone,addressBook->contacts[collect].email);
            }
        }
        else
        printf("Phone no. isn't present\n");
        break;
        case 3:
        printf("Enter email ID: ");
        scanf(" %[^\n]",email);
        flag=checkemail(addressBook,email,ind);
        if(flag>0)
        {
            for(int i=0;i<flag;i++)
            {
                collect=ind[i];
                printf("%d %s %s %s\n",collect,addressBook->contacts[collect].name,addressBook->contacts[collect].phone,addressBook->contacts[collect].email);
            }
        }
        else
        printf("Email ID isn't present\n");
        break;
        default:
        printf("Try again U choose wrong option\n");
        
    }
    if(flag!=0)
    {
        printf("Choose the index: ");
        scanf("%d",&uindex);
        index=uindex;
    }
    if(index!=-1)
            {
                printf("1.edit name\n2.edit phone\n3.edit email\n4.edit all fields\n");
                printf("Choose the option: ");
                scanf("%d",&choice);
                switch(choice)
                {
                    case 1:
                    do
                    {
                    printf("Enter new name: ");
                    scanf(" %[^\n]",name);
                    res=checkname(addressBook,name,ind);
                    if(res)
                    printf("Name already exist\n");
                    } while (res>0);
                    strcpy(addressBook->contacts[index].name,name);
                    break;

                    case 2:
                    do
                    {
                    printf("Enter phone No. to create: ");
                    scanf(" %[^\n]",phone);
                    pc=validatephone(phone);
                    res=checkphone(addressBook,phone,ind);
                    if(pc)
                    {
                    if(res)
                    printf("Phone no. already exist\n");
                    }  
                    else
                    printf("Phone no. should be 10 digits man\n");
                    } while (pc==0 || res>0);
                    strcpy(addressBook->contacts[index].phone,phone);
                    break;
                    
                    case 3:
                    do
                    {
                    printf("Enter email ID to create: ");
                    scanf(" %[^\n]",phone);
                    pc=validateemail(email);
                    res=checkemail(addressBook,email,ind);
                    if(pc)
                    {
                    if(res)
                    printf("Email ID already exist\n");
                    }  
                    else
                    printf("INVALID Email ID\n");
                    } while (pc==0 || res>0);
                    strcpy(addressBook->contacts[index].email,email);
                    break;

                    case 4:
                    printf("Enter new all fields:\n");
                    do
                    {
                    printf("Enter new name: ");
                    scanf(" %[^\n]",name);
                    res=checkname(addressBook,name,ind);
                    if(res)
                    printf("Name already exist\n");
                    } while (res>0);
                    do
                    {
                    printf("Enter phone No. to create: ");
                    scanf(" %[^\n]",phone);
                    pc=validatephone(phone);
                    res=checkphone(addressBook,phone,ind);
                    if(pc)
                    {
                    if(res)
                    printf("Phone no. already exist\n");
                    }  
                    else
                    printf("Phone no. should be 10 digits man\n");
                    } while (pc==0 || res>0);
                    do
                    {
                    printf("Enter email ID to create: ");
                    scanf(" %[^\n]",email);
                    ec=validateemail(email);
                    if(ec)
                    {
                      for(int i=0;i<addressBook->contactCount;i++)
                    {
                         res=0;
                         if(strcmp(addressBook->contacts[i].email,email)==0)
                        {
                           printf("Email ID exists ,Try again\n");
                           res=1;
                           break;
                        }
                    }
                    }
                    else
                    printf("Email ID is INVALID\n");
                    } while (res>0 || ec==0);
                    strcpy(addressBook->contacts[index].name,name);
                    strcpy(addressBook->contacts[index].phone,phone);
                    strcpy(addressBook->contacts[index].email,email);
                    break;

                    default:
                    printf("Choose the right option man\n");

                }
            }
}


void deleteContact(AddressBook *addressBook)
{
    int option,index=-1,flag=0,uindex,ind[25],collect;
    char name[20],phone[20],email[25];
    printf("1.Choose by name\n2.Choose by phone\n3.Choose by email\n");
    printf("Choose option: ");
    scanf("%d",&option);
    switch(option)
    {
        case 1:
        printf("Enter name: ");
        scanf(" %[^\n]",name);
        flag=checkname(addressBook,name,ind);
        if(flag>0)
        {
            for(int i=0;i<flag;i++)
            {
                collect=ind[i];
                printf("%d %s %s %s\n",collect,addressBook->contacts[collect].name,addressBook->contacts[collect].phone,addressBook->contacts[collect].email);
            }
        }
        else
        printf("Name isn't present\n");
        break;
        case 2:
        printf("Enter phone no.: ");
        scanf(" %[^\n]",phone);
        flag=checkphone(addressBook,phone,ind);
        if(flag>0)
        {
            for(int i=0;i<flag;i++)
            {
                collect=ind[i];
                printf("%d %s %s %s\n",collect,addressBook->contacts[collect].name,addressBook->contacts[collect].phone,addressBook->contacts[collect].email);
            }
        }
        else
        printf("Phone no. isn't present\n");
        break;
        case 3:
        printf("Enter email ID: ");
        scanf(" %[^\n]",email);
        flag=checkemail(addressBook,email,ind);
        if(flag>0)
        {
            for(int i=0;i<flag;i++)
            {
                collect=ind[i];
                printf("%d %s %s %s\n",collect,addressBook->contacts[collect].name,addressBook->contacts[collect].phone,addressBook->contacts[collect].email);
            }
        }
        else
        printf("Email ID isn't present\n");
        break;
        default:
        printf("Try again U choose wrong option\n");
        
    }
    if(flag!=0)
    {
        printf("Choose the index: ");
        scanf("%d",&uindex);
        index=uindex;
    }
    if(index!=-1)
    {
        for(int i=index;i<addressBook->contactCount-1;i++)
        addressBook->contacts[i]=addressBook->contacts[i+1];
        (addressBook->contactCount)--;
    }
}
