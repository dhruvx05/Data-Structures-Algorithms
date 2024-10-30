#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
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

    if (newnode == NULL) {
        printf("Memory allocation failed\n");
        return head;
    }

    newnode->data = newvalue;
    newnode->next = NULL;

    if (head == NULL) {
        return newnode;
    }

    struct node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newnode;
    return head;
}

struct node* insertionatbeginning(struct node* head, int newvalue) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));

    if (newnode == NULL) {
        printf("Memory allocation failed\n");
        return head;
    }

    newnode->data = newvalue;
    newnode->next = head;
    return newnode;
}

struct node* insertionatparticular(struct node* head, int newvalue, int loc) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));

    if (newnode == NULL) {
        printf("Memory allocation failed\n");
        return head;
    }

    newnode->data = newvalue;

    if (loc == 1) {
        newnode->next = head;
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
    temp->next = newnode;

    return head;
}

struct node* deletionatbeginning(struct node* head) {
    struct node* temp;

    if (head == NULL) {
        printf("LL is empty\n");
        return head;
    } else {
        temp = head;
        head = temp->next;
        free(temp);
        return head;
    }
}

struct node* deletionatend(struct node* head) {
    struct node* temp;
    struct node* prev = NULL;

    if (head == NULL) {
        printf("LL is empty\n");
        return head;
    } else if (head->next == NULL) {
        temp = head;
        head = NULL;
        free(temp);
        return head;
    } else {
        temp = head;
        while (temp->next != NULL) {
            prev = temp;
            temp = temp->next;
        }
        free(temp);
        prev->next = NULL;
        return head;
    }
}

struct node* deletionatparticular(struct node* head, int value) {
    struct node* temp;
    struct node* prev = NULL;

    if (head == NULL) {
        printf("LL is empty\n");
        return head;
    } else if (head->data == value) {
        temp = head;
        head = temp->next;
        free(temp);
        return head;
    } else {
        temp = head;
        while (temp != NULL && temp->data != value) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            printf("Value not found in the list\n");
            return head;
        }

        prev->next = temp->next;
        free(temp);
        return head;
    }
}

int main() {
    struct node* head = NULL;
    char choice = 'Y';

    while (choice == 'Y' || choice == 'y') {
        printf("Enter value to insert in the linked list: ");
        int inputValue;
        scanf("%d", &inputValue);

        head = insertionatend(head, inputValue);

        printf("Do you want to continue adding initial values? (Y/y for yes): ");
        scanf(" %c", &choice);
    }

    if (head != NULL) {
        printf("Initial Linked List: ");
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
                printf("What type of insertion you want to perform: \n");
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
                printf("What type of deletion you want to perform: \n");
                printf("a. Deletion at beginning.\n");
                printf("b. Deletion at end.\n");
                printf("c. Deletion at particular location.\n");

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
                        int value3;
                        scanf("%d", &value3);
                        head = deletionatparticular(head, value3);
                        break;

                    default:
                        printf("Invalid option\n");
                }
                break;

            default:
                printf("Invalid Option.\n");
        }

        printf("Linked List: ");
        traverse(head);

        while (head != NULL) {
            struct node* temp = head;
            head = head->next;
            free(temp);
        }
    }

    return 0;
}
