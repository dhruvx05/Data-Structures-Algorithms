#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Merge function for Merge Sort
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }
}

// Merge Sort function
void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Partition function for Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}

// Quick Sort function
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

int main() {
    // Array sizes to test
    int array_sizes[] = {100, 1000, 10000, 50000};
    int number_of_sizes = sizeof(array_sizes) / sizeof(array_sizes[0]);

    // Seed the random number generator
    srand(time(0));

    for (int i = 0; i < number_of_sizes; i++) {
        int size = array_sizes[i];
        int *arr_merge = (int *)malloc(size * sizeof(int));
        int *arr_quick = (int *)malloc(size * sizeof(int));

        // Generate random elements for both arrays
        for (int j = 0; j < size; j++) {
            int random_number = rand() % 100000;
            arr_merge[j] = random_number;
            arr_quick[j] = random_number;
        }

        // Measure time for Merge Sort
        clock_t start_merge = clock();
        merge_sort(arr_merge, 0, size - 1);
        clock_t end_merge = clock();
        double time_merge = (double)(end_merge - start_merge) / CLOCKS_PER_SEC;

        // Measure time for Quick Sort
        clock_t start_quick = clock();
        quick_sort(arr_quick, 0, size - 1);
        clock_t end_quick = clock();
        double time_quick = (double)(end_quick - start_quick) / CLOCKS_PER_SEC;

        printf("Array Size: %d\n", size);
        printf("Merge Sort Time: %f seconds\n", time_merge);
        printf("Quick Sort Time: %f seconds\n", time_quick);
        printf("-----------------------------\n");

        free(arr_merge);
        free(arr_quick);
    }

    return 0;
