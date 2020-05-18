CXX = g++
CXXFLAGS += -O0 -Wall -Wextra -std=c++17
SOURCES =  hashmap.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: clean all
.DEFAULT_GOAL := all

all: main

main: tests.cpp hashmap.h hashmap.cpp main.cpp test_settings.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp

clean:
	rm -f main *.o
