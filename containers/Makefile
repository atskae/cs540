CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++11

all: deque

%.o: %.cpp 
	$(CC) -c -o $@ $< $(CFLAGS)

deque: main.o
	$(CC) main.o $(CFLAGS) -o deque.exe

clean:
	rm *.o deque.exe
