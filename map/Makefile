CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++11 -g -O

all: map test1 test2 minimal morseex stdmap-test-scaling test-scaling

%.o: %.cpp 
	$(CC) -c -o $@ $< $(CFLAGS)

map: main.o
	$(CC) main.o -o map.exe

test1: test1.o
	$(CC) test1.o -o test1.exe

test2: test2.o
	$(CC) test2.o -o test2.exe

minimal: minimal.o
	$(CC) minimal.o -o minimal.exe

morseex: morseex.o
	$(CC) morseex.o -o morseex.exe

stdmap-test-scaling: stdmap-test-scaling.o
	$(CC) stdmap-test-scaling.o -o stdmap-test-scaling.exe

test-scaling: test-scaling.o
	$(CC) test-scaling.o -o test-scaling.exe

clean:
	rm *.o map.exe test1.exe test2.exe minimal.exe morseex.exe stdmap-test-scaling.exe test-scaling.exe
