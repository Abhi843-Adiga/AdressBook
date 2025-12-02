#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "contact.h"
#include "populate.h"
#include "file.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    Contact te[addressBook->contactCount];
    for(int i=0;i<addressBook->contactCount;i++)
    te[i]=addressBook->contacts[i];
    if(sortCriteria==1)
    {
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
           for(int j=0;j<addressBook->contactCount-i-1;j++)
           {
              if(strcasecmp(te[j].name,te[j+1].name)>0)
              {
                Contact t=te[j];
                te[j]=te[j+1];
                te[j+1]=t;
              }
           }
        }
    }
    else if(sortCriteria==2)
    {
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
           for(int j=0;j<addressBook->contactCount-i-1;j++)
           {
              if(strcasecmp(te[j].phone,te[j+1].phone)>0)
              {
                Contact t=te[j];
                te[j]=te[j+1];
                te[j+1]=t;
              }
           }
        }
    } 
    else if(sortCriteria==3)
    {
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
           for(int j=0;j<addressBook->contactCount-i-1;j++)
           {
              if(strcasecmp(te[j].email,te[j+1].email)>0)
              {
                Contact t=te[j];
                te[j]=te[j+1];
                te[j+1]=t;
              }
           }
        }
    }
    printf("LISTING CONTACTS.......\n");
    sleep(2);
    int c=1;
    printf("%*s|%-39s|\n",30,"","\t\t\tADDRESS BOOK LIST");
    printf("%*s|Slno.|%-15s|%-10s|%-20s|\n",30,"","Name","Phone","Email");
    for(int i=0;i<addressBook->contactCount;i++)
    {
        printf("%*s|%-5d|%-15s|%-10s|%-20s|\n",30,"",c,te[i].name,te[i].phone,te[i].email); 
        c++;
    }
     
}

void initialize(AddressBook *addressBook) {
     addressBook->contactCount = 0;
     //populateAddressBook(addressBook);
     printf("\nINITIALISING CONTACTS.......\n");
     sleep(1);
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
int check(AddressBook *addressBook,char *which,int *ind,int t)
{
    int m,c=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        m=0;
        if(t==1 && strcmp(which,addressBook->contacts[i].name)==0)
        m=1;
        if(t==2 && strcmp(which,addressBook->contacts[i].phone)==0)
        m=1;
        if(t==3 && strcmp(which,addressBook->contacts[i].email)==0)
        m=1;
        if(m)
        ind[c++]=i;
    }
    return c;
}   
void createContact(AddressBook *addressBook)
{
    if(addressBook->contactCount > MAX_CONTACTS)
    {
        printf("ADDRESS BOOK IS FULL!!\n");
        return ;
    }
    printf("CREATE CONTACT.......\n");
    sleep(2);
    char name[20],email[25],phone [20],res=0,pc=0,ec=0;
    int ind[25];
    printf("Enter name to create: ");
    scanf(" %[^\n]",name);
    do
    {
    printf("Enter phone No. to create: ");
    scanf(" %[^\n]",phone);
    pc=validatephone(phone);
    res=check(addressBook,phone,ind,2);
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
    res=check(addressBook,email,ind,3);
    if(ec)
    {
       if(res)
       printf("Email ID already exists\n");
    }
    else
    printf("Email ID is INVALID\n");
    } while (ec==0 || res>0);

    strcpy(addressBook->contacts[addressBook->contactCount].name,name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email,email);
    (addressBook->contactCount)++;
    printf("CREATED CONTACTS SUCCESSFULLY !!.......\n");
    sleep(2);
}

void searchContact(AddressBook *addressBook) 
{ 
    printf("SEARCHING CONTACTS.......\n");
    sleep(2);
    printf("1. search by name\n2. search by phone number\n3.search by email id\n");
    int option,flag=0,ind[25],collect;
    char name[20],phone[20],email[25];
    printf("Choose option:\n");
    if(scanf("%d",&option)==1 && (option>=1 && option<=3))
    {
    switch(option)
    {
        case 1:
        printf("Enter name to search: ");
        scanf(" %[^\n]",name);
        flag=check(addressBook,name,ind,1);
        if(flag>0)
        {
            for(int i=0;i<flag;i++)
            {
                collect=ind[i];
                printf("%d. %s %s %s\n",collect+1,addressBook->contacts[collect].name,addressBook->contacts[collect].phone,addressBook->contacts[collect].email);
            }
        }
        else
        printf("Name isn't present\n");
        break;
        case 2:
        printf("Enter phone to search: ");
        scanf(" %[^\n]",phone);
        flag=check(addressBook,phone,ind,2);
        if(flag>0)
        {
            for(int i=0;i<flag;i++)
            {
                collect=ind[i];
                printf("%d. %s %s %s\n",collect+1,addressBook->contacts[collect].name,addressBook->contacts[collect].phone,addressBook->contacts[collect].email);
            }
        }
        else
        printf("Phone no. isn't present\n");
        break;
        case 3:
        printf("Enter email ID to search: ");
        scanf(" %[^\n]",email);
        flag=check(addressBook,email,ind,3);
        if(flag>0)
        {
            for(int i=0;i<flag;i++)
            {
                collect=ind[i];
                printf("%d. %s %s %s\n",collect+1,addressBook->contacts[collect].name,addressBook->contacts[collect].phone,addressBook->contacts[collect].email);
            }
        }
        else
        printf("Email ID isn't present\n");
        break;
    }
    }
    else
    {
        printf("Option invalid !\n");
        while(getchar()!='\n');
    }
}

void editContact(AddressBook *addressBook)
{
    printf("EDITING CONTACTS.......\n");
    sleep(2);
    int option,choice,index=-1,flag=0,uindex,pc=0,ec=0,res=0,ind[25],collect,v;
    char name[20],phone[20],email[25];
    printf("1.Choose by name\n2.Choose by phone\n3.Choose by email\n");
    printf("Choose option: ");
    if(scanf("%d",&option)==1 && (option>=1 && option<=3))
    {
    switch(option)
    {
        case 1:
        printf("Enter name: ");
        scanf(" %[^\n]",name);
        flag=check(addressBook,name,ind,1);
        if(flag>0)
        {
            for(int i=0;i<flag;i++)
            {
                collect=ind[i];
                printf("%d. %s %s %s\n",collect+1,addressBook->contacts[collect].name,addressBook->contacts[collect].phone,addressBook->contacts[collect].email);
            }
        }
        else
        printf("Name isn't present\n");
        break;
        case 2:
        printf("Enter phone no.: ");
        scanf(" %[^\n]",phone);
        flag=check(addressBook,phone,ind,2);
        if(flag>0)
        {
            for(int i=0;i<flag;i++)
            {
                collect=ind[i];
                printf("%d. %s %s %s\n",collect+1,addressBook->contacts[collect].name,addressBook->contacts[collect].phone,addressBook->contacts[collect].email);
            }
        }
        else
        printf("Phone no. isn't present\n");
        break;
        case 3:
        printf("Enter email ID: ");
        scanf(" %[^\n]",email);
        flag=check(addressBook,email,ind,3);
        if(flag>0)
        {
            for(int i=0;i<flag;i++)
            {
                collect=ind[i];
                printf("%d. %s %s %s\n",collect+1,addressBook->contacts[collect].name,addressBook->contacts[collect].phone,addressBook->contacts[collect].email);
            }
        }
        else
        printf("Email ID isn't present\n");
        break;
    }
    }
    else
    {
        printf("Option INVALID !\n");
        while(getchar()!='\n');
    }
    if(flag>1)
    {
        do 
        {
        printf("Choose the index: ");
        if(scanf("%d",&uindex)==1)
        {
        v=0;
        for(int i=0;i<flag;i++)
        {
            if(uindex==ind[i])
            {
                index=uindex;
                v=1;
                break;
            }
        }
        if(!v)
        printf("Choose the correct index man\n");
        }
        else
        {
            printf("option is invalid\n");
            while(getchar()!='\n');
        }
        }while(!v);
    }
    else if(flag!=0)
    index=ind[0];
    if(index!=-1)
            {
                printf("1.edit name\n2.edit phone\n3.edit email\n4.edit all fields\n");
                printf("Choose the option: ");
                if(scanf("%d",&choice)==1 && (option>=1 && option<=4))
                {
                switch(choice)
                {
                    case 1:
                    do
                    {
                    printf("Enter new name: ");
                    scanf(" %[^\n]",name);
                    res=check(addressBook,name,ind,1);
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
                    res=check(addressBook,phone,ind,2);
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
                    res=check(addressBook,email,ind,3);
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
                    res=check(addressBook,name,ind,1);
                    if(res)
                    printf("Name already exist\n");
                    } while (res>0);
                    do
                    {
                    printf("Enter phone No. to create: ");
                    scanf(" %[^\n]",phone);
                    pc=validatephone(phone);
                    res=check(addressBook,phone,ind,2);
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
                    scanf(" %[^\n]",phone);
                    pc=validateemail(email);
                    res=check(addressBook,email,ind,3);
                    if(pc)
                    {
                    if(res)
                    printf("Email ID already exist\n");
                    }  
                    else
                    printf("INVALID Email ID\n");
                    } while (pc==0 || res>0);
                    strcpy(addressBook->contacts[index].name,name);
                    strcpy(addressBook->contacts[index].phone,phone);
                    strcpy(addressBook->contacts[index].email,email);
                    break;
                }
            }
            else
            {
                printf("Option INVALID !");
                while(getchar()!='\n');
            }
        }
    printf("EDITED CONTACT SUCCESSFULLY !!.......\n");
    sleep(2);
}


void deleteContact(AddressBook *addressBook)
{
    printf("DELETING CONTACT.......\n");
    sleep(2);
    int option,index=-1,flag=0,uindex,ind[25],collect,v;
    char name[20],phone[20],email[25];
    printf("1.Choose by name\n2.Choose by phone\n3.Choose by email\n");
    printf("Choose option: ");
    if(scanf("%d",&option)==1 && (option>=1 && option<=3))
    {
    switch(option)
    {
        case 1:
        printf("Enter name: ");
        scanf(" %[^\n]",name);
        flag=check(addressBook,name,ind,1);
        if(flag>0)
        {
            for(int i=0;i<flag;i++)
            {
                collect=ind[i];
                printf("%d. %s %s %s\n",collect+1,addressBook->contacts[collect].name,addressBook->contacts[collect].phone,addressBook->contacts[collect].email);
            }
        }
        else
        printf("Name isn't present\n");
        break;
        case 2:
        printf("Enter phone no.: ");
        scanf(" %[^\n]",phone);
        flag=check(addressBook,phone,ind,2);
        if(flag>0)
        {
            for(int i=0;i<flag;i++)
            {
                collect=ind[i];
                printf("%d. %s %s %s\n",collect+1,addressBook->contacts[collect].name,addressBook->contacts[collect].phone,addressBook->contacts[collect].email);
            }
        }
        else
        printf("Phone no. isn't present\n");
        break;
        case 3:
        printf("Enter email ID: ");
        scanf(" %[^\n]",email);
        flag=check(addressBook,email,ind,3);
        if(flag>0)
        {
            for(int i=0;i<flag;i++)
            {
                collect=ind[i];
                printf("%d. %s %s %s\n",collect+1,addressBook->contacts[collect].name,addressBook->contacts[collect].phone,addressBook->contacts[collect].email);
            }
        }
        else
        printf("Email ID isn't present\n");
        break;       
    }
    }
    else
    {
        printf("Option is invalid\n");
        while(getchar()!='\n');
    }
    if(flag>1)
    {
        do 
        {
        printf("Choose the index: ");
        if(scanf("%d",&uindex)==1)
        {
        v=0;
        for(int i=0;i<flag;i++)
        {
            if(uindex==ind[i])
            {
                index=uindex;
                v=1;
                break;
            }
        }
        if(!v)
        printf("Choose the correct index man\n");
        }
        else
        {
            printf("Option INVALID\n");
            while(getchar()!='\n');
        }
        }while(!v);
    }
    else if(flag!=0)
    index=ind[0];
    if(index!=-1)
    {
        for(int i=index;i<addressBook->contactCount-1;i++)
        addressBook->contacts[i]=addressBook->contacts[i+1];
        (addressBook->contactCount)--;
    }
    printf("DELETED CONTACT SUCCESSFULLY.......\n");
    sleep(2);
}
