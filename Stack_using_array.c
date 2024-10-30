#include <stdio.h>
#define MAX_SIZE 100

int stack[MAX_SIZE]; 
int top = -1; 

// Push operation
void push(int value) {
    if (top == MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = value;
}

// Pop operation
int pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        return -1; 
    }
    return stack[top--];
}

// Peek operation
int peek() {
    if (top == -1) {
        printf("Stack is empty\n");
        return -1; // indicating empty stack
    }
    return stack[top];
}

int main() {

    char option = 'y';

    while(option == 'Y' || option == 'y') {
        int choice;
        printf("1 for push and 2 for pop: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                int element;
                printf("Enter value to push: ");
                scanf("%d", &element);
                push(element);
                break;
            case 2:
                printf("Popped element: %d\n", pop());
                break;
            default:
                printf("Invalid choice\n");
        }

        printf("Do you want to continue:( y/Y-Yes, n/N-No )");
        scanf(" %c", &option); 
    }

    // Display the stack
    printf("Stack contents:\n");
    for (int i = top; i >= 0; i--) {
        printf("%d\n", stack[i]);
    }

    return 0;
}
