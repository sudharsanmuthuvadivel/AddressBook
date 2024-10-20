#include <stdio.h>
//#include<stdio_exe.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook)
{
    if(addressBook->contacts->name[0] == 0)
    {
        addr_book_empty(addressBook);
    }
    else{
        int size = addressBook->contactCount;
        printf("\n--------------------------------------------------------\n");
        printf("Name\t\t| Phone Number\t|   Email Id\n");
        printf("--------------------------------------------------------\n");
        for (int i = 0; i < size; i++)
        {
            printf("%s\t|  %s \t|   %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
}

void initialize(AddressBook *addressBook)
{
    populateAddressBook(addressBook);
    printf("Duplicate user Details Initialization Successfull.\n");
}

void saveAndExit(AddressBook *addressBook)
{
}

void createContact(AddressBook *addressBook)
{
    int res, c;
    char input[30], ch;
    if(addressBook->contacts->name[0] == 0)
    {
        addressBook->contactCount = 0;
    }
    printf("Enter Name:");
    scanf(" %[^\n]", &input);
    getchar();
    strcpy(addressBook->contacts[addressBook->contactCount].name, input);
    mobile_number:
        printf("Enter Mobile Number:");
        scanf("%19[^\n]", &input);
        getchar();
        res = create_user(addressBook, input);
        if(res == 0)
            strcpy(addressBook->contacts[addressBook->contactCount].phone, input);
        else
            {
                printf("Do You Want to Continue to Enter Diffrent Number? press (Y/N): ");
                scanf(" %c", &ch);
                getchar();
                if(ch == 'Y' || ch == 'y')
                    goto mobile_number;
                else
                    return;
            }
    mail_id:
        printf("Enter EmailId:");
        scanf("%29[^\n]", &input);
        getchar();
        res = create_user(addressBook, input);
        if(res == 0){
            strcpy(addressBook->contacts[addressBook->contactCount].email, input);
            printf("Contact Created Successfull.\n");
            addressBook->contactCount++;
        }
        else
        {
            printf("Do You Want to Continue to Enter Diffrent EmailId? press (Y/N): ");
            scanf(" %c", &ch);
            getchar();
            if(ch == 'Y' || ch == 'y')
                goto mail_id;
            else
                return;
        }
    
}
static int create_user(AddressBook* addressBook, char arr[])
{
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if((strcmp(arr , addressBook->contacts[i].phone) == 0) || (strcmp(arr, addressBook->contacts[i].email) == 0))
        {
            printf("User Details Already Exsit.\n");
            return 1;
        }
    }
    return 0;
}

void searchContact(AddressBook *addressBook)
{
    int choice;
    char ch, arr[20];
    if(addressBook->contacts->name[0] == 0)
    {
        addr_book_empty(addressBook);
        return;
    }
    else
    {
        search:
            printf("Enter your choice to serach contact.\n");
            printf("1. Search by Name.\n");
            printf("2. Search by Phone number.\n");
            printf("3. Search by Email id.\n");
            scanf("%d", &choice);
            getchar();
            switch (choice)
            {
            case 1:
                printf("Enter Name: ");
                scanf("%19[^\n]", &arr);
                getchar();
                search_user(addressBook, arr);
                break;
            case 2:
                printf("Enter Mobile Number: ");
                scanf("%[^\n]", &arr);
                getchar();
                search_user(addressBook, arr);
                break;
            case 3:
                printf("Enter EmailId: ");
                scanf("%[^\n]", &arr);
                getchar();
                search_user(addressBook, arr);
                break;
            default:
                printf("Invalid Option\n");
                break;
            }
    }
    printf("Do you want to search again? press (Y/N):");
    scanf(" %c", &ch);
    getchar();
    if (ch == 'Y' || ch == 'y')
        goto search;
    else
        return;
}
static int search_user(AddressBook *addressBook, char arr[])
{
    int flag = 1, i;
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(arr, addressBook->contacts[i].name) == 0)
        {
            flag = 0;
            break;
        }
        else if(strcmp(arr, addressBook->contacts[i].phone) == 0)
        {
            flag = 0;
            break;
        }
        else if(strcmp (arr, addressBook->contacts[i].email) == 0)
        {
            flag = 0;
            break;
        }
    }
    if (flag == 0)
    {
        printf("\n--------------------------------------------------------\n");
        printf("Name\t\t| Phone Number\t|   Email Id\n");
        printf("--------------------------------------------------------\n");
        printf("%s\t|  %s \t|   %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        printf("\n");
        return i;
    }
    else{
        printf("User Doesn't Exist.\n");
        return -1;
    }
        
}
void editContact(AddressBook *addressBook)
{
    int choice, index;
    char ch, arr[20];
    if(addressBook->contacts->name[0] == 0)
    {
        addr_book_empty(addressBook);
    }
    else
    {
        edit:
            printf("Which Contact You Want to Edit?\n");
            printf("1. Select By Name.\n");
            printf("2. Select by MobileNumber.\n");
            printf("3. Select by EmailId.\n");
            printf("Enter Your Choice: ");
            scanf("%d", &choice);
            getchar();
            switch(choice)
            {
                case 1:
                    printf("Enter Name: ");
                    scanf("%19[^\n]", &arr);
                    getchar();
                    index = search_user(addressBook, arr);
                    //printf("%d\n", index);
                    if(index >= 0)
                        edit_user(addressBook, index);
                    break;
                case 2:
                    printf("Enter Mobilenumber: ");
                    scanf("%19[^\n]", &arr);
                    getchar();
                    index = search_user(addressBook, arr);
                    if(index >= 0)
                        edit_user(addressBook, index);
                    break;
                case 3:
                    printf("Enter EmailId: ");
                    scanf("%19[^\n]", &arr);
                    getchar();
                    index = search_user(addressBook, arr);
                    if(index >= 0)
                        edit_user(addressBook, index);
                    break;
            }
        printf("Do you want to Edit again? press (Y/N): ");
        scanf(" %c", &ch);
        getchar();
        if(ch == 'Y' || ch == 'y')
            goto edit;
        else
            return;
    }
} 
static void edit_user(AddressBook* addressBook, int index)
{
    int choice;
    char arr[20];
    printf("which Details you Want to Edit?\n");
    printf("1. Edit Name.\n");
    printf("2. Edit Mobile Number.\n");
    printf("3. Edit EmailId.\n");
    printf("Enter Your Choice: ");
    scanf("%d", &choice);
    getchar();
    switch(choice)
    {
        case 1:
            printf("Enter Newname: ");
            scanf("%19[^\n]", &arr);
            getchar();
            strcpy(addressBook->contacts[index].name, arr);
            printf("Contact Name Edited Successfully.\n");
            break;
        case 2:
            printf("Enter New Mobilenumber: ");
            scanf("%19[^\n]", &arr);
            getchar();
            strcpy(addressBook->contacts[index].phone, arr);
            printf("Contact Mobilenumber Edited Successfully.\n");
            break;
        case 3:
            printf("Enter New EmailId: ");
            scanf("%19[^\n]", &arr);
            getchar();
            strcpy(addressBook->contacts[index].email, arr);
            printf("Contact EmailId Edited Successfully.\n");
            break;
        default:
            printf("Invalid Option.\n");
            break;
    }
}

void deleteContact(AddressBook *addressBook)
{
    int choice, index;
    char input[20], ch;
    if(addressBook->contacts->name[0] == 0)
    {
        addr_book_empty(addressBook);
    }
    else{
        delete:
            printf("Select contact to delete\n");
            printf("1. select by Name.\n");
            printf("2. select by Mobile NUmber.\n");
            printf("3. Select by EmailId\n");
            printf("Enter your choice:");
            scanf("%d", &choice);
            getchar();
            switch(choice)
            {
                case 1:
                    printf("Enter Name:");
                    scanf("%19[^\n]", &input);
                    getchar();
                    index = search_user(addressBook, input);
                    if(index >= 0)
                        delete_user(addressBook, index);
                    break;
                case 2:
                    printf("Enter Mobile NUmber:");
                    scanf("%19[^\n]", &input);
                    getchar();
                    index = search_user(addressBook, input);
                    if(index >= 0)
                        delete_user(addressBook, index);
                    break;
                case 3:
                    printf("Enter EmailId:");
                    scanf("%19[^\n]", &input);
                    getchar();
                    index = search_user(addressBook, input);
                    if(index >= 0)
                        delete_user(addressBook, index);
                    break;
                default:
                    printf("Invalid Option.\n");
                    break;
            }
    printf("Do you want to delete again? press (Y/N): ");
    scanf(" %c", &ch);
    getchar();
    if(ch == 'Y' || ch == 'y')
        goto delete;
    else
        return;
    }
}
static void delete_user(AddressBook* addressBook, int index)
{
    char ch;
    printf("Are you sure to delete? press(Y/N):");
    scanf(" %c", &ch);
    getchar();
    if(ch == 'Y' || ch == 'y')
    {
        for(int i = index; i < addressBook->contactCount; i++)
        {
            strcpy(addressBook->contacts[i].name, addressBook->contacts[i+1].name);
            strcpy(addressBook->contacts[i].phone, addressBook->contacts[i+1].phone);
            strcpy(addressBook->contacts[i].email, addressBook->contacts[i+1].email);
        }
        addressBook->contactCount--;
        printf("Contact Deleted successfull.\n");
    }
    return;

}
static void addr_book_empty(AddressBook* addressBook)
{
    char ch;
    printf("Address Book is Empty!\n");
    printf("Shall I create duplicate user details? press (Y/N): ");
    scanf(" %c", &ch);
    getchar();
    if(ch == 'Y' || ch == 'y')
    {
        initialize(addressBook);
    }
    else
    {
        printf("Do you want to create New Contact? press (Y/N): ");
        scanf(" %c", &ch);
        getchar();
        if(ch == 'Y' || ch == 'y')
            createContact(addressBook);
        else
            return;
    }
}