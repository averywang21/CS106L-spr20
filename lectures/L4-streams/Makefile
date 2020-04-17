FLAGS = -O -std=c++17 -Wall -Wextra
CC = g++ 

all: input output streamBuffer

input: inputStreams.o
	$(CC) $(CFLAGS) -o input inputStreams.o

output: outputStreams.o
	$(CC) $(CFLAGS) -o output outputStreams.o

streamBuffer: StreamBuffer.o
	$(CC) $(CFLAGS) -o streamBuffer StreamBuffer.o
	
clean:
	rm -f main *.o
