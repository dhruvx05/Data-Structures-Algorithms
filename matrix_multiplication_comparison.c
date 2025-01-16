#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N1 8
#define N2 16
#define N3 128

// Traditional matrix multiplication
void traditionalMultiply(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Matrix addition
void add(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Matrix subtraction
void subtract(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Strassen's matrix multiplication
void strassen(int n, int A[n][n], int B[n][n], int C[n][n]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;
    int A11[newSize][newSize], A12[newSize][newSize], A21[newSize][newSize], A22[newSize][newSize];
    int B11[newSize][newSize], B12[newSize][newSize], B21[newSize][newSize], B22[newSize][newSize];
    int C11[newSize][newSize], C12[newSize][newSize], C21[newSize][newSize], C22[newSize][newSize];
    int M1[newSize][newSize], M2[newSize][newSize], M3[newSize][newSize], M4[newSize][newSize];
    int M5[newSize][newSize], M6[newSize][newSize], M7[newSize][newSize];
    int temp1[newSize][newSize], temp2[newSize][newSize];

    // Dividing matrices into submatrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calculating M1 to M7
    add(newSize, A11, A22, temp1);
    add(newSize, B11, B22, temp2);
    strassen(newSize, temp1, temp2, M1);

    add(newSize, A21, A22, temp1);
    strassen(newSize, temp1, B11, M2);

    subtract(newSize, B12, B22, temp2);
    strassen(newSize, A11, temp2, M3);

    subtract(newSize, B21, B11, temp2);
    strassen(newSize, A22, temp2, M4);

    add(newSize, A11, A12, temp1);
    strassen(newSize, temp1, B22, M5);

    subtract(newSize, A21, A11, temp1);
    add(newSize, B11, B12, temp2);
    strassen(newSize, temp1, temp2, M6);

    subtract(newSize, A12, A22, temp1);
    add(newSize, B21, B22, temp2);
    strassen(newSize, temp1, temp2, M7);

    // Calculating C11, C12, C21, C22
    add(newSize, M1, M4, temp1);
    subtract(newSize, temp1, M5, temp2);
    add(newSize, temp2, M7, C11);

    add(newSize, M3, M5, C12);
    add(newSize, M2, M4, C21);

    add(newSize, M1, M3, temp1);
    subtract(newSize, temp1, M2, temp2);
    add(newSize, temp2, M6, C22);

    // Combining submatrices into result matrix C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
}

// Function to initialize matrices with random values
void initializeMatrix(int n, int A[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = rand() % 10; // Random values between 0-9
}

int main() {
    srand(time(0)); // Seed for random number generation

    int sizes[] = {N1, N2, N3};
    for (int k = 0; k < 3; k++) {
        int N = sizes[k];

        // Dynamically allocate matrices
        int A[N][N], B[N][N], C[N][N], D[N][N]; 

        // Initialize matrices with random values
        initializeMatrix(N, A);
        initializeMatrix(N, B);

        clock_t start, end;
        double cpu_time_used;

        // Traditional method
        start = clock();
        traditionalMultiply(N, A, B, C);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Traditional method time for %dx%d: %f seconds\n", N, N, cpu_time_used);

        // Strassen's method
        start = clock();
        strassen(N, A, B, D);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Strassen's method time for %dx%d: %f seconds\n", N, N, cpu_time_used);
    }

    return 0;
}
