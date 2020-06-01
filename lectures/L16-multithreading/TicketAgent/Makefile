CXX = g++
CXXFLAGS += -O0 -Wall -Wextra -std=c++17 
SOURCES = ostreamlock.h main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: main

main: main.cpp ostreamlock.h
	$(CXX) $(CXXFLAGS) -o main main.cpp

clean:
	rm -f main *.o
