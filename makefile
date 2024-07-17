PYTHON_INCLUDE = $(shell python3.12-config --includes)
PYTHON_LDFLAGS = $(shell python3.12-config --ldflags)

rbt: rbt.hpp rbt.cpp main.cpp
	g++ -std=c++2a -O3 -Wall -Wextra -g -o rbt rbt.cpp main.cpp $(PYTHON_INCLUDE) $(PYTHON_LDFLAGS) -lpython3.12