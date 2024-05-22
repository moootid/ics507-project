#include <vector>
#include <omp.h>
#include "matrix_utils.h"

void parallelSequentialMatrixMultiply(const std::vector<std::vector<long>>& A, const std::vector<std::vector<long>>& B, std::vector<std::vector<long>>& C) {
    int n = A.size();
    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
