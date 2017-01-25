CC = nvcc
CPP = g++
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
CFLAGSE = -std=c++11

VALG = valgrind

all: main

main:
	$(CC) $(CFLAGS) $(SOURCES) -o xample.o

vec:
	$(CC) vecAddVec.cu

matrix:
	$(CC) matrixAddMatrix.cu

matvec:
	$(CC) matrixXVec.cu



clean: 
	rm -rf *o *out callgrind.out.*
	clear
