CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++11

all: deque_myclass

%.o: %.cpp 
	$(CC) -c -o $@ $< $(CFLAGS)

deque_myclass: main.o
	$(CC) main.o $(CFLAGS) -o deque_myclass.exe

clean:
	rm *.o deque_myclass.exe
