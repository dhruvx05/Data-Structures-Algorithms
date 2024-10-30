#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
    struct node* prev;
};

void traverse(struct node* head) {
    struct node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

struct node* insertionatend(struct node* head, int newvalue) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = newvalue;
    newnode->next = NULL;

    if (head == NULL) {
        newnode->prev = NULL;
        return newnode;
    }

    struct node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newnode;
    newnode->prev = temp;

    return head;
}

struct node* insertionatbeginning(struct node* head, int newvalue) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = newvalue;
    newnode->prev = NULL;
    newnode->next = head;

    if (head != NULL) {
        head->prev = newnode;
    }

    return newnode;
}

struct node* insertionatparticular(struct node* head, int newvalue, int loc) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = newvalue;

    if (loc == 1) {
        newnode->next = head;
        newnode->prev = NULL;
        if (head != NULL) {
            head->prev = newnode;
        }
        return newnode;
    }

    struct node* temp = head;

    for (int i = 1; i < loc - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Invalid location for insertion\n");
        free(newnode);
        return head;
    }

    newnode->next = temp->next;
    newnode->prev = temp;

    if (temp->next != NULL) {
        temp->next->prev = newnode;
    }

    temp->next = newnode;

    return head;
}

struct node* deletionatbeginning(struct node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return NULL;
    }

    struct node* temp = head;
    head = head->next;

    if (head != NULL) {
        head->prev = NULL;
    }

    free(temp);
    return head;
}

struct node* deletionatend(struct node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return NULL;
    }

    struct node* temp = head;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    if (temp->prev != NULL) {
        temp->prev->next = NULL;
    } else {
        head = NULL;  // The list is now empty
    }

    free(temp);
    return head;
}

struct node* deletionatparticular(struct node* head, int value) {
    struct node* temp = head;

    while (temp != NULL && temp->data != value) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Value not found in the list\n");
        return head;
    }

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next;  // Updating head if the first node is deleted
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    free(temp);
    return head;
}

int main() {
    struct node* head = NULL;
    char choice = 'Y';

    while (choice == 'Y' || choice == 'y') {
        printf("Enter value to insert in the doubly linked list: ");
        int inputValue;
        scanf("%d", &inputValue);

        head = insertionatend(head, inputValue);

        printf("Do you want to continue adding initial values? (Y/y for yes): ");
        scanf(" %c", &choice);
    }

    if (head != NULL) {
        printf("Initial Doubly Linked List: ");
        traverse(head);

        printf("Choose operation:\n");
        printf("1. Traverse\n");
        printf("2. Insertion\n");
        printf("3. Deletion\n");

        int option;
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Traversing: ");
                traverse(head);
                break;

            case 2:
                printf("What type of insertion do you want to perform: \n");
                printf("a. Insertion at beginning.\n");
                printf("b. Insertion at end.\n");
                printf("c. Insertion at particular location.\n");

                char option1;
                scanf(" %c", &option1);

                switch (option1) {
                    case 'a':
                        printf("Enter value to insert at the beginning: ");
                        int value1;
                        scanf("%d", &value1);
                        head = insertionatbeginning(head, value1);
                        break;

                    case 'b':
                        printf("Enter value to insert at the end: ");
                        int value2;
                        scanf("%d", &value2);
                        head = insertionatend(head, value2);
                        break;

                    case 'c':
                        printf("Enter value to insert: ");
                        int value3;
                        scanf("%d", &value3);
                        printf("Enter location for insertion: ");
                        int location;
                        scanf("%d", &location);
                        head = insertionatparticular(head, value3, location);
                        break;

                    default:
                        printf("Invalid Option.\n");
                }
                break;

            case 3:
                printf("What type of deletion do you want to perform: \n");
                printf("a. Deletion at beginning.\n");
                printf("b. Deletion at end.\n");
                printf("c. Deletion at particular value.\n");

                char option2;
                scanf(" %c", &option2);

                switch (option2) {
                    case 'a':
                        head = deletionatbeginning(head);
                        break;

                    case 'b':
                        head = deletionatend(head);
                        break;

                    case 'c':
                        printf("Enter value to delete: ");
                        int value4;
                        scanf("%d", &value4);
                        head = deletionatparticular(head, value4);
                        break;

                    default:
                        printf("Invalid option\n");
                }
                break;

            default:
                printf("Invalid Option.\n");
        }

        printf("Doubly Linked List: ");
        traverse(head);

        while (head != NULL) {
            struct node* temp = head;
            head = head->next;
            free(temp);
        }
    }

    return 0;
}
