#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
    struct node* prev;
};

void traverse(struct node* head) {
    if (head == NULL) return;

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

    if (head == NULL) {
        newnode->next = newnode;
        newnode->prev = newnode;
        return newnode;
    }

    struct node* tail = head->prev;

    tail->next = newnode;
    newnode->prev = tail;
    newnode->next = head;
    head->prev = newnode;

    return head;
}

struct node* insertionatbeginning(struct node* head, int newvalue) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = newvalue;

    if (head == NULL) {
        newnode->next = newnode;
        newnode->prev = newnode;
        return newnode;
    }

    struct node* tail = head->prev;

    newnode->next = head;
    newnode->prev = tail;
    head->prev = newnode;
    tail->next = newnode;

    return newnode;
}

struct node* insertionatparticular(struct node* head, int newvalue, int loc) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = newvalue;

    if (loc == 1) {
        return insertionatbeginning(head, newvalue);
    }

    struct node* temp = head;

    for (int i = 1; i < loc - 1 && temp != head; i++) {
        temp = temp->next;
    }

    if (temp == head && loc != 1) {
        printf("Invalid location for insertion\n");
        free(newnode);
        return head;
    }

    newnode->next = temp->next;
    newnode->prev = temp;

    if (temp->next != head) {
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

    struct node* tail = head->prev;

    if (head == tail) {
        free(head);
        return NULL;
    }

    struct node* new_head = head->next;
    tail->next = new_head;
    new_head->prev = tail;
    free(head);
    
    return new_head;
}

struct node* deletionatend(struct node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return NULL;
    }

    struct node* tail = head->prev;

    if (head == tail) {
        free(head);
        return NULL;
    }

    struct node* new_tail = tail->prev;
    new_tail->next = head;
    head->prev = new_tail;
    free(tail);
    
    return head;
}

struct node* deletionatparticular(struct node* head, int value) {
    if (head == NULL) {
        printf("List is empty\n");
        return NULL;
    }

    struct node* temp = head;

    do {
        if (temp->data == value) {
            if (temp->next == head && temp->prev == head) {
                free(temp);
                return NULL; // List becomes empty
            }

            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;

            if (temp == head) {
                head = temp->next; // Update head if necessary
            }

            free(temp);
            return head;
        }
        temp = temp->next;
    } while (temp != head);

    printf("Value not found in the list\n");
    return head;
}

int main() {
    struct node* head = NULL;
    char choice = 'Y';

    while (choice == 'Y' || choice == 'y') {
        printf("Enter value to insert in the circular doubly linked list: ");
        int inputValue;
        scanf("%d", &inputValue);

        head = insertionatend(head, inputValue);

        printf("Do you want to continue adding initial values? (Y/y for yes): ");
        scanf(" %c", &choice);
    }

    if (head != NULL) {
        printf("Initial Circular Doubly Linked List: ");
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

        printf("Circular Doubly Linked List: ");
        traverse(head);

        while (head != NULL) {
            struct node* temp = head;
            head = head->next;
            free(temp);
            if (head == temp) break; // Avoid infinite loop if it was the last node
        }
    }

    return 0;
}
