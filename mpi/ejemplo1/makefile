CC = mpic++
CCC = mpicc
CCCC = gcc
SOURCE = trapecio.cpp
OBJECTS = $(SOURCES:.cpp=.o)
CFLAGS = -std=c++11
CCR = mpiexec
CCRO = mpirun

all: trapecio

trapecio: trapecio.cpp
	$(CC) $(CFLAGS) $(SOURCE) -o task

run:
	$(CCR) -n 5 ./task

clean: 
	rm -rf *o *out
	clear