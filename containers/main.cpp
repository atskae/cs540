#include <stdio.h>

#include "Deque.hpp"

Deque_DEFINE(int)
Deque_DEFINE(char)

int main() {

	printf("Containers in C: Deque\n");	
	
	Deque_int d_int;
	Deque_char d_char;

	return 0;
}
