CFLAGS = -O -std=c++17 -Wall -Wextra
CC = g++ 
SRC = main.cpp 
OBJ = $(SRC:.cpp = .o) 

main: $(OBJ) 
	$(CC) $(CFLAGS) -o main $(OBJ) 
clean:
	rm -f main *.o
