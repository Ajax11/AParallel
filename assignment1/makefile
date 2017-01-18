CC = g++
SOURCES = task1.cpp
OBJECTS = $(SOURCES:.cpp=.o)
CFLAGS = -std=c++11

VALG = valgrind

all: main

main:
	$(CC) $(CFLAGS) $(SOURCES) -o xample.o

val:
	$(VALG) --tool=callgrind --cacheuse=yes ./xample.o

clean: 
	rm -rf *o *out callgrind.out.*
	clear

