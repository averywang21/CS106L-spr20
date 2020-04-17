FLAGS = -O -std=c++17 -Wall -Wextra
CC = g++ 
SRC = inputStreams.cpp outputStreams.cpp StreamBuffer.cpp 
OBJ = $(SRC:.cpp = .o) 

all: input output streamBuffer

input: inputStreams.o
	$(CC) $(CFLAGS) -o input inputStreams.o

output: outputStreams.o
	$(CC) $(CFLAGS) -o output outputStreams.o

streamBuffer: StreamBuffer.o
	$(CC) $(CFLAGS) -o streamBuffer StreamBuffer.o
	
clean:
	rm -f main *.o
