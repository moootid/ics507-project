#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include <vector>
#include <string>

void readMatrix(const std::string& filename, int& n, std::vector<std::vector<long>>& A, std::vector<std::vector<long>>& B);
void writeMatrix(const std::string& filename, const std::vector<std::vector<long>>& C);
void generateRandomMatrix(const std::string& filename, int n);
void generateRandomMatrixData(std::vector<std::vector<long>>& A, std::vector<std::vector<long>>& B, int n);
void sequentialMatrixMultiplier(const std::vector<std::vector<long>>& A, const std::vector<std::vector<long>>& B, std::vector<std::vector<long>>& C);
void parallelSequentialMatrixMultiplier(const std::vector<std::vector<long>>& A, const std::vector<std::vector<long>>& B, std::vector<std::vector<long>>& C);
void addMatrices(const std::vector<std::vector<long>>& A, const std::vector<std::vector<long>>& B, std::vector<std::vector<long>>& C);
void subtractMatrices(const std::vector<std::vector<long>>& A, const std::vector<std::vector<long>>& B, std::vector<std::vector<long>>& C);
// void generateRandomMatrix(const string &filename, int n);

#endif // MATRIX_UTILS_H
