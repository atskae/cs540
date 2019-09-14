CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++11

all: macros

%.o: %.cpp 
	$(CC) -c -o $@ $< $(CFLAGS)

macros: main.o
	$(CC) main.o $(CFLAGS) -o macros

clean:
	rm *.o macros
