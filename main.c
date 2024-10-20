#include <stdio.h>
#include <stdlib.h>
#include "contact.h"

int main()
{
    AddressBook book;
    int choice;
    do
    {
        printf("\n\n=============================================================\n");
        printf("             ADDRESS BOOK MENU          \n");
        printf("=============================================================\n");
        printf("1. Create Contact\n");
        printf("2. Search Contact\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. List All Contact\n");
        printf("6. Exit\n");
        printf("=============================================================\n");
        printf("Enter your choice :");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            createContact(&book);
            break;
        case 2:
            searchContact(&book);
            break;
        case 3:
            editContact(&book);
            break;
        case 4:
            deleteContact(&book);
            break;
        case 5:
            listContacts(&book);
            break;
        case 6:
            exit(0);
            break;
        }
    } while (choice != 6);

    return 0;
}
