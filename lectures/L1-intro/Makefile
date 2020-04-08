CFLAGS = -O -std=c++17 -Wall
CC = g++ 
SRC = hello.cpp 
OBJ = $(SRC:.cpp = .o) 

main: $(OBJ) 
	$(CC) $(CFLAGS) -o main $(OBJ) 
clean:
	rm -f main *.o
