CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++11 -g
EXE=array.exe

all: array memcheck clean

%.o: %.cpp 
	$(CC) -c -o $@ $< $(CFLAGS)

array: main.o
	$(CC) main.o -o $(EXE)

memcheck:
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXE)

clean:
	rm *.o *.exe
