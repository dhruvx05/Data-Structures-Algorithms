#include <stdio.h>

struct Item {
    int weight;
    int value;
};

struct Node {
    int level;
    int profit;
    int weight;
    float bound;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

// 1. Backtracking Approach
int knapsackBacktracking(int weights[], int values[], int n, int W) {
    if (n == 0 || W == 0)
        return 0;

    if (weights[n - 1] > W) {
        return knapsackBacktracking(weights, values, n - 1, W);
    } else {
        return max(values[n - 1] + knapsackBacktracking(weights, values, n - 1, W - weights[n - 1]),
                   knapsackBacktracking(weights, values, n - 1, W));
    }
}

// 2. Branch & Bound Approach
float bound(struct Node u, int n, int W, struct Item items[]) {
    if (u.weight >= W) return 0;
    int profit_bound = u.profit;
    int j = u.level + 1;
    int total_weight = u.weight;

    while (j < n && total_weight + items[j].weight <= W) {
        total_weight += items[j].weight;
        profit_bound += items[j].value;
        j++;
    }

    if (j < n) {
        profit_bound += (W - total_weight) * items[j].value / items[j].weight;
    }

    return profit_bound;
}

int knapsackBranchBound(struct Item items[], int n, int W) {
    struct Node u, v;
    u.level = -1;
    u.profit = 0;
    u.weight = 0;
    u.bound = 0.0;

    int max_profit = 0;

    struct Node Q[1000];
    int front = 0, rear = 0;

    u.bound = bound(u, n, W, items);
    Q[rear++] = u;

    while (front < rear) {
        u = Q[front++];

        if (u.level == n - 1)
            continue;

        v.level = u.level + 1;
        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].value;

        if (v.weight <= W && v.profit > max_profit)
            max_profit = v.profit;

        v.bound = bound(v, n, W, items);

        if (v.bound > max_profit)
            Q[rear++] = v;
    }

    return max_profit;
}

// 3. Dynamic Programming Approach
int knapsackDP(int weights[], int values[], int n, int W) {
    int dp[n+1][W+1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i-1] <= w)
                dp[i][w] = max(values[i-1] + dp[i-1][w - weights[i-1]], dp[i-1][w]);
            else
                dp[i][w] = dp[i-1][w];
        }
    }

    return dp[n][W];
}

int main() {
    struct Item items[] = {{2, 3}, {3, 4}, {4, 5}, {5, 6}};
    int W = 5;
    int n = sizeof(items) / sizeof(items[0]);

    // Backtracking Approach
    int resultBacktracking = knapsackBacktracking((int[]){2, 3, 4, 5}, (int[]){3, 4, 5, 6}, n, W);
    printf("Backtracking Maximum value: %d\n", resultBacktracking);

    // Branch & Bound Approach
    int resultBranchBound = knapsackBranchBound(items, n, W);
    printf("Branch & Bound Maximum value: %d\n", resultBranchBound);

    // Dynamic Programming Approach
    int resultDP = knapsackDP((int[]){2, 3, 4, 5}, (int[]){3, 4, 5, 6}, n, W);
    printf("Dynamic Programming Maximum value: %d\n", resultDP);

    return 0;
}
