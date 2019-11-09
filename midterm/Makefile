CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++11

all: string

%.o: %.cpp 
	$(CC) -c -o $@ $< $(CFLAGS)

string: main.o
	$(CC) main.o $(CFLAGS) -o string

clean:
	rm *.o string
