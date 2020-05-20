CXX = g++
CXXFLAGS += -O -Wall -Wextra -std=c++17
SOURCES = median.h
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: clean all
.DEFAULT_GOAL := all

all: main

main: main.cpp median.h
	$(CXX) $(CXXFLAGS) -o main main.cpp

clean:
	rm -f main *.o