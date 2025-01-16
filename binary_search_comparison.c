#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binary_search_iterative(int array[], int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int middle = (left + right) / 2;
        if (array[middle] == target)
            return middle;
        else if (array[middle] < target)
            left = middle + 1;
        else
            right = middle - 1;
    }
    return -1;
}

int binary_search_recursive(int array[], int left, int right, int target) {
    if (right >= left) {
        int middle = (left + right) / 2;
        if (array[middle] == target)
            return middle;
        else if (array[middle] > target)
            return binary_search_recursive(array, left, middle - 1, target);
        else
            return binary_search_recursive(array, middle + 1, right, target);
    }
    return -1;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int array_sizes[] = {100, 1000, 100000};
    int number_of_sizes = sizeof(array_sizes) / sizeof(array_sizes[0]);

    for (int i = 0; i < number_of_sizes; i++) {
        int size = array_sizes[i];
        int *array = (int *)malloc(size * sizeof(int));

        // Initialize array with even numbers
        for (int j = 0; j < size; j++) {
            array[j] = j * 2;  
        }

        // Sort the array (though it is already sorted, this step is kept in case of future changes)
        qsort(array, size, sizeof(int), compare);

        int target = array[size / 2];

        clock_t start_time_iterative = clock();
        binary_search_iterative(array, size, target);
        clock_t end_time_iterative = clock();
        double time_taken_iterative = (double)(end_time_iterative - start_time_iterative) / CLOCKS_PER_SEC;

        clock_t start_time_recursive = clock();
        binary_search_recursive(array, 0, size - 1, target);
        clock_t end_time_recursive = clock();
        double time_taken_recursive = (double)(end_time_recursive - start_time_recursive) / CLOCKS_PER_SEC;

        printf("Array Size: %d\n", size);
        printf("Iterative Binary Search Time: %f seconds\n", time_taken_iterative);
        printf("Recursive Binary Search Time: %f seconds\n", time_taken_recursive);
        printf("\n");

        free(array);
    }

    return 0;
}
