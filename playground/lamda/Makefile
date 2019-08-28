CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++11

all: lamda

%.o: %.cpp 
	$(CC) -c -o $@ $< $(CFLAGS)

lamda: main.o
	$(CC) main.o $(CFLAGS) -o lamda

clean:
	rm *.o lamda
