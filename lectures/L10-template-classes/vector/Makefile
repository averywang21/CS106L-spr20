CXX = g++
CXXFLAGS += -O -Wall -Wextra -std=c++17
SOURCES =  vector.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: clean all
.DEFAULT_GOAL := all

all: main

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ -c

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@
	rm *.o

clean:
	rm -f *.o main *.d