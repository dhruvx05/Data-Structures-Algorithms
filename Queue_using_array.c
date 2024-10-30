#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int queue[MAX_SIZE];
int *front = NULL;
int *rear = NULL;

// Enqueue operation
void enqueue(int value) {
    if (rear == &queue[MAX_SIZE - 1]) {
        printf("Queue Overflow\n");
        return;
    }

    if (front == NULL && rear == NULL) {
        front = rear = queue;
    } 
    else {
        rear++;
    }

    *rear = value;
}

// Dequeue operation
int dequeue() {
    if (front == NULL) {
        printf("Queue Underflow\n");
        return -1;
    }

    int dequeuedvalue = *front;

    if (front == rear) {
        front = rear = NULL;
    } 
    else {
        front++;
    }

    return dequeuedvalue;
}
// Peek operation
int peek() {
    if (front == NULL) {
        printf("Queue is empty\n");
        return -1;
    }
    return *front;
}
int main() {

    char option = 'y';

    while(option == 'Y' || option == 'y') {
        int choice;
        printf("1 for enqueue and 2 for dequeue: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                int element;
                printf("Enter value to enqueue: ");
                scanf("%d", &element);
                enqueue(element);
                break;
            case 2:
                printf("Dequeued element: %d\n", dequeue());
                break;
            default:
                printf("Invalid choice\n");
        }

        printf("Do you want to continue:( y/Y-Yes, n/N-No )");
        scanf(" %c", &option); 
    }

    // Display the queue
    printf("Queue elements:\n");
    if (front != NULL) {
        int *tmp = front;
        while (tmp <= rear) {
            printf("%d\n", *tmp);
            tmp++;
        }
    }
    return 0;
}
