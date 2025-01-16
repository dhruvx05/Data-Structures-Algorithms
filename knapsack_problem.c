#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int value;
    int weight;
    float ratio;
} Item;

// Comparison function for sorting items by value/weight ratio
int compare(const void* a, const void* b) {
    float r1 = ((Item*)a)->ratio;
    float r2 = ((Item*)b)->ratio;
    if (r1 < r2) return 1;
    else if (r1 > r2) return -1;
    return 0;
}

// Greedy Knapsack approach
void greedyKnapsack(Item items[], int n, int capacity) {
    qsort(items, n, sizeof(Item), compare);  // Sort items by value/weight ratio
    int totalValue = 0;
    int totalWeight = 0;

    for (int i = 0; i < n; i++) {
        if (totalWeight + items[i].weight <= capacity) {
            totalWeight += items[i].weight;
            totalValue += items[i].value;
        }
    }

    printf("\nGreedy Approach:\n");
    printf("Total Value: %d\n", totalValue);
    printf("Total Weight: %d\n", totalWeight);
}

// Dynamic Programming Knapsack approach
void knapsackDP(int values[], int weights[], int n, int capacity) {
    int dp[n+1][capacity+1];

    // Initialize DP table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i-1] <= w)
                dp[i][w] = (values[i-1] + dp[i-1][w - weights[i-1]] > dp[i-1][w]) ? 
                           (values[i-1] + dp[i-1][w - weights[i-1]]) : dp[i-1][w];
            else
                dp[i][w] = dp[i-1][w];
        }
    }

    printf("\nDynamic Programming Approach:\n");
    printf("Maximum Value: %d\n", dp[n][capacity]);
}

int main() {
    // Sample items: value, weight
    Item items[] = {
        {60, 10, 6.0},
        {100, 20, 5.0},
        {120, 30, 4.0}
    };

    int n = sizeof(items) / sizeof(items[0]);
    int capacity = 50;

    // Calculate value-to-weight ratio for each item (for greedy approach)
    for (int i = 0; i < n; i++) {
        items[i].ratio = (float)items[i].value / items[i].weight;
    }

    // Greedy Approach
    greedyKnapsack(items, n, capacity);

    // Dynamic Programming Approach
    int values[] = {60, 100, 120};  // Values of the items
    int weights[] = {10, 20, 30};  // Weights of the items
    knapsackDP(values, weights, n, capacity);

    return 0;
}
