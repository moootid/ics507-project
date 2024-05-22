#!/bin/bash

echo "Compiling and running benchmark..."

g++ -c matrix_utils.cpp -fopenmp
g++ -c sequential_multiply.cpp
g++ -c parallel_sequential_multiply.cpp -fopenmp
g++ -c divide_conquer_multiply.cpp
g++ -c parallel_divide_conquer_multiply.cpp -fopenmp
g++ -c strassen_multiply.cpp
g++ -o benchmark benchmark.cpp matrix_utils.o sequential_multiply.o parallel_sequential_multiply.o divide_conquer_multiply.o parallel_divide_conquer_multiply.o strassen_multiply.o -fopenmp
./benchmark

echo "Benchmark completed. Check benchmark_results.txt for summary."