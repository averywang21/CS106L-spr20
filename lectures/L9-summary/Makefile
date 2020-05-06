FLAGS = -O -std=c++17 -Wall -Wextra
CC = g++ 
SRC = main.cpp 
OBJ = $(SRC:.cpp = .o) 

main: $(OBJ) 
	$(CC) $(CFLAGS) -o main $(OBJ) 
	
chal15: chal15.o
	$(CC) $(CFLAGS) -o chal15 chal15.o 

chal2: chal2.o
	$(CC) $(CFLAGS) -o chal2 chal2.o 

chal34: chal34.o
	$(CC) $(CFLAGS) -o chal34 chal34.o 

chal6: chal6.o
	$(CC) $(CFLAGS) -o chal6 chal6.o 

clean:
	rm -f main chal15 chal2 chal34 chal6 *.o
