CXX = g++
CXXFLAGS += -O0 -Wall -Wextra -std=c++17 
SOURCES =  main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp

clean:
	rm -f main *.o
