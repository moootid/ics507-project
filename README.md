# Matrix Multiplication Algorithms Project

This project implements and benchmarks five different matrix multiplication algorithms:

1. Sequential Matrix Multiplication
2. Parallelized Matrix Multiplication
3. Divide and Conquer Matrix Multiplication
4. Parallelized Divide and Conquer Matrix Multiplication
5. Strassen's Matrix Multiplication

The project includes scripts and code to generate input matrices, execute each algorithm, and benchmark their performance across different matrix sizes.

## Project Source Code

- `generate_input.cpp`: Generates a random input matrix file `input.txt`.
- `matrix_utils.h` / `matrix_utils.cpp`: Utility functions for matrix operations and file I/O.
- `sequential_multiply.cpp`: Sequential matrix multiplication implementation.
- `parallel_sequential_multiply.cpp`: Parallelized matrix multiplication implementation.
- `divide_conquer_multiply.cpp`: Sequential divide and conquer matrix multiplication implementation.
- `parallel_divide_conquer_multiply.cpp`: Parallelized divide and conquer matrix multiplication implementation.
- `strassen_multiply.cpp`: Strassen's matrix multiplication implementation.
- `benchmark.cpp`: Benchmarking code to run and time each algorithm.
- `build_run.sh`: Shell script to compile and run all the programs and benchmark tests.

## Requirements

- g++ (with OpenMP support)
- Make sure you have the necessary permissions to execute shell scripts
- This code has been tested on linux (WSL Ubuntu)

## How to Run the System

1. **Clone the repository** (if not done already):
   ```sh
   git clone <repository_url>
   cd <repository_directory>
   ```
2. **Excute the shell file** (if not done already):
   ```sh
   ./src/build_run.sh
   ```

## Output Files

- `input.txt`: The generated input matrix file.
- `input_<size>_output_<method>.txt`: Output matrix files for each method.
- `input_<size>_info_<method>.txt`: Timing information for each method.
- `benchmark_results.txt`: Summary of benchmark results.
