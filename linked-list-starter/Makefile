CXX = g++
CXXFLAGS += -O0 -Wall -Wextra -std=c++17
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: clean all
.DEFAULT_GOAL := all

all: main

main: tests.cpp list.h list_iterator.h
	$(CXX) $(CXXFLAGS) -o main tests.cpp

clean:
	rm -f main *.o
