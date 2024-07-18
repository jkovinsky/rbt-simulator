PYTHON_CFLAGS = $(shell python3.12-config --cflags)
PYTHON_LFLAGS = $(shell python3.12-config --ldflags --embed)

rbt: main.cpp rbt.cpp rbt.hpp
	g++ -std=c++2a -O3 -Wall -g $(PYTHON_CFLAGS) -o rbt main.cpp rbt.cpp $(PYTHON_LFLAGS)

.PHONY: clean

clean:
	@rm -f rbt main.o rbt.o 
	@rm -r rbt.dSYM




