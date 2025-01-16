#include <stdio.h>
#include <limits.h>

// Function to print the optimal parenthesis structure
void printOptimalParenthesis(int i, int j, int n, int bracket[n][n], char *name) {
    if (i == j) {
        printf("%c", (*name)++);
        return;
    }
    printf("(");
    printOptimalParenthesis(i, bracket[i][j], n, bracket, name);
    printOptimalParenthesis(bracket[i][j] + 1, j, n, bracket, name);
    printf(")");
}

// Matrix Chain Multiplication function
void matrixChainMultiplication(int p[], int n) {
    int dp[n][n];
    int bracket[n][n];  // To store optimal split points

    // Initialize the diagonal of dp table to 0
    for (int i = 1; i < n; i++) dp[i][i] = 0;

    // Fill dp table
    for (int length = 2; length < n; length++) { // Chain length
        for (int i = 1; i < n - length + 1; i++) {
            int j = i + length - 1;
            dp[i][j] = INT_MAX;

            // Find the minimum cost for current subproblem
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    bracket[i][j] = k;
                }
            }
        }
    }

    printf("Minimum number of multiplications is: %d\n", dp[1][n - 1]);

    char name = 'A';
    printf("Optimal Parenthesization is: ");
    printOptimalParenthesis(1, n - 1, n, bracket, &name);
    printf("\n");
}

int main() {
    // Matrices: A(40x20), B(20x30), C(30x10), D(10x30)
    int dimensions[] = {40, 20, 30, 10, 30};
    int n = sizeof(dimensions) / sizeof(dimensions[0]);

    matrixChainMultiplication(dimensions, n);

    return 0;
}
