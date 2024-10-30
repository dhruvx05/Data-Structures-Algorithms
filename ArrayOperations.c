#include <stdio.h>
#define MAX_SIZE 10

void traverse(int *array, int size) {
    if (size <= 0) {
        printf("Array is Empty\n");
    } else {
        for (int i = 0; i < size; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
    }
}

void insertion(int *array, int *size, int value, int loc) {
    if (*size >= MAX_SIZE) {
        printf("Array is full. Cannot insert more elements.\n");
    } else if (loc < 0 || loc > *size) {
        printf("Invalid insertion location\n");
    } else {
        // Shifting elements to the right to make space for the new element
        for (int i = *size; i > loc; i--) {
            array[i] = array[i - 1];
        }

        // Insert the new element at the specified location
        array[loc] = value;

        // Update the size of the array
        (*size)++;

        // Print the updated array
        traverse(array, *size);
    }
}

void deletion(int *array, int *size, int loc) {
    if (*size <= 0) {
        printf("Array is already empty\n");
    } else if (loc < 0 || loc >= *size) {
        printf("Invalid deletion location\n");
    } else {
        // Shifting elements to the left to fill the gap
        for (int i = loc; i < *size - 1; i++) {
            array[i] = array[i + 1];
        }

        // Decrement the size of the array
        (*size)--;

        // Print the updated array
        traverse(array, *size);
    }
}

int main() {
    
    printf("My name is Dhruv, SapID:500123606");
    
    int arr[MAX_SIZE];
    int size;
    printf("\nEnter size of array (Max Size: 10): ");
    scanf("%d", &size);

    printf("Enter elements in the array: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);  
    }

    int choice;
    do {
        printf("\n1. Traverse\n2. Insert\n3. Delete\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Array: ");
                traverse(arr, size);
                break;
            case 2:
                {
                    int insertValue, insertLocation;
                    printf("Enter value to insert: ");
                    scanf("%d", &insertValue);
                    printf("Enter location to insert: ");
                    scanf("%d", &insertLocation);
                    insertion(arr, &size, insertValue, insertLocation);
                }
                break;
            case 3:
                {
                    int deleteLocation;
                    printf("Enter location to delete: ");
                    scanf("%d", &deleteLocation);
                    deletion(arr, &size, deleteLocation);
                }
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}
