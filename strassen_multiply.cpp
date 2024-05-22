#include <vector>
#include "matrix_utils.h"

const int THRESHOLD = 64; // Threshold for switching to iterative multiplication





void strassenMultiply(const std::vector<std::vector<long>>& A, const std::vector<std::vector<long>>& B, std::vector<std::vector<long>>& C) {
    int n = A.size();
    if (n <= THRESHOLD) {
        sequentialMatrixMultiplier(A, B, C);
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
        std::vector<std::vector<long>> M1(newSize, std::vector<long>(newSize));
        std::vector<std::vector<long>> M2(newSize, std::vector<long>(newSize));
        std::vector<std::vector<long>> M3(newSize, std::vector<long>(newSize));
        std::vector<std::vector<long>> M4(newSize, std::vector<long>(newSize));
        std::vector<std::vector<long>> M5(newSize, std::vector<long>(newSize));
        std::vector<std::vector<long>> M6(newSize, std::vector<long>(newSize));
        std::vector<std::vector<long>> M7(newSize, std::vector<long>(newSize));
        std::vector<std::vector<long>> tempA(newSize, std::vector<long>(newSize));
        std::vector<std::vector<long>> tempB(newSize, std::vector<long>(newSize));

        // Divide matrices into submatrices
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

        // Compute M1 = (A11 + A22) * (B11 + B22)
        addMatrices(A11, A22, tempA);
        addMatrices(B11, B22, tempB);
        strassenMultiply(tempA, tempB, M1);

        // Compute M2 = (A21 + A22) * B11
        addMatrices(A21, A22, tempA);
        strassenMultiply(tempA, B11, M2);

        // Compute M3 = A11 * (B12 - B22)
        subtractMatrices(B12, B22, tempB);
        strassenMultiply(A11, tempB, M3);

        // Compute M4 = A22 * (B21 - B11)
        subtractMatrices(B21, B11, tempB);
        strassenMultiply(A22, tempB, M4);

        // Compute M5 = (A11 + A12) * B22
        addMatrices(A11, A12, tempA);
        strassenMultiply(tempA, B22, M5);

        // Compute M6 = (A21 - A11) * (B11 + B12)
        subtractMatrices(A21, A11, tempA);
        addMatrices(B11, B12, tempB);
        strassenMultiply(tempA, tempB, M6);

        // Compute M7 = (A12 - A22) * (B21 + B22)
        subtractMatrices(A12, A22, tempA);
        addMatrices(B21, B22, tempB);
        strassenMultiply(tempA, tempB, M7);

        // Compute C11 = M1 + M4 - M5 + M7
        addMatrices(M1, M4, tempA);
        subtractMatrices(tempA, M5, tempB);
        addMatrices(tempB, M7, C11);

        // Compute C12 = M3 + M5
        addMatrices(M3, M5, C12);

        // Compute C21 = M2 + M4
        addMatrices(M2, M4, C21);

        // Compute C22 = M1 - M2 + M3 + M6
        subtractMatrices(M1, M2, tempA);
        addMatrices(tempA, M3, tempB);
        addMatrices(tempB, M6, C22);

        // Combine submatrices into the result matrix
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
