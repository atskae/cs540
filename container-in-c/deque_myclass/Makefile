CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++11 -g

all: deque_myclass

%.o: %.cpp 
	$(CC) -c -o $@ $< $(CFLAGS)

deque_myclass: main.o Deque_MyClass.o
	$(CC) main.o Deque_MyClass.o $(CFLAGS) -o deque_myclass.exe

clean:
	rm *.o deque_myclass.exe
