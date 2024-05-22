#include <vector>
#include <omp.h>
#include "matrix_utils.h"

const int THRESHOLD = 64; // Threshold for switching to iterative multiplication

void parallelMultiplyMatrices(const std::vector<std::vector<long>>& A, const std::vector<std::vector<long>>& B, std::vector<std::vector<long>>& C) {
    int n = A.size();
    if (n <= THRESHOLD) {
        parallelSequentialMatrixMultiplier(A, B, C);
    } else {
        int newSize = n / 2;
        std::vector<std::vector<long>> A11(newSize, std::vector<long>(newSize));
        std::vector<std::vector<long>> A12(newSize, std::vector<long>(newSize));
        std::vector<std::vector<long>> A21(newSize, std::vector<long>(newSize));
        std::vector<std::vector<long>> A22(newSize, std::vector<long>(newSize));
        std::vector<std::vector<long>> B11(newSize, std::vector<long>(newSize));
        std::vector<std::vector<long>> B12(newSize, std::vector<long>(newSize));
        std::vector<std::vector<long>> B21(newSize, std::vector<long>(newSize));
        std::vector<std::vector<long>> B22(newSize, std::vector<long>(newSize));
        std::vector<std::vector<long>> C11(newSize, std::vector<long>(newSize));
        std::vector<std::vector<long>> C12(newSize, std::vector<long>(newSize));
        std::vector<std::vector<long>> C21(newSize, std::vector<long>(newSize));
        std::vector<std::vector<long>> C22(newSize, std::vector<long>(newSize));
        std::vector<std::vector<long>> temp1(newSize, std::vector<long>(newSize));
        std::vector<std::vector<long>> temp2(newSize, std::vector<long>(newSize));

        // Divide matrices into submatrices
        #pragma omp parallel for collapse(2)
        for (int i = 0; i < newSize; ++i) {
            for (int j = 0; j < newSize; ++j) {
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

        // Compute C11 = A11*B11 + A12*B21
        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMultiplyMatrices(A11, B11, temp1);
            #pragma omp section
            parallelMultiplyMatrices(A12, B21, temp2);
        }
        addMatrices(temp1, temp2, C11);

        // Compute C12 = A11*B12 + A12*B22
        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMultiplyMatrices(A11, B12, temp1);
            #pragma omp section
            parallelMultiplyMatrices(A12, B22, temp2);
        }
        addMatrices(temp1, temp2, C12);

        // Compute C21 = A21*B11 + A22*B21
        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMultiplyMatrices(A21, B11, temp1);
            #pragma omp section
            parallelMultiplyMatrices(A22, B21, temp2);
        }
        addMatrices(temp1, temp2, C21);

        // Compute C22 = A21*B12 + A22*B22
        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMultiplyMatrices(A21, B12, temp1);
            #pragma omp section
            parallelMultiplyMatrices(A22, B22, temp2);
        }
        addMatrices(temp1, temp2, C22);

        // Combine submatrices into the result matrix
        #pragma omp parallel for collapse(2)
        for (int i = 0; i < newSize; ++i) {
            for (int j = 0; j < newSize; ++j) {
                C[i][j] = C11[i][j];
                C[i][j + newSize] = C12[i][j];
                C[i + newSize][j] = C21[i][j];
                C[i + newSize][j + newSize] = C22[i][j];
            }
        }
    }
}
