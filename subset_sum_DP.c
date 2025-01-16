#include <stdio.h>
#include <stdbool.h>

bool isSubsetSum(int set[], int n, int sum) {
    // Create a 2D array dp[][] where dp[i][j] will be true if sum j is possible with the first i items
    bool dp[n+1][sum+1];

    // If sum is 0, answer is true (empty subset)
    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;
    }

    // Fill the subset sum table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            // If current element is greater than the sum, we ignore it
            if (set[i-1] > j) {
                dp[i][j] = dp[i-1][j];
            } else {
                // Else, check if sum can be achieved by including or excluding the current element
                dp[i][j] = dp[i-1][j] || dp[i-1][j - set[i-1]];
            }
        }
    }

    return dp[n][sum];
}

int main() {
    int set[] = {3, 34, 4, 12, 5, 2};  // Set of numbers
    int sum = 9;  // Target sum
    int n = sizeof(set) / sizeof(set[0]);

    if (isSubsetSum(set, n, sum)) {
        printf("Subset with sum %d found.\n", sum);
    } else {
        printf("No subset with sum %d found.\n", sum);
    }

    return 0;
}
