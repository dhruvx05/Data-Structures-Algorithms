#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

void traverse(struct node* head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    struct node* temp = head;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

struct node* insertionatend(struct node* head, int newvalue) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = newvalue;
    newnode->next = head; // Points to head initially

    if (head == NULL) {
        newnode->next = newnode; // Point to itself
        return newnode;
    }

    struct node* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }

    temp->next = newnode;
    return head;
}

struct node* insertionatbeginning(struct node* head, int newvalue) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = newvalue;

    if (head == NULL) {
        newnode->next = newnode; // Point to itself
        return newnode;
    }

    struct node* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }

    temp->next = newnode;
    newnode->next = head; // New node points to head
    return newnode;
}

struct node* insertionatparticular(struct node* head, int newvalue, int loc) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = newvalue;

    if (loc == 1) {
        return insertionatbeginning(head, newvalue);
    }

    if (head == NULL) {
        printf("Invalid location for insertion\n");
        return head;
    }

    struct node* temp = head;
    for (int i = 1; i < loc - 1 && temp->next != head; i++) {
        temp = temp->next;
    }

    if (temp->next == head && loc > 1) {
        printf("Invalid location for insertion\n");
        free(newnode);
        return head;
    }

    newnode->next = temp->next;
    temp->next = newnode;

    return head;
}

struct node* deletionatbeginning(struct node* head) {
    if (head == NULL) {
        printf("LL is empty\n");
        return head;
    }

    struct node* temp = head;

    if (head->next == head) { // Only one node
        free(head);
        return NULL;
    }

    struct node* last = head;
    while (last->next != head) {
        last = last->next;
    }

    last->next = head->next; // Last node points to second node
    free(head);
    return last->next;
}

struct node* deletionatend(struct node* head) {
    if (head == NULL) {
        printf("LL is empty\n");
        return head;
    }

    struct node* temp = head;

    if (head->next == head) { // Only one node
        free(head);
        return NULL;
    }

    struct node* prev = NULL;
    while (temp->next != head) {
        prev = temp;
        temp = temp->next;
    }

    prev->next = head; // Previous node points to head
    free(temp);
    return head;
}

struct node* deletionatparticular(struct node* head, int value) {
    if (head == NULL) {
        printf("LL is empty\n");
        return head;
    }

    struct node* temp = head;
    struct node* prev = NULL;

    if (head->data == value) {
        return deletionatbeginning(head);
    }

    while (temp->next != head && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    if (temp->data != value) {
        printf("Value not found in the list\n");
        return head;
    }

    prev->next = temp->next; // Bypass the node to delete
    free(temp);
    return head;
}

int main() {
    struct node* head = NULL;
    char choice = 'Y';

    while (choice == 'Y' || choice == 'y') {
        printf("Enter value to insert in the circular linked list: ");
        int inputValue;
        scanf("%d", &inputValue);

        head = insertionatend(head, inputValue);

        printf("Do you want to continue adding initial values? (Y/y for yes): ");
        scanf(" %c", &choice);
    }

    if (head != NULL) {
        printf("Circular Linked List: ");
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

        printf("Circular Linked List: ");
        traverse(head);
    }

    // Clean up memory
    while (head != NULL) {
        struct node* temp = head;
        if (head->next == head) { // Only one node
            free(head);
            break;
        }

        struct node* nextNode = head->next;
        while (nextNode != head) {
            struct node* toFree = nextNode;
            nextNode = nextNode->next;
            free(toFree);
        }
        free(head);
        break; // To exit the loop after freeing all nodes
    }

    return 0;
}
