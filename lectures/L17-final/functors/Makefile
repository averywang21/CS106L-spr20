CXX = g++
CXXFLAGS += -O -Wall -Wextra -std=c++17
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: clean all
.DEFAULT_GOAL := all

all: main

main: main.cpp 
	$(CXX) $(CXXFLAGS) -o main main.cpp

clean:
	rm -f main *.o