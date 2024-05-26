#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include "matrix_utils.h"
#include <cmath>

using namespace std;

// Function prototypes for the five algorithms
void sequentialMatrixMultiplier(const vector<vector<long>> &A, const vector<vector<long>> &B, vector<vector<long>> &C);
void parallelSequentialMatrixMultiplier(const vector<vector<long>> &A, const vector<vector<long>> &B, vector<vector<long>> &C);
void multiplyMatrices(const vector<vector<long>> &A, const vector<vector<long>> &B, vector<vector<long>> &C);
void parallelMultiplyMatrices(const vector<vector<long>> &A, const vector<vector<long>> &B, vector<vector<long>> &C);
void strassenMultiply(const vector<vector<long>> &A, const vector<vector<long>> &B, vector<vector<long>> &C);

const string INPUT_FILENAME = "input.txt";
int NUM_RUNS = 1;
int MATRIX_SIZE = pow(2, 9) ;

double benchmark(void (*matrixMultiply)(const vector<vector<long>> &, const vector<vector<long>> &, vector<vector<long>> &), vector<vector<long>> &A, vector<vector<long>> &B, const string &method, int n)
{
    double totalTime = 0.0;
    vector<vector<long>> C(n, vector<long>(n, 0));

    for (int i = 0; i < NUM_RUNS; ++i)
    {
        // generateRandomMatrixData(A, B, n); // Regenerate random data for every run
        generateRandomMatrix("input.txt", MATRIX_SIZE); // Regenerate random data for every run
        auto start = chrono::high_resolution_clock::now();
        matrixMultiply(A, B, C);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        totalTime += duration.count();
    }

    // Write the result matrix to a file
    string outputFilename = "test_" + to_string(n) + "_output_" + method + ".txt";
    writeMatrix(outputFilename, C);

    // Write the time taken to a file
    string infoFilename = "test_" + to_string(n) + "_info_" + method + ".txt";
    ofstream infoFile(infoFilename);
    if (infoFile.is_open())
    {
        infoFile << "Average time taken (seconds): " << totalTime / NUM_RUNS << endl;
        infoFile.close();
    }
    else
    {
        cerr << "Unable to open " << infoFilename << " for writing." << endl;
    }

    return totalTime / NUM_RUNS;
}

int main()
{

    vector<vector<long>> A, B;
    int n;

    generateRandomMatrix("input.txt", MATRIX_SIZE); // Regenerate random data for every run
    // Read matrices from input.txt
    readMatrix(INPUT_FILENAME, n, A, B);
    // Benchmark each matrix multiplication algorithm
    printf("Benchmarking for matrix size %d\n", MATRIX_SIZE);
    double seqTime = benchmark(sequentialMatrixMultiplier, A, B, "Sequential", n);
    printf("Sequential Matrix Multiplication: %f seconds\n", seqTime);
    double parSeqTime = benchmark(parallelSequentialMatrixMultiplier, A, B, "SequentialP", n);
    printf("Parallelized Sequential Matrix Multiplication: %f seconds\n", parSeqTime);
    double divConqTime = benchmark(multiplyMatrices, A, B, "StraightDivAndConq", n);
    printf("Divide and Conquer Matrix Multiplication: %f seconds\n", divConqTime);
    double parDivConqTime = benchmark(parallelMultiplyMatrices, A, B, "StraightDivAndConqP", n);
    printf("Parallelized Divide and Conquer Matrix Multiplication: %f seconds\n", parDivConqTime);
    double strassenTime = benchmark(strassenMultiply, A, B, "StrassenDivAndConq", n);
    printf("Strassen's Matrix Multiplication: %f seconds\n", strassenTime);

    // Write benchmark summary to file
    ofstream resultsFile("benchmark_results_" + to_string(n) + ".txt");
    if (resultsFile.is_open())
    {
        resultsFile << fixed << setprecision(6);
        resultsFile << "Average execution time over " << NUM_RUNS << " runs:" << endl;
        resultsFile << "Sequential Matrix Multiplication: " << seqTime << " seconds" << endl;
        resultsFile << "Parallelized Sequential Matrix Multiplication: " << parSeqTime << " seconds" << endl;
        resultsFile << "Divide and Conquer Matrix Multiplication: " << divConqTime << " seconds" << endl;
        resultsFile << "Parallelized Divide and Conquer Matrix Multiplication: " << parDivConqTime << " seconds" << endl;
        resultsFile << "Strassen's Matrix Multiplication: " << strassenTime << " seconds" << endl;
        resultsFile.close();
    }
    else
    {
        cerr << "Unable to open benchmark_results.txt for writing." << endl;
    }

    return 0;
}
