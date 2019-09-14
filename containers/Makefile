CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++11

all: deque_myclass deque

%.o: %.cpp 
	$(CC) -c -o $@ $< $(CFLAGS)

deque_myclass: deque_myclass.o
	$(CC) deque_myclass.o $(CFLAGS) -o deque_myclass

deque: main.o
	$(CC) main.o $(CFLAGS) -o deque

clean:
	rm *.o deque_myclass deque
