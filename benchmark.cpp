#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include "matrix_utils.h"

using namespace std;

// Function prototypes for the five algorithms
void sequentialMatrixMultiplier(const vector<vector<long>> &A, const vector<vector<long>> &B, vector<vector<long>> &C);
void parallelSequentialMatrixMultiplier(const vector<vector<long>> &A, const vector<vector<long>> &B, vector<vector<long>> &C);
void multiplyMatrices(const vector<vector<long>> &A, const vector<vector<long>> &B, vector<vector<long>> &C);
void parallelMultiplyMatrices(const vector<vector<long>> &A, const vector<vector<long>> &B, vector<vector<long>> &C);
void strassenMultiply(const vector<vector<long>> &A, const vector<vector<long>> &B, vector<vector<long>> &C);

const int NUM_RUNS = 3;
const string INPUT_FILENAME = "input.txt";
const int MATRIX_SIZE = 128;
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
    string outputFilename = INPUT_FILENAME + "_" + to_string(n) + "_output_" + method + ".txt";
    writeMatrix(outputFilename, C);

    // Write the time taken to a file
    string infoFilename = INPUT_FILENAME + "_" + to_string(n) + "_info_" + method + ".txt";
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
    generateRandomMatrix("input.txt", MATRIX_SIZE); // Regenerate random data for every run
    vector<vector<long>> A, B;
    int n;

    // Read matrices from input.txt
    readMatrix(INPUT_FILENAME, n, A, B);

    // Benchmark each matrix multiplication algorithm
    double seqTime = benchmark(sequentialMatrixMultiplier, A, B, "Sequential", n);
    double parSeqTime = benchmark(parallelSequentialMatrixMultiplier, A, B, "SequentialP", n);
    double divConqTime = benchmark(multiplyMatrices, A, B, "StraightDivAndConq", n);
    double parDivConqTime = benchmark(parallelMultiplyMatrices, A, B, "StraightDivAndConqP", n);
    double strassenTime = benchmark(strassenMultiply, A, B, "StrassenDivAndConq", n);

    // Write benchmark summary to file
    ofstream resultsFile("benchmark_results.txt");
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
