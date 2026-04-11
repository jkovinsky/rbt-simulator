# Red-Black Tree vs Binary Search Tree Benchmark Tool

This project is an interactive C++ CLI program that compares the performance of a Red-Black Tree (RBT) and a Binary Search Tree (BST) by tracking insertion times, running simulations, and generating plots via Python.

It supports manual operations, randomized simulations, performance statistics, and file exports.

---

## Features

- Interactive command-line interface
- Compare Red-Black Tree and Binary Search Tree insertion performance
- Timing instrumentation for each insertion
- Randomized simulations (1000 inserts per run)
- Export results to text files
- Python-based plotting integration
- Statistical analysis (average, comparison, history output)

---

## Requirements

### C++ Dependencies
- C++17 or later
- Python development libraries (for embedding Python)
- Standard library (STL)

### Python Dependencies
- Python 3.x
- matplotlib (for plot.py)

Install Python dependencies:

```bash
pip install matplotlib
```
## Commands
1. `.insert` to insert a comma seperated list of numbers or `.sim` to simulate 1000 insertions
2. `.write` to write time values for each search algorithm
3. `.plot` to see average insertion speeds
4. `.compare` to see stats in command line
5. `.exit` to close the app
