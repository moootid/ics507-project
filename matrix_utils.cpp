#include "matrix_utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>



using namespace std;

void readMatrix(const string &filename, int &n, vector<vector<long>> &A, vector<vector<long>> &B)
{
    ifstream infile(filename);
    if (!infile)
    {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }
    infile >> n;
    A.resize(n, vector<long>(n));
    B.resize(n, vector<long>(n));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            infile >> A[i][j];
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            infile >> B[i][j];
        }
    }
}

void writeMatrix(const string &filename, const vector<vector<long>> &C)
{
    ofstream outfile(filename);
    if (!outfile)
    {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }
    int n = C.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            outfile << C[i][j] << " ";
        }
        outfile << endl;
    }
}

// void generateRandomMatrix(const string &filename, int n)
// {
//     ofstream outfile(filename);
//     if (!outfile)
//     {
//         cerr << "Error opening file: " << filename << endl;
//         exit(1);
//     }
//     srand(time(0));
//     outfile << n << endl;
//     for (int i = 0; i < 2 * n * n; ++i)
//     {
//         long value = (rand() % 19) - 9;
//         outfile << value << " ";
//         if ((i + 1) % n == 0)
//             outfile << endl;
//     }
// }

void generateRandomMatrixData(vector<vector<long>> &A, vector<vector<long>> &B, int n)
{
    srand(time(0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            A[i][j] = (rand() % 19) - 9;
            B[i][j] = (rand() % 19) - 9;
        }
    }
}

void addMatrices(const vector<vector<long>> &A, const vector<vector<long>> &B, vector<vector<long>> &C)
{
    int n = A.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtractMatrices(const vector<vector<long>> &A, const vector<vector<long>> &B, vector<vector<long>> &C)
{
    int n = A.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void sequentialMatrixMultiplier(const std::vector<std::vector<long>> &A, const std::vector<std::vector<long>> &B, std::vector<std::vector<long>> &C)
{
    int n = A.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            C[i][j] = 0;
            for (int k = 0; k < n; ++k)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
void parallelSequentialMatrixMultiplier(const std::vector<std::vector<long>> &A, const std::vector<std::vector<long>> &B, std::vector<std::vector<long>> &C)
{
    int n = A.size();
#pragma omp parallel for
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            C[i][j] = 0;
            for (int k = 0; k < n; ++k)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void generateRandomMatrix(const string &filename, int n)
{
    ofstream outfile(filename);
    if (!outfile)
    {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }
    srand(time(0));
    outfile << n << endl;
    for (int i = 0; i < 2 * n * n; ++i)
    {
        long value = (rand() % 19) - 9;
        outfile << value << " ";
        if ((i + 1) % n == 0)
            outfile << endl;
    }
    outfile.close();
}