# README: Cache Efficiency in 2D Array Traversal

## Overview
This project explores cache efficiency in two-dimensional array traversal using a `ColorPoint` struct. It compares the performance of two different traversal patterns—row-major (`f` function) and column-major (`g` function)—to analyze their impact on cache performance and execution speed.

## Features
- **Dynamically allocates a 2D array** of `ColorPoint` structs.
- **Performs two different summation functions** (`f` and `g`) to measure the effect of cache locality.
- **Uses clock timing** to benchmark the execution speed of both traversal methods.
- **Demonstrates cache misses and memory access patterns** through comments and analysis.

## Files
- `main.c` - The main C program implementing the 2D array operations, summation functions, and performance benchmarking.

## Compilation and Execution
To compile and run the program, use:
```sh
gcc -o cache_analysis main.c
./cache_analysis
```

## Expected Output
The program prints the execution time for both traversal methods:
```
The time to run function f is X.XXXXXX seconds.
The time to run function g is Y.YYYYYY seconds.
```
Typically, function `f` (row-major traversal) runs faster due to better cache locality.

## Explanation of Results
- **Function `f` (Row-Major Traversal)**
  - Iterates through the 2D array in a contiguous memory order.
  - Leads to fewer cache misses.
  - Generally executes faster.

- **Function `g` (Column-Major Traversal)**
  - Accesses elements in a non-contiguous memory order.
  - Causes more cache misses, leading to slower execution.

## Key Learning Points
- Understanding how **cache memory affects performance**.
- The importance of **memory access patterns in optimizing algorithms**.
- Practical demonstration of **cache locality and cache miss penalties**.

## License
This project is open-source and can be used for educational purposes.

