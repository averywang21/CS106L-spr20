CFLAGS = -O -std=c++17 
CC = g++ 
SRC = main.cpp 
OBJ = $(SRC:.cpp = .o) 

get_data: $(OBJ) 
	$(CC) $(CFLAGS) -o main $(OBJ) 
clean:
	rm -f main *.o
