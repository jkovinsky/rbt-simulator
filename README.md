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
## Get Started
1. CD into red-black-tree
2. Type `make` into the command line
3. Tpy ./rbt into the command line
4. Typical Demo Flow:
  - .insert: 5,10,15,20
  - .sim
  - .compare
  - .write
  - .plot
  - .exit
