CXX = g++
CXXFLAGS += -O0 -Wall -Wextra -std=c++17 
SOURCES =  vector.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: clean all
.DEFAULT_GOAL := all

all: main

main: main.cpp vector.h vector.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp

clean:
	rm -f main *.o
