CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++11 -ldl -g

all: test-run

%.o: %.cpp 
	$(CC) -c -o $@ $< $(CFLAGS)

test-run: main.o
	$(CC) main.o $(CFLAGS) -o test-run.exe

clean:
	rm *.o test-run.exe
