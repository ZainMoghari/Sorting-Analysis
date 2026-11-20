# Sorting Algorithms Empirical Analysis

## Overview
This project compares Bubble Sort, Selection Sort, Insertion Sort, and Merge Sort using the input sizes required in the assignment: 5, 10, 50, and 100 elements.

## Input and test method
The assignment's arrays are ascending. For worst-case testing, the program creates descending arrays of the same sizes. Descending input is a worst-case arrangement for Bubble Sort and Insertion Sort; Selection Sort and Merge Sort are also measured on the same input for a consistent comparison.

Each algorithm/input-size combination is measured in 5 trials. Each trial performs 20,000 sorts. A fresh copy of the input is created before each timed sort, so the measured interval focuses on the sorting operation rather than input preparation. The average time per sort is reported in microseconds.

## Requirements
- A C++ compiler supporting C++11 or later (g++).
- Python 3 and matplotlib are only needed if you want to regenerate the graph/report.

## Compile and run
```bash
g++ -O2 -std=c++11 sorting_analysis.cpp -o sorting_analysis
./sorting_analysis
```
On Windows with MinGW:
```bash
g++ -O2 -std=c++11 sorting_analysis.cpp -o sorting_analysis.exe
sorting_analysis.exe
```

The program prints CSV-formatted results to the terminal.

## Algorithms and complexity
| Algorithm | Best case | Average case | Worst case |
|---|---:|---:|---:|
| Bubble Sort (with early-exit flag) | O(n) | O(n^2) | O(n^2) |
| Selection Sort | O(n^2) | O(n^2) | O(n^2) |
| Insertion Sort | O(n) | O(n^2) | O(n^2) |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) |

## Files
- `sorting_analysis.cpp`: C++ source code.
- `results.csv`: measured average execution times.
- `sorting_comparison.png`: comparison graph.
- `SAP_Name_SortingAnalysis.pdf`: assignment report. Replace `Name` in the filename with your own name before submission.
